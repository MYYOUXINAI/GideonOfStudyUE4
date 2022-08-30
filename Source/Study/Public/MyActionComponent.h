// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "gameplayTagContainer.h"
#include "MyActionComponent.generated.h"

class UMyAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDY_API UMyActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = "Action")
		void AddAction(AActor* InstigatorActor, TSubclassOf<UMyAction> ActionClass);


	UFUNCTION(BlueprintCallable, Category = "Action")
		void RemoveAction(UMyAction* RemoveToAction);

	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StartActionByName(AActor* InstigatorActor, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StopActionByName(AActor* InstigatorActor, FName ActionName);

	UMyActionComponent();

protected:

	UPROPERTY()
	TArray<UMyAction*>Actions;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	TArray<TSubclassOf<UMyAction>> DefaultsActions;

	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
