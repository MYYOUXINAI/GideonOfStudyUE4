// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPowerUpActor.h"
#include "MyPowerUp_HealthPotion.generated.h"



class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class STUDY_API AMyPowerUp_HealthPotion : public AMyPowerUpActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

	AMyPowerUp_HealthPotion();
};
