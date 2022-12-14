// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
//class UParticleSystem;


UCLASS(ABSTRACT)
class STUDY_API AMyProjectileBase : public AActor
{
	GENERATED_BODY()
	


protected:

	UPROPERTY(EditDefaultsOnly,Category="Effect")
		UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
		USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UParticleSystemComponent* EffectComp;



	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
	
	virtual void Explode_Implementation();

	virtual void PostInitializeComponents() override;

public:	
	// Sets default values for this actor's properties
	AMyProjectileBase();
};
