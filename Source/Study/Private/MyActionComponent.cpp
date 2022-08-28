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

	
}

void UMyActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}



void UMyActionComponent::AddAction(TSubclassOf<UMyAction> ActionClass)
{
	UMyAction* NewAction = NewObject<UMyAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
	return;

}

bool UMyActionComponent::StartActionByName(AActor* InstigatorActor, FName ActionName)
{
	for (UMyAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
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
			Action->StopAction(InstigatorActor);
			return true;
		}
	}
	return false;
}