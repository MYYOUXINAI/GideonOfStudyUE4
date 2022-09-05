// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "MyItemChest.generated.h"


class UStaticMeshComponent;
UCLASS()
class STUDY_API AMyItemChest : public AActor,public IMyInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* IntigatorPawn);
	
public:	
	AMyItemChest();

	void OnActorLoaded_Implementation();

protected:
	UPROPERTY(ReplicatedUsing="OnRep_LidOpened", BlueprintReadOnly,SaveGame)
	bool bLidOpened;

	UFUNCTION()
	void OnRep_LidOpened();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;


	UPROPERTY(EditAnywhere)
	float MyRotator;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
