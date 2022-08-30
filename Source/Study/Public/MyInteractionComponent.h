// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyInteractionComponent.generated.h"


class UMyWorldUserWidget;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDY_API UMyInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyInteractionComponent();

	void PrimaryInteract();

protected:
	virtual void BeginPlay() override;

	void FindBestInstractable();

	UPROPERTY()
		AActor* FocusActor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UMyWorldUserWidget> DefaultWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		TEnumAsByte<ECollisionChannel> CollisionChannel;



	UPROPERTY()
		UMyWorldUserWidget* DefaultWidgetInstance;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
