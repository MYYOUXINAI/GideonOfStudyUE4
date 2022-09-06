// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "gameplayTagContainer.h"
#include "MyAction.generated.h"



USTRUCT()
struct FActionRepData
{
	GENERATED_BODY();
public:

	UPROPERTY()
		bool bisRunning;

	UPROPERTY()
		AActor* InstigatorActor;
};


/**
 * 
 */
class UTexture2D;
class UWorld;
class UMyActionComponent;

UCLASS(Blueprintable)
class STUDY_API UMyAction : public UObject
{
	GENERATED_BODY()
	


protected:

	UPROPERTY(Replicated)
	float TimeStarted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(Replicated)
		UMyActionComponent* ActionComp;

	UFUNCTION(BlueprintCallable, Category = "Action")
		UMyActionComponent* GetOwningComponent()const;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer BlockedTags;


	UPROPERTY(ReplicatedUsing="OnRep_RepData")
		FActionRepData RepData;

	UFUNCTION()
	void OnRep_RepData();

public:

	void Initialize(UMyActionComponent* NewActionComp);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
		bool bAutoStart;

	UFUNCTION(BlueprintCallable, Category = "Action")
		bool isRunning()const;



	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		bool CanStart(AActor* InstigatorActor);
	virtual bool CanStart_Implementation(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StartAction(AActor* InstigatorActor);
	virtual void StartAction_Implementation(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Action")
		void StopAction(AActor* InstigatorActor);
	virtual void StopAction_Implementation(AActor* InstigatorActor);


	UPROPERTY(EditDefaultsOnly,Category="Action")
	FName ActionName;

	virtual UWorld* GetWorld()const override;


	 bool IsSupportedForNetworking()const override;
};
