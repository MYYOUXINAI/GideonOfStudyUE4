// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "MyPowerUpActor.generated.h"

class USphereComponent;

UCLASS()
class STUDY_API AMyPowerUpActor : public AActor,public IMyInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "PowerUP")
	float RespawnTime;
	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCoolPowerup();

	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

public:	

	void Interact_Implementation(APawn* InstigatorPawn) override;

	// Sets default values for this actor's properties
	AMyPowerUpActor();

};
