// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyInteractionComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<UMyInteractionComponent>("InteractionComp");

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MyMoveForward", this, &AMyCharacter::MyMoveForward);

	PlayerInputComponent->BindAxis("MyTurnRight", this, &AMyCharacter::MyTurnRight);

	PlayerInputComponent->BindAxis("MyTurn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MyLookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("MyPrimaryAttack",IE_Pressed, this, &AMyCharacter::MyPrimaryAttack);

	PlayerInputComponent->BindAction("MyPrimaryInteraction", IE_Pressed, this, &AMyCharacter::MyPrimaryInteraction);
}

//控制角色向前移动
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

void AMyCharacter::MyPrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTM = FTransform(GetActorRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void AMyCharacter::MyPrimaryInteraction()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}


