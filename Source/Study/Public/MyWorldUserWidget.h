// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWorldUserWidget.generated.h"




class USizeBox;
/**
 * 
 */
UCLASS()
class STUDY_API UMyWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

public:

	UPROPERTY(EditAnywhere, Category = "MyUI")
	FVector WorldOffset;

	UPROPERTY(BlueprintReadOnly, Category = "MyUI",meta=(ExposeOnSpawn=true))
	AActor* AttachActor;
};
