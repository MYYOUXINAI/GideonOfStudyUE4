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
	UPROPERTY(ReplicatedUsing = "OnRep_IsActive"/*,Replicated*/)
		bool bIsActive;

	UFUNCTION()
		void OnRep_IsActive();



	UPROPERTY(EditAnywhere, Category = "PowerUP")
	float RespawnTime;
	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION(NetMulticast, Unreliable)
	void ShowPowerup();
	virtual void ShowPowerup_Implementation();

	UFUNCTION(NetMulticast, Unreliable)
	void HideAndCoolPowerup();
	virtual void HideAndCoolPowerup_Implementation();

	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

public:

	FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

	void Interact_Implementation(APawn* InstigatorPawn) override;

	// Sets default values for this actor's properties
	AMyPowerUpActor();

};
