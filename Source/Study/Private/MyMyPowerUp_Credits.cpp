// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMyPowerUp_Credits.h"
#include "MyPlayerState.h"
#include "GameFramework/Pawn.h"


AMyMyPowerUp_Credits::AMyMyPowerUp_Credits()
{
	CreditsAmount = 80;
}

void AMyMyPowerUp_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return ;
	}

	if (AMyPlayerState* PS = InstigatorPawn->GetPlayerState<AMyPlayerState>())
	{
		PS->RemoveCredits(this->CreditsAmount);

		HideAndCoolPowerup();
	}
}


