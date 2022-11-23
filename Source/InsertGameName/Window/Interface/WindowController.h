// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WindowController.generated.h"

UINTERFACE()
class UWindowController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSERTGAMENAME_API IWindowController
{
	GENERATED_BODY()

public:
	
	virtual void Open() = 0;

	virtual void Close() = 0;

	virtual void Destroy() = 0;
};
