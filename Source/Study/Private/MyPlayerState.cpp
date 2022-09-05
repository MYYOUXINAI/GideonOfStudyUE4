// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MySaveGame.h"
#include "Net/UnrealNetwork.h"



AMyPlayerState::AMyPlayerState()
{
    Credits = 0;
}

void AMyPlayerState::OnRep_Credits(int OldCredits)
{
    OnCreditsChanged.Broadcast(this, this->Credits, this->Credits - OldCredits);
}

int32 AMyPlayerState::GetCredits() const
{
    return this->Credits;
}

void AMyPlayerState::AddCredits(int32 Delta)
{
    /*if (!ensure(Delta > 0.0f))
    {
        return;
    }*/
    this->Credits += Delta;

    OnCreditsChanged.Broadcast(this, this->Credits, Delta);
}

bool AMyPlayerState::RemoveCredits(int32 Delta)
{
    if (!ensure(Delta >= 0.0f))
    {
        return false;
    }
    if (this->Credits < Delta)
    {
        return false;
    }

    this->Credits -= Delta;
    OnCreditsChanged.Broadcast(this, this->Credits, -Delta);
    return true;
}

void AMyPlayerState::SavePlayerState_Implementation(UMySaveGame* SaveObject)
{
    if (SaveObject)
    {
        SaveObject->Credits = this->Credits;

    }
}

void AMyPlayerState::LoadPlayerState_Implementation(UMySaveGame* SaveObject)
{
    if (SaveObject)
    {
        //this->Credits = SaveObject->Credits;
        AddCredits(SaveObject->Credits);
    }
    
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMyPlayerState, Credits);
}