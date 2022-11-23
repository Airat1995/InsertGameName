// Fill out your copyright notice in the Description page of Project Settings.


#include "IUpdatablePowerUp.h"

void IIUpdatablePowerUp::AddScore(float Score)
{
	if(bIsActive)
		return;
	IPowerUp::AddScore(Score);
}

// Add default functionality here for any IIUpdatablePowerUp functions that are not pure virtual.
void IIUpdatablePowerUp::Update(float DeltaTime)
{
	if(!bIsActive)
		return;

	ActiveTime-=DeltaTime;
	if(ActiveTime <= 0)
	{
		OnEndPowerUp.Broadcast();
		bIsActive = false;
	}
}

void IIUpdatablePowerUp::Use()
{
	OnStartPowerUp.Broadcast();
	bIsActive = true;
}

void IIUpdatablePowerUp::SetActiveTime(float Time)
{
	ActiveTime = Time;
}
