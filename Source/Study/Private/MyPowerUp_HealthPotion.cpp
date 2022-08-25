// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPowerUp_HealthPotion.h"
#include "MyAttributeComponent.h"

AMyPowerUp_HealthPotion::AMyPowerUp_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MeshComp->SetupAttachment(RootComponent);
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
		if (AttributeComp->ApplyHealthChange(AttributeComp->GetMaxHealth()))
		{
			this->HideAndCoolPowerup();
		}
	}
	
}

