// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainWindowPresenter.h"
#include "Interface/AbstractWindowController.h"

#include "MainWindowController.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UMainWindowController : public UAbstractWindowController
{
	GENERATED_BODY()
	
public:

	virtual ~UMainWindowController() override;
	
	void Init(const TObjectPtr<UMainWindowPresenter>& Object);

protected:

	TObjectPtr<UMainWindowPresenter> Presenter;
};
