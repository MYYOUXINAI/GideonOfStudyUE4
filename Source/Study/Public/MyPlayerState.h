// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, AMyPlayerState*, PlayerState, int32, NewCredits, int32, Delta);


class UMySaveGame;
/**
 * 
 */
UCLASS()
class STUDY_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,ReplicatedUsing="OnRep_Credits", Category = "Credits"/*,Replicated*/)
	int32 Credits;

	UFUNCTION()
	void OnRep_Credits(int OldCredits);

public:
	UFUNCTION(BlueprintCallable,Category="Credits")
		int32 GetCredits()const;

	UFUNCTION(BlueprintCallable, Category = "Credits")
		void AddCredits(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Credits")
		bool RemoveCredits(int32 Delta);

	UPROPERTY(BlueprintAssignable, Category = "CustomEvents")
		FOnCreditsChanged OnCreditsChanged;
	
	UFUNCTION(BlueprintNativeEvent)
		void SavePlayerState(UMySaveGame* SaveObject);
	virtual void SavePlayerState_Implementation(UMySaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
		void LoadPlayerState(UMySaveGame* SaveObject);
	virtual void LoadPlayerState_Implementation(UMySaveGame* SaveObject);

	AMyPlayerState();

};
