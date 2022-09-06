// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "gameplayTagContainer.h"
#include "MyActionComponent.generated.h"

class UMyAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged, UMyActionComponent*, OwningComp, UMyAction*, Action);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDY_API UMyActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = "Action")
		void AddAction(AActor* InstigatorActor, TSubclassOf<UMyAction> ActionClass);

	UFUNCTION(BlueprintCallable,Category="Action")
		void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
		void RemoveAction(UMyAction* RemoveToAction);

	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StartActionByName(AActor* InstigatorActor, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StopActionByName(AActor* InstigatorActor, FName ActionName);

	UMyActionComponent();

protected:

	
	
	UFUNCTION(Server, Reliable)
		void ServerStartAction(AActor* InstigatorActor, FName ActionName);
	virtual void ServerStartAction_Implementation(AActor* InstigatorActor, FName ActionName);

	UFUNCTION(Server, Reliable)
		void ServerStopAction(AActor* InstigatorActor, FName ActionName);
	virtual void ServerStopAction_Implementation(AActor* InstigatorActor, FName ActionName);

	UPROPERTY(BlueprintReadOnly,Replicated)
	TArray<UMyAction*>Actions;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	TArray<TSubclassOf<UMyAction>> DefaultsActions;

	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
		FOnActionStateChanged OnActionStopped;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)override;
};
