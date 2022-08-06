// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UMyInteractionComponent;
class UAnimMontage;

UCLASS()
class STUDY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();


protected:
	UPROPERTY(EditAnywhere,Category="MyAttack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "MyAttack")
	UAnimMontage* AttackAnim;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UMyInteractionComponent* InteractionComp;

	void MyMoveForward(float Value);

	void MyTurnRight(float Value);

	void MyPrimaryAttack();

	void MyPrimaryInteraction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
