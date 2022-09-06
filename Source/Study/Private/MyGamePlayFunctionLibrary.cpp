// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGamePlayFunctionLibrary.h"
#include "MyAttributeComponent.h"
#include "Components/PrimitiveComponent.h"

bool UMyGamePlayFunctionLibrary::ApplyDamege(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	if (TargetActor)
	{
		UMyAttributeComponent* AttributeComp = UMyAttributeComponent::GetAttributes(TargetActor);

		if (AttributeComp)
		{
			return AttributeComp->ApplyHealthChange(DamageCauser, DamageAmount);
		}
	}

	return false;
}

bool UMyGamePlayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if (ApplyDamege(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}

		return true;
	}

	return false;
}
