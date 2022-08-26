// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_RangeAttack.generated.h"

/**
 * 
 */


UCLASS()
class STUDY_API UMyBTTask_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor>ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "AI")
		float MaxBulletSpread;

public:
	UMyBTTask_RangeAttack();

};
