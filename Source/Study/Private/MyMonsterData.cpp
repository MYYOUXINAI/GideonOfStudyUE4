// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMonsterData.h"

FPrimaryAssetId UMyMonsterData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("Monsters", GetFName());
}
