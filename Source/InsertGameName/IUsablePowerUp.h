// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPowerUp.h"
#include "UObject/Interface.h"
#include "IUsablePowerUp.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIUsablePowerUp : public UPowerUp
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSERTGAMENAME_API IIUsablePowerUp : public IPowerUp
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
