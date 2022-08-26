// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMagicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "MyAttributeComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "AI/MyAICharacter.h"

// Sets default values
AMyMagicProjectile::AMyMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	SphereComp->SetCollisionProfileName("MyProjectile");

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMyMagicProjectile::OnActorOverlap);

	this->DamageValue = -50;


	/*AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
	if (ensure(AudioComp))
	{
		AudioComp->Play();
	}*/

}

// Called when the game starts or when spawned
void AMyMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMyMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor!=GetInstigator())
	{
		UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>( OtherActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));

		


		if (AttributeComp)
		{

			AttributeComp->ApplyHealthChange(DamageValue);

			if (ensure(!IsPendingKill()))
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

				Destroy();
			}


			/*AMyAICharacter* MyAI = Cast<AMyAICharacter>(OtherActor);
			if (MyAI)
			{
				float tempF = AttributeComp->GetCurrentHealth();
				UE_LOG(LogTemp, Log, TEXT("have attacked The actor, and the least health is: %f"),tempF);
			}*/
		}
	}

}

// Called every frame
void AMyMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

