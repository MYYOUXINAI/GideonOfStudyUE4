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
	// Sets default values for this actor's properties
	AMyItemChest();

protected:
	// Called when the game starts or when spawned
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
