// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"

// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	this->Health = 200.0f;
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

bool UMyAttributeComponent::ApplyHealthChange(float Delta)
{
	/*this->Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;*/

	float OldHealth = this->Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);

	return ActualDelta != 0;
}

