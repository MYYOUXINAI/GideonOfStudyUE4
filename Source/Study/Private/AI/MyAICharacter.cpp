// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAttributeComponent.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "MyWorldUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	TimeToHitParamName = "TimeToHit";
}

void AMyAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMyAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyAICharacter::OnHealthChanged);
}

void AMyAICharacter::OnPawnSeen(APawn* Pawn)
{

	this->SetTargetActor(Pawn);
}

void AMyAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

void AMyAICharacter::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{

		if (InstigatorActor != this)
		{
			this->SetTargetActor(InstigatorActor);
		}


		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

		if (ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<UMyWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			
			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}

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

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

		}
	}
}


