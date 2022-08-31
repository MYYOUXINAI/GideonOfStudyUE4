// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActionEffect.h"
#include "MyActionEffect_Thorns.generated.h"



class UMyAttributeComponent;
/**
 * 
 */
UCLASS()
class STUDY_API UMyActionEffect_Thorns : public UMyActionEffect
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Thorns")
		float ReflectFraction;

	UFUNCTION()
		void OnHealthChanged(AActor* Instigator, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

public:
	virtual void StartAction_Implementation(AActor* InstigatorActor)override;
	
	virtual void StopAction_Implementation(AActor* InstigatorActor)override;

	UMyActionEffect_Thorns();
};
