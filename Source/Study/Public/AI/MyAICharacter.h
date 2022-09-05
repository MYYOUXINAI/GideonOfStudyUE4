// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyAICharacter.generated.h"

class UPawnSensingComponent;
class UMyAttributeComponent;
class UUserWidget;
class UMyWorldUserWidget;
class UMyActionComponent;

UCLASS()
class STUDY_API AMyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAICharacter();

protected:

	UMyWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget>HealthBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget>SpottedWidgetClass;

	UPROPERTY(VisibleAnywhere,Category="Effect")
	FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TargetActorKey;

	virtual void PostInitializeComponents()override;

	UPROPERTY(VisibleAnywhere,Category="AI")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMyAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMyActionComponent* ActionComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION(NetMulticast, UnReliable)
		void MulticastOnPawnSeen(APawn* Pawn);
	virtual void MulticastOnPawnSeen_Implementation(APawn* Pawn);

	UFUNCTION()
	void SetTargetActor(AActor* NewTarget);

	UFUNCTION()
		AActor* GetTargetActor()const;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);
};
