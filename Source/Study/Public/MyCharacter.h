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
class UMyActionComponent;
class UMyAction;

UCLASS()
class STUDY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();


protected:

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActionComponent")
	UMyActionComponent* ActionComp;

	void MyMoveForward(float Value);

	void MyTurnRight(float Value);

	void SprintStart();
	void SprintStop();

	void MyPrimaryAttack();

	void MyDash();

	void MyBlackHoleAttack();

	void MyPrimaryInteraction();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents()override;

	virtual FVector GetPawnViewLocation()const override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount=100);

};
