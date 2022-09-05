// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPowerUpActor.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyPowerUpActor::AMyPowerUpActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;

	SetReplicates(true);
}

void AMyPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{

}

//void AMyPowerUpActor::ShowPowerup()
//{
//	/*SetPowerupState(true);*/
//}

void AMyPowerUpActor::ShowPowerup_Implementation()
{
	SetPowerupState(true);
}

//void AMyPowerUpActor::HideAndCoolPowerup()
//{
//	/*SetPowerupState(false);
//
//	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &AMyPowerUpActor::ShowPowerup, RespawnTime);*/
//}

void AMyPowerUpActor::HideAndCoolPowerup_Implementation()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &AMyPowerUpActor::ShowPowerup, RespawnTime);
}

void AMyPowerUpActor::SetPowerupState(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
	OnRep_IsActive();
}

void AMyPowerUpActor::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	RootComponent->SetVisibility(bIsActive, true);
}

void AMyPowerUpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPowerUpActor, bIsActive);
}



