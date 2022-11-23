// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WindowPresenter.generated.h"


// This class does not need to be modified.
UINTERFACE()
class UWindowPresenter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSERTGAMENAME_API IWindowPresenter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Open() = 0;

	virtual void Close() = 0;
};
