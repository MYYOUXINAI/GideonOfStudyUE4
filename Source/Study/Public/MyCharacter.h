// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UMyInteractionComponent;
class UAnimMontage;
class UMyAttributeComponent;

UCLASS()
class STUDY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();


protected:
	UPROPERTY(EditAnywhere, Category = "MyAttack")
	TSubclassOf<AActor>DashProjectile;

	UPROPERTY(EditAnywhere, Category = "MyAttack")
	TSubclassOf<AActor>BlackHoleProjectile;

	UPROPERTY(EditAnywhere,Category="MyAttack")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "MyAttack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "MyAttack")
	float AnimateDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UMyInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	UMyAttributeComponent* AttributeComp;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimerHandle_BlackHoleAttack;

	void MyMoveForward(float Value);

	void MyTurnRight(float Value);

	void MyPrimaryAttack();
	void PrimaryAttack_TimeElapsed();

	void MyDash();
	void Dash_TimeElapsed();

	void MyBlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();

	void MyPrimaryInteraction();

	void SpawnProjectile(TSubclassOf<AActor>ClassToSpawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
