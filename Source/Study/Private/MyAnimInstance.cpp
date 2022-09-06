// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "gameplayTagContainer.h"
#include "MyActionComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AActor* OwningActor = GetOwningActor();
	if(OwningActor)
	{
		ActionComp = Cast<UMyActionComponent>(OwningActor->GetComponentByClass(UMyActionComponent::StaticClass()));

	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	static FGameplayTag StunnedTag = FGameplayTag::RequestGameplayTag("Status.Stunned");

	if(ActionComp)
	{
		bIsStunned = ActionComp->ActiveGameplayTags.HasTag(StunnedTag);
	}
}
