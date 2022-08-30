// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPowerUp_HealthPotion.h"
#include "MyPlayerState.h"
#include "MyAttributeComponent.h"

AMyPowerUp_HealthPotion::AMyPowerUp_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MeshComp->SetupAttachment(RootComponent);

	CreditsAmount = 80;
}

void AMyPowerUp_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{

	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(InstigatorPawn->GetComponentByClass(UMyAttributeComponent::StaticClass()));

	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (AMyPlayerState* PS=InstigatorPawn->GetPlayerState<AMyPlayerState>())
		{
			if (PS->RemoveCredits(CreditsAmount) && AttributeComp->ApplyHealthChange(this, AttributeComp->GetMaxHealth()))
			{
				this->HideAndCoolPowerup();
			}
		}
	}
	
}

