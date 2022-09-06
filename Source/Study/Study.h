// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/EngineBaseTypes.h"
#include "UObject/Object.h"


static void LogOnScreen(UObject* WorldContext, FString Msg, FColor Color = FColor::White, float Duration = 0.5f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	UWorld* world = WorldContext->GetWorld();
	if (!ensure(world))
	{
		return;
	}

	FString NetPerfix = world->IsNetMode(NM_Client) ? "[CLIENT]" : "[SERVER]";
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, NetPerfix + Msg);
	}
}
