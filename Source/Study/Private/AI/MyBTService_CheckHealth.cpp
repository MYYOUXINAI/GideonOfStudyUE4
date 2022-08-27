// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTService_CheckHealth.h"
#include "AIController.h"
#include "MyAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTService_CheckHealth::UMyBTService_CheckHealth()
{
	this->LowHealthFraction = 0.4;
}


void UMyBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (AIPawn)
	{
		UMyAttributeComponent* AttributeComp = UMyAttributeComponent::GetAttributes(Cast<AActor>(AIPawn));

		if (ensure(AttributeComp))
		{
			bool bLowHealth = AttributeComp->GetCurrentHealth() / AttributeComp->GetMaxHealth() <= LowHealthFraction;

			UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
			if (BlackboardComp)
			{
				BlackboardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
			}
		}
	}
}

