// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemChest.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h" 



// Sets default values
AMyItemChest::AMyItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	MyRotator = 110.0f;

	SetReplicates(true);

}

void AMyItemChest::OnActorLoaded_Implementation()
{
	OnRep_LidOpened();
}

// Called when the game starts or when spawned
void AMyItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyItemChest::Interact_Implementation(APawn* IntigatorPawn)
{
	bLidOpened = !bLidOpened;

	OnRep_LidOpened();
}

void AMyItemChest::OnRep_LidOpened()
{
	float CurrPitch = bLidOpened ? MyRotator : 0.0f;

	LidMesh->SetRelativeRotation(FRotator(CurrPitch, 0.0f, 0.0f));
}

void AMyItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyItemChest, bLidOpened);
}