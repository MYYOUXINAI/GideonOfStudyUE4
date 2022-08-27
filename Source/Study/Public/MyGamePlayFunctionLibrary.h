// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyGamePlayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UMyGamePlayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	static bool ApplyDamege(AActor* DamageCauser, AActor* TargetActor, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	static bool ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult);
	
};
