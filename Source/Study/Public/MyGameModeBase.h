// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "MyGameModeBase.generated.h"


class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class UMySaveGame;
/**
 * 
 */
UCLASS()
class STUDY_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:

	UPROPERTY()
		FString SlotName;

	UPROPERTY()
		UMySaveGame* CurrentSaveGame;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		int32 CreditsPerKill;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		int32 DesiredPowerupCount;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		int32 RequiredPowerupDistance;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* SpawnCreditCurve;
	
	UFUNCTION()
	void SpawnBotTimeElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
	
public:
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)override;

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)override;

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	AMyGameModeBase();

	virtual void StartPlay()override;

	UFUNCTION(Exec)
	void KillAll();
	
	UFUNCTION(BlueprintCallable, Category = "MySaveGame")
		void WirteSaveGame();

	UFUNCTION(BlueprintCallable, Category = "MySaveGame")
		void LoadSaveGame();

};
