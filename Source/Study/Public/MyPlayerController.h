// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, APlayerState*, NewPlayerState);


/**
 * 
 */
UCLASS()
class STUDY_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable)
		FOnPawnChanged OnPawnChanged;


	UPROPERTY(BlueprintAssignable)
		FOnPlayerStateChanged OnPlayerStateReceived;

	virtual void SetPawn(APawn* InPawn)override;
	
	virtual void BeginPlayingState()override;

	UFUNCTION(BlueprintImplementableEvent)
		void BlueprintBeginPlayState();

	void OnRep_PlayerState()override;

};
