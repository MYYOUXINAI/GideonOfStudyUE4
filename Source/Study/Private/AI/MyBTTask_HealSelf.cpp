// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTTask_HealSelf.h"
#include "AIController.h"
#include "MyAttributeComponent.h"

EBTNodeResult::Type UMyBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* AIPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
    
    if (AIPawn==nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UMyAttributeComponent* AttributeComp = UMyAttributeComponent::GetAttributes(AIPawn);
    if (ensure(AttributeComp))
    {
        AttributeComp->ApplyHealthChange(AIPawn, AttributeComp->GetMaxHealth());
    }
    return  EBTNodeResult::Succeeded;
}
