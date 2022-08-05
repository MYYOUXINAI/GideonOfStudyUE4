// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemChest.h"
#include "Components/StaticMeshComponent.h"



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
	LidMesh->SetRelativeRotation(FRotator(MyRotator, 0.0f, 0.0f));
}
