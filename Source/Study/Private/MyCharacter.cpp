// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyInteractionComponent.h"
#include "MyAttributeComponent.h"

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

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	TimeToHitParamName = "TimeToHit";
	
}


void AMyCharacter::PostInitializeComponents()
{

	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyCharacter::OnHealthChanged);
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

	PlayerInputComponent->BindAction("MyJump", IE_Pressed, this, &AMyCharacter::Jump);
	//PlayerInputComponent->BindAction("MyJump", IE_Released, this, &AMyCharacter::StopJumping);

	PlayerInputComponent->BindAction("MyPrimaryAttack",IE_Pressed, this, &AMyCharacter::MyPrimaryAttack);

	PlayerInputComponent->BindAction("MyDash", IE_Pressed, this, &AMyCharacter::MyDash);

	PlayerInputComponent->BindAction("MyBlackHoleAttack", IE_Pressed, this, &AMyCharacter::MyBlackHoleAttack);

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
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMyCharacter::PrimaryAttack_TimeElapsed, AnimateDelay);
}

void AMyCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(PrimaryProjectileClass);
}

void AMyCharacter::MyDash()
{
	PlayAnimMontage(this->AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &AMyCharacter::Dash_TimeElapsed, AnimateDelay);
}

void AMyCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectile);
}

void AMyCharacter::MyBlackHoleAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack, this, &AMyCharacter::BlackHoleAttack_TimeElapsed, AnimateDelay);
}

void AMyCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectile);
}

void AMyCharacter::MyPrimaryInteraction()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void AMyCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComp->GetComponentLocation();
		
		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		FHitResult Hit;
		// returns true if we got to a blocking hit
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			// Overwrite trace end with impact point in world
			TraceEnd = Hit.ImpactPoint;
		}

		// find new direction/rotation from Hand pointing to impact point in world.
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}

void AMyCharacter::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{

	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}

	if (NewHealth < 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}



