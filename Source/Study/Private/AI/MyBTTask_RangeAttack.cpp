// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTTask_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMyBTTask_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (false)
	{
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController))
		{
			ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
			if (MyPawn == nullptr)
			{
				return EBTNodeResult::Failed;
			}

			FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");

			AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

			if (TargetActor == nullptr)
			{
				return EBTNodeResult::Failed;
			}

			FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;

			FRotator MuzzleRotator = Direction.Rotation();

			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotator, Params);
			if (ensure(NewProj)) {}
			ensureMsgf(NewProj, TEXT("The Spawn NewProj is error!"));
			return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
		}

		return EBTNodeResult::Failed;
	}

	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		//FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");
		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_Front_XForward"); 

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = MyPawn;

		AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
