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

	friend class FMainWindowFactory;

	void Init(const TObjectPtr<UMainWindowPresenter>& Object, bool bShowCursor);
	
public:

	virtual ~UMainWindowController() override;

	virtual void Open() override;

	virtual void Close() override;

	virtual void DestroyWindow() override;

protected:

	UPROPERTY()
	TObjectPtr<UMainWindowPresenter> Presenter;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	
	bool bShouldShowCursor;
};
