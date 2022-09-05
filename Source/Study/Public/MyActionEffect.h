// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAction.h"
#include "MyActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UMyActionEffect : public UMyAction
{
	GENERATED_BODY()
public:
	virtual void StartAction_Implementation(AActor* InstigatorActor)override;

	virtual void StopAction_Implementation(AActor* InstigatorActor)override;

	UFUNCTION(BlueprintCallable, Category = "Action")
		float GetTimeRemaining()const;

	UMyActionEffect();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
		float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
		float Period;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintNativeEvent, Category = "Effect")
		void ExecutePeriodEffect(AActor* InstigatorActor);
	virtual void ExecutePeriodEffect_Implementation(AActor* InstigatorActor);
	
};
