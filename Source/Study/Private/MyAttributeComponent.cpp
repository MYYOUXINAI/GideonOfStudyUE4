// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"

// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	this->Health = 200.0f;
}







bool UMyAttributeComponent::ApplyHealthChange(float Delta)
{
	this->Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

