// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/MyAICharacter.h"
#include "MyAttributeComponent.h"
#include "EngineUtils.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "GameFramework/GameStateBase.h"
#include "MyInterface.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
//#include "GameFramework/GameModeBase.h"


static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);


AMyGameModeBase::AMyGameModeBase()
{

	SpawnTimerInterval = 2.0f;

	CreditsPerKill = 20;
	
	DesiredPowerupCount = 10;
	RequiredPowerupDistance = 2000;

	PlayerStateClass = AMyPlayerState::StaticClass();

	SlotName = "SaveGame01";
}



void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AMyGameModeBase::SpawnBotTimeElapsed, SpawnTimerInterval, true);


}

void AMyGameModeBase::KillAll()
{

	for (TActorIterator<AMyAICharacter> It(GetWorld()); It; ++It)
	{
		AMyAICharacter* Bot = *It;

		UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(Bot->GetComponentByClass(UMyAttributeComponent::StaticClass()));

		if (AttributeComp && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this);//@fixme: pass player as a instigator; for kill credits
		}
	}
}

void AMyGameModeBase::SpawnBotTimeElapsed()
{

	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("bot spawning disabled via cvar 'cvarSpawnBots'."));
	}

	int32 NrOfAliveBots = 0;
	for (TActorIterator<AMyAICharacter> It(GetWorld()); It; ++It)
	{
		AMyAICharacter* Bot = *It;

		UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(Bot->GetComponentByClass(UMyAttributeComponent::StaticClass()));

		if (AttributeComp && AttributeComp->IsAlive())
		{
			++NrOfAliveBots;
		}
	}

	float MaxBotCount = 2.0f;

	if (SpawnCreditCurve)
	{
		MaxBotCount = SpawnCreditCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
	}

	if (NrOfAliveBots >= MaxBotCount)	return;


	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AMyGameModeBase::OnQueryCompleted);
	}
}

void AMyGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)	return;


	

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}

void AMyGameModeBase::RespawnPlayerElapsed(AController* Controller)
{

	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}



void AMyGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{

	AMyPlayerState* PS = NewPlayer->GetPlayerState<AMyPlayerState>();
	if (PS)
	{
		PS->LoadPlayerState(CurrentSaveGame);
	}
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

void AMyGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	this->LoadSaveGame();
}

void AMyGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	AMyCharacter* Player = Cast<AMyCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		float RespawnDelay = 2.0f;

		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}

	APawn* KillerPawn = Cast<APawn>(Killer);
	if (KillerPawn)
	{
		AMyPlayerState* PS = KillerPawn->GetPlayerState<AMyPlayerState>();
		if (PS)
		{
			PS->AddCredits(CreditsPerKill);
		}
	}	
}


void AMyGameModeBase::WirteSaveGame()
{
	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		AMyPlayerState* PS = Cast<AMyPlayerState>(GameState->PlayerArray[i]);
		if (PS)
		{
			PS->SavePlayerState(CurrentSaveGame);
			break;
		}
	}

	CurrentSaveGame->SaveActors.Empty();

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor->Implements<UMyInterface>())	continue;
		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetName();
		ActorData.ActorTransform = Actor->GetTransform();

		FMemoryWriter MemWriter(ActorData.byteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;

		Actor->Serialize(Ar);

		CurrentSaveGame->SaveActors.Add(ActorData);
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
}

void AMyGameModeBase::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		if (CurrentSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("load game failed!!! please check it"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Load game succed!"));
		}

		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			if (!Actor->Implements<UMyInterface>())	continue;

			for (FActorSaveData ActorData : CurrentSaveGame->SaveActors)
			{
				if (ActorData.ActorName == Actor->GetName())
				{
					Actor->SetActorTransform(ActorData.ActorTransform);

					FMemoryReader MemReader(ActorData.byteData);
					FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
					Ar.ArIsSaveGame = true;
					Actor->Serialize(Ar);

					IMyInterface::Execute_OnActorLoaded(Actor);

					break;
				}
			}
		}
	}
	else
	{
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("Create save game successed!"));
	}
}