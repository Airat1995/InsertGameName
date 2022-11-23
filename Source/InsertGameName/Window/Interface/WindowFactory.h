// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WindowFactory.generated.h"

UINTERFACE()
class UWindowFactory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSERTGAMENAME_API IWindowFactory
{
	GENERATED_BODY()

public:

	virtual UClass* GetWindowControllerType() const noexcept = 0;
	
	virtual UAbstractWindowController* CreateWindow() = 0;
};
