// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAttributeComponent.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMyAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyAICharacter::OnHealthChanged);
}

void AMyAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", Pawn);
		BBComp->SetValueAsVector("MoveToLocation", Pawn->GetActorLocation());
		DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 4.0f, true);
	}
}

void AMyAICharacter::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (NewHealth <= 0.0f)
		{
			//Stop Behavior

			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("The Minion is killed!");
			}

			//Fall Down

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			//Set Liftspan

			SetLifeSpan(10.0f);

		}
	}
}


