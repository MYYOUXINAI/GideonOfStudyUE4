// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"
#include "MyGameModeBase.h"
#include "Net/UnrealNetwork.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.damageMultiplier"), 1.0f, TEXT("Global damage modifier for attribute component."), ECVF_Cheat);


// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	this->HealthMax = 200.0f;
	this->Health = this->HealthMax;

	this->RageMax = 100.f;
	this->Rage = 0.f;

	SetIsReplicatedByDefault(true);
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
	float ActualHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = ActualHealth - OldHealth;

	if (GetOwner()->HasAuthority())
	{
		Health = ActualHealth;
		if (ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		if (Health == 0.0f && ActualDelta < 0.0f)
		{
			AMyGameModeBase* GM = GetWorld()->GetAuthGameMode<AMyGameModeBase>();

			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}
	//OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}

float UMyAttributeComponent::GetRage() const
{
	return this->Rage;
}

bool UMyAttributeComponent::ApplyRage(AActor* Instigator, float Delta)
{
	float OldRage = this->Rage;
	Rage = FMath::Clamp(Rage + Delta, 0.0f, this->RageMax);

	float CurrentDelta = Rage - OldRage;
	if (CurrentDelta != 0)
	{
		OnRageChanged.Broadcast(Instigator, this, this->Rage, CurrentDelta);
	}
	return CurrentDelta != 0;
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

void UMyAttributeComponent::MulticastHealthChanged_Implementation(AActor* Instigator, float NewHealth, float Delta)
{

	OnHealthChanged.Broadcast(Instigator, this, NewHealth, Delta);
	ApplyRage(Instigator, -Delta);
}

void UMyAttributeComponent::MulticastRageChanged_Implementation(AActor* Instigator, float NewRage, float Delta)
{
	OnRageChanged.Broadcast(Instigator, this, NewRage, Delta);
}


void UMyAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyAttributeComponent, Health);
	DOREPLIFETIME(UMyAttributeComponent, HealthMax);

	DOREPLIFETIME(UMyAttributeComponent, Rage);
	DOREPLIFETIME(UMyAttributeComponent, RageMax);

	//DOREPLIFETIME_CONDITION(UMyAttributeComponent, HealthMax, COND_InitialOnly);//to save resource
}