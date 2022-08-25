// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPowerUpActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyPowerUpActor::AMyPowerUpActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;
}

void AMyPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{

}
void AMyPowerUpActor::ShowPowerup()
{
	SetPowerupState(true);
}

void AMyPowerUpActor::HideAndCoolPowerup()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &AMyPowerUpActor::ShowPowerup, RespawnTime);
}

void AMyPowerUpActor::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(bNewIsActive, true);
}





