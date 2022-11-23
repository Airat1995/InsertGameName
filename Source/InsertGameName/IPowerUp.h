// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPowerUp.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPowerUp : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSERTGAMENAME_API IPowerUp
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void AddScore(float Score);
	
protected:

	virtual void Use() = 0;
	virtual void ResetTrigger();
	virtual void SetTriggeringCount(uint8 Count);
	virtual void SetScoreToTrigger(float Score);
	
private:
	
	float ScoreToTrigger = 0;
	uint8 TriggerCount = 0;
	uint8 InitialTriggerCount = 0;
	
};
