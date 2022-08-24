// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr! Please assign Behavior Tree in your AI Controller.")))
	{

		RunBehaviorTree(BehaviorTree);
	}


	//APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//if (ensure(MyPawn))
	//{
	//	GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

	//	GetBlackboardComponent()->SetValueAsObject("TargetActor", Cast<AActor>(MyPawn));
	//}
}
