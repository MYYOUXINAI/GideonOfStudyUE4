// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionEffect.h"
#include "MyActionComponent.h"

UMyActionEffect::UMyActionEffect()
{
	this->bAutoStart = true;
}

void UMyActionEffect::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	if (Duration > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopAction", InstigatorActor);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}

	if (Period > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodEffect", InstigatorActor);

		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}
}

void UMyActionEffect::StopAction_Implementation(AActor* InstigatorActor)
{

	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		this->ExecutePeriodEffect(InstigatorActor);
	}

	Super::StopAction_Implementation(InstigatorActor);

	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);

	UMyActionComponent* Comp = GetOwningComponent();
	if (Comp)
	{
		Comp->RemoveAction(this);
	}
}



void UMyActionEffect::ExecutePeriodEffect_Implementation(AActor* InstigatorActor)
{
}
