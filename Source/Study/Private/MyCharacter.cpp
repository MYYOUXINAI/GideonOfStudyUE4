// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyInteractionComponent.h"
#include "MyAttributeComponent.h"
#include "MyActionComponent.h"
#include "MyAction.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<UMyInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<UMyActionComponent>("ActionComp");

	TimeToHitParamName = "TimeToHit";
}


void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyCharacter::OnHealthChanged);
}

FVector AMyCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}


void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MyMoveForward", this, &AMyCharacter::MyMoveForward);

	PlayerInputComponent->BindAxis("MyTurnRight", this, &AMyCharacter::MyTurnRight);

	PlayerInputComponent->BindAction("MySprint", IE_Pressed, this, &AMyCharacter::SprintStart);

	PlayerInputComponent->BindAction("MySprint", IE_Released, this, &AMyCharacter::SprintStop);

	PlayerInputComponent->BindAxis("MyTurn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MyLookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("MyJump", IE_Pressed, this, &AMyCharacter::Jump);

	PlayerInputComponent->BindAction("MyPrimaryAttack",IE_Pressed, this, &AMyCharacter::MyPrimaryAttack);

	PlayerInputComponent->BindAction("MyDash", IE_Pressed, this, &AMyCharacter::MyDash);

	PlayerInputComponent->BindAction("MyBlackHoleAttack", IE_Pressed, this, &AMyCharacter::MyBlackHoleAttack);

	PlayerInputComponent->BindAction("MyPrimaryInteraction", IE_Pressed, this, &AMyCharacter::MyPrimaryInteraction);
}


void AMyCharacter::MyMoveForward(float Value)
{
	FRotator CameraRotation = GetControlRotation();
	CameraRotation.Pitch = 0.0f;
	CameraRotation.Roll = 0.0f;

	AddMovementInput(CameraRotation.Vector(), Value);
}


void AMyCharacter::MyTurnRight(float Value)
{
	FRotator CameraRotation = GetControlRotation();
	CameraRotation.Pitch = 0.0f;
	CameraRotation.Roll = 0.0f;

	FVector RightVector=FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}


void AMyCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void AMyCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

void AMyCharacter::MyPrimaryAttack()
{
	ActionComp->StartActionByName(this, "MyPrimaryAttack");
}


void AMyCharacter::MyDash()
{
	ActionComp->StartActionByName(this, "MyDash");
}


void AMyCharacter::MyBlackHoleAttack()
{
	ActionComp->StartActionByName(this, "MyBlackHoleAttack");
}


void AMyCharacter::MyPrimaryInteraction()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}


void AMyCharacter::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{

	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}


void AMyCharacter::HealSelf(float Amount)
{
	if (AttributeComp)
	{
		AttributeComp->ApplyHealthChange(this, Amount);
	}
}