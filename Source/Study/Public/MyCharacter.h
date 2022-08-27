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

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;


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

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
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

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents()override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount=100);

};
