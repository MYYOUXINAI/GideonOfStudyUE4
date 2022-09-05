// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"


USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString ActorName;

	UPROPERTY()
		FTransform ActorTransform;

	UPROPERTY()
		TArray<uint8>byteData;
};

/**
 * 
 */
UCLASS()
class STUDY_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Credits;
	
	UPROPERTY()
	TArray<FActorSaveData>SaveActors;


};
