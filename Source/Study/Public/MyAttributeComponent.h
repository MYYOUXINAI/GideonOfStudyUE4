// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UMyAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, UMyAttributeComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDY_API UMyAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UMyAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes",meta=(DisplayName="IsAlive"))
	static bool IsActorAlive(AActor* FromActor);

	// Sets default values for this component's properties
	UMyAttributeComponent();

protected:
	// Called when the game starts
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Replicated,Category="Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Replicated, Category = "Attributes")
	float HealthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Replicated, Category = "Attributes")
		float Rage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Replicated, Category = "Attributes")
		float RageMax;

	UFUNCTION(NetMulticast, reliable)
	void MulticastHealthChanged(AActor* Instigator, float NewHealth, float Delta);
	void MulticastHealthChanged_Implementation(AActor* Instigator, float NewHealth, float Delta);


	UFUNCTION(NetMulticast, Unreliable)
		void MulticastRageChanged(AActor* Instigator, float NewRage, float Delta);
	virtual void MulticastRageChanged_Implementation(AActor* Instigator, float NewRage, float Delta);

public:	

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable)
	bool IsAlive()const;

	UFUNCTION(BlueprintCallable)
		bool IsFullHealth()const;

	UFUNCTION(BlueprintCallable)
		float GetMaxHealth()const;

	UFUNCTION(BlueprintCallable)
		float GetCurrentHealth()const;


	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnRageChanged;

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetRage()const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool ApplyRage(AActor* Instigator, float Delta);
};
