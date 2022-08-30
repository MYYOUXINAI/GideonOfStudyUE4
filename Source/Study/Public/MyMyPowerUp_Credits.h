// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPowerUpActor.h"
#include "MyMyPowerUp_Credits.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API AMyMyPowerUp_Credits : public AMyPowerUpActor
{
	GENERATED_BODY()

protected:
	int32 CreditsAmount;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;


	AMyMyPowerUp_Credits();
};
