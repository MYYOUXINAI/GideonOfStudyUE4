// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

AMyPlayerState::AMyPlayerState()
{
    Credits = 0;
    //OnCreditsChanged.Broadcast(this, this->Credits, Credits);
}



int32 AMyPlayerState::GetCredits() const
{
    return this->Credits;
}

void AMyPlayerState::AddCredits(int32 Delta)
{
    if (!ensure(Delta > 0.0f))
    {
        return;
    }
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

