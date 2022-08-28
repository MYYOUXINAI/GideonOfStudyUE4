// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAction.h"
#include "MyAttributeComponent.h"
#include "MyActionComponent.h"
#include "GameplayTagContainer.h"






bool UMyAction::CanStart_Implementation(AActor* InstigatorActor)
{
	if (isRunning())	return false;

	UMyActionComponent* comp = GetOwningComponent();
	if (comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}

void UMyAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	UMyActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	bisRunning = true;
}

void UMyAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	ensureAlways(bisRunning);

	UMyActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bisRunning = false;
}

UWorld* UMyAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if (Comp)
	{
		return Comp->GetWorld();
	}

	return nullptr;
}

UMyActionComponent* UMyAction::GetOwningComponent() const
{
	return Cast<UMyActionComponent>(GetOuter());
}

bool UMyAction::isRunning() const
{
	return bisRunning;
}