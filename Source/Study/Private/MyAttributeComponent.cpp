// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"
#include "MyGameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.damageMultiplier"), 1.0f, TEXT("Global damage modifier for attribute component."), ECVF_Cheat);


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

	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}


	float OldHealth = this->Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);


	if (Health == 0.0f && ActualDelta < 0.0f)
	{
		AMyGameModeBase* GM = GetWorld()->GetAuthGameMode<AMyGameModeBase>();

		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

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
