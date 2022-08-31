// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionEffect_Thorns.h"
#include "MyAttributeComponent.h"
#include "MyActionComponent.h"
#include "MyGamePlayFunctionLibrary.h"


UMyActionEffect_Thorns::UMyActionEffect_Thorns()
{
	ReflectFraction = 0.2;
	this->Duration = 0.0f;
	this->Period = 0.0f;

}


void UMyActionEffect_Thorns::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	UMyAttributeComponent* AttributeComp = UMyAttributeComponent::GetAttributes(InstigatorActor);
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.AddDynamic(this, &UMyActionEffect_Thorns::OnHealthChanged);
	}
}

void UMyActionEffect_Thorns::StopAction_Implementation(AActor* InstigatorActor)
{
	Super::StopAction_Implementation(InstigatorActor);

	UMyAttributeComponent* AttributeComp = UMyAttributeComponent::GetAttributes(InstigatorActor);
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &UMyActionEffect_Thorns::OnHealthChanged);
	}

}


void UMyActionEffect_Thorns::OnHealthChanged(AActor* Instigator, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	AActor* OwnerActor = GetOwningComponent()->GetOwner();

	if (Delta < 0.0f && OwnerActor != Instigator)
	{
		int32 ReflectedAmount = FMath::RoundToInt(Delta * ReflectFraction);

		if (ReflectedAmount == 0)
		{
			return;
		}

		ReflectedAmount = fabs(ReflectedAmount);
		
		UMyGamePlayFunctionLibrary::ApplyDamege(OwnerActor, Instigator, -ReflectedAmount);
	}
}