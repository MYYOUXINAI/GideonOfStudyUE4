// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionComponent.h"
#include "MyAction.h"


UMyActionComponent::UMyActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


void UMyActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UMyAction> ActionClass : DefaultsActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
}

void UMyActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}



void UMyActionComponent::AddAction(AActor* InstigatorActor, TSubclassOf<UMyAction> ActionClass)
{
	UMyAction* NewAction = NewObject<UMyAction>(this, ActionClass);
	if (ensure(NewAction))
	{
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
				Action->StopAction(InstigatorActor);
				return true;
			}
		}
	}
	return false;
}