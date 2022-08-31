// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractionComponent.h"
#include "MyInterface.h"
#include "MyWorldUserWidget.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMyInteractionComponent::UMyInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceDistance = 500.f;
	TraceRadius = 30.0f;
	CollisionChannel = ECC_WorldDynamic;
}





// Called when the game starts
void UMyInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}




// Called every frame
void UMyInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		this->FindBestInstractable();
	}
}

void UMyInteractionComponent::FindBestInstractable()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	FVector Start, End;
	FVector EyeLocation;
	FRotator EyeRotation;
	AActor* MyOwner = GetOwner();

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	Start = EyeLocation;
	End = EyeLocation + TraceDistance * EyeRotation.Vector();

	TArray<FHitResult>Hits;
	float Radius = TraceRadius;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool RightHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor ResColor = RightHit ? FColor::Green : FColor::Red;

	FocusActor = nullptr;

	for (FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UMyInterface>())
			{
				FocusActor = HitActor;

				//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, ResColor, false, 2.0f);
				break;
			}
		}
	}

	if (FocusActor)
	{
		if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<UMyWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachActor = FocusActor;
			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}

	//DrawDebugLine(GetWorld(), EyeLocation, End, ResColor, false, 2.0f, 0, 2.0f);
}


void UMyInteractionComponent::PrimaryInteract()
{
	ServerInterface(FocusActor);
}

void UMyInteractionComponent::ServerInterface_Implementation(AActor* InFocus)
{
	if (InFocus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No Focus Actor to Interact!");
		return;
	}

	APawn* MyApawn = Cast<APawn>(GetOwner());
	IMyInterface::Execute_Interact(InFocus, MyApawn);
}
