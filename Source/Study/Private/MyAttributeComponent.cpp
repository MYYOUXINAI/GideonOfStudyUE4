// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"



// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	this->Health = 200.0f;
}







bool UMyAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}

bool UMyAttributeComponent::IsAlive()const
{
	return this->Health > 0;
}

bool UMyAttributeComponent::IsFullHealth() const
{
	return this->Health==this->HealthMax;
}

float UMyAttributeComponent::GetMaxHealth() const
{
	return this->HealthMax;
}

float UMyAttributeComponent::GetCurrentHealth() const
{
	return this->Health;
}

bool UMyAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	/*this->Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;*/

	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}


	float OldHealth = this->Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}

UMyAttributeComponent* UMyAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UMyAttributeComponent>(FromActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UMyAttributeComponent::IsActorAlive(AActor* FromActor)
{
	UMyAttributeComponent* AttributeComp = UMyAttributeComponent::GetAttributes(FromActor);

	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}
