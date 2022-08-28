// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyAction.generated.h"

/**
 * 
 */
class UWorld;

UCLASS(Blueprintable)
class STUDY_API UMyAction : public UObject
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StartAction(AActor* InstigatorActor);
	virtual void StartAction_Implementation(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StopAction(AActor* InstigatorActor);
	virtual void StopAction_Implementation(AActor* InstigatorActor);


	UPROPERTY(EditDefaultsOnly,Category="Action")
	FName ActionName;

	virtual UWorld* GetWorld()const override;
};
