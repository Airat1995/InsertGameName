// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainWindowController.h"
#include "WindowDataAsset.h"
#include "Interface/AbstractWindowController.h"
#include "Interface/WindowFactory.h"

/**
 * 
 */
class INSERTGAMENAME_API FMainWindowFactory : public IWindowFactory
{
	
public:
	explicit FMainWindowFactory(TObjectPtr<UWorld> SpawnObjectWorld, TObjectPtr<UWindowDataAsset> WindowDataAsset);
	virtual ~FMainWindowFactory() override;

	virtual UAbstractWindowController* CreateWindow() override;
	virtual UClass* GetWindowControllerType() const noexcept override
	{
		return UMainWindowController::StaticClass();
	}

private:
	TObjectPtr<UWorld> World;
	TObjectPtr<UWindowDataAsset> DataAsset;
	
};
