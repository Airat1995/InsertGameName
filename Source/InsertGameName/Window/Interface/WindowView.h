// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UObject/Interface.h"
#include "WindowView.generated.h"

UINTERFACE()
class UWindowView : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSERTGAMENAME_API IWindowView
{
	GENERATED_BODY()

public:

	virtual void Open() = 0;

	virtual void Close() = 0;
};
