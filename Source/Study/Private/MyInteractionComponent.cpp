// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractionComponent.h"
#include "MyInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMyInteractionComponent::UMyInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UMyInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector Start, End;
	FVector EyeLocation;
	FRotator EyeRotation;
	AActor* MyOwner = GetOwner();

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	Start = EyeLocation;
	End = EyeLocation + 1000 * EyeRotation.Vector();


	TArray<FHitResult>Hits;
	float Radius = 30.0f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);



	bool RightHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End,FQuat::Identity, ObjectQueryParams,Shape);

	FColor ResColor = RightHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<UMyInterface>())
			{
				APawn* MyApawn = Cast<APawn>(MyOwner);

				IMyInterface::Execute_Interact(HitActor, MyApawn);

				//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, ResColor, false, 2.0f);

				break;
			}
		}
	}

	//DrawDebugLine(GetWorld(), EyeLocation, End, ResColor, false, 2.0f, 0, 2.0f);
}