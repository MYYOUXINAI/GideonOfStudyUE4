// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAction.h"
#include "MyAttributeComponent.h"
#include "MyActionComponent.h"
#include "GameplayTagContainer.h"
#include "Net/UnrealNetwork.h"




void UMyAction::Initialize(UMyActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

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

	RepData.bisRunning = true;
	RepData.InstigatorActor = InstigatorActor;
}

void UMyAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	//ensureAlways(bisRunning);

	UMyActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	
	RepData.bisRunning = false;
	RepData.InstigatorActor = InstigatorActor;
}

UWorld* UMyAction::GetWorld() const
{
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}

bool UMyAction::IsSupportedForNetworking() const
{
	return true;
}


UMyActionComponent* UMyAction::GetOwningComponent() const
{
	return ActionComp;
	//return Cast<UMyActionComponent>(GetOuter());
}

void UMyAction::OnRep_RepData()
{
	if (RepData.bisRunning)
	{
		StartAction(RepData.InstigatorActor);
	}
	else
	{
		StopAction(RepData.InstigatorActor);
	}
}


bool UMyAction::isRunning() const
{
	return RepData.bisRunning;
}

void UMyAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyAction, RepData);
	DOREPLIFETIME(UMyAction, ActionComp);
}