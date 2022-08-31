// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionComponent.h"
#include "MyAction.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"


UMyActionComponent::UMyActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UMyActionComponent::BeginPlay()
{
	Super::BeginPlay();

	//only run in server
	if (GetOwner()->HasAuthority())
	{
		for (TSubclassOf<UMyAction> ActionClass : DefaultsActions)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}
}

void UMyActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}



void UMyActionComponent::AddAction(AActor* InstigatorActor, TSubclassOf<UMyAction> ActionClass)
{
	if (!GetOwner()->HasAuthority())	return;

	if (!ensure(ActionClass))	return;

	UMyAction* NewAction = NewObject<UMyAction>(GetOwner(), ActionClass);
	if (ensure(NewAction))
	{
		NewAction->Initialize(this);

		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(InstigatorActor)))
		{
			NewAction->StartAction(InstigatorActor);
		}
	}
	return;

}


void UMyActionComponent::RemoveAction( UMyAction* RemoveToAction)
{
	if (!ensure(RemoveToAction && !RemoveToAction->isRunning()))
	{
		return;
	}
	Actions.Remove(RemoveToAction);
}

bool UMyActionComponent::StartActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (UMyAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(InstigatorActor))	continue;

			if (!GetOwner()->HasAuthority())
			{
				ServerStartAction(InstigatorActor, ActionName);
			}

			Action->StartAction(InstigatorActor);
			return true;
		}
	}
	return false;
}

bool UMyActionComponent::StopActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (UMyAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->isRunning())
			{
				if (!GetOwner()->HasAuthority())
				{
					ServerStopAction(InstigatorActor, ActionName);
				}
				Action->StopAction(InstigatorActor);
				return true;
			}
		}
	}
	return false;
}


void UMyActionComponent::ServerStartAction_Implementation(AActor* InstigatorActor, FName ActionName)
{
	StartActionByName(InstigatorActor, ActionName);
}

void UMyActionComponent::ServerStopAction_Implementation(AActor* InstigatorActor, FName ActionName)
{
	StopActionByName(InstigatorActor, ActionName);
}

bool UMyActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (UMyAction* Action : Actions)
	{
		if (Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}


void UMyActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyActionComponent, Actions);
}


