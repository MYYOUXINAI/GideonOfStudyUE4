// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/MyAICharacter.h"
#include "MyAttributeComponent.h"
#include "EngineUtils.h"

AMyGameModeBase::AMyGameModeBase()
{

	SpawnTimerInterval = 2.0f;

}



void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AMyGameModeBase::SpawnBotTimeElapsed, SpawnTimerInterval, true);


}
void AMyGameModeBase::SpawnBotTimeElapsed()
{

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

