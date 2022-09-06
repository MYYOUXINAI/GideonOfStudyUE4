// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyMonsterData.generated.h"

class UTexture2D;
class UMyAction;
/**
 * 
 */
UCLASS()
class STUDY_API UMyMonsterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
		TSubclassOf<AActor>MonsterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
		TArray<TSubclassOf<UMyAction>>Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		UTexture2D* Icon;

	FPrimaryAssetId GetPrimaryAssetId() const override;
};
