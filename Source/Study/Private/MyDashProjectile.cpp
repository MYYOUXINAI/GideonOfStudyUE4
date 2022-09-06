// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDashProjectile.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Sound/SoundCue.h"


AMyDashProjectile::AMyDashProjectile()
{
	this->TeleportDelay = 0.2f;
	this->DetonateDelay = 0.2f;

	this->MoveComp->InitialSpeed = 6000.f;
}

void AMyDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &AMyDashProjectile::Explode, DetonateDelay);
}

void AMyDashProjectile::Explode_Implementation()
{

	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AMyDashProjectile::TeleportInstigator, TeleportDelay);
	
}

void AMyDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();

	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}


