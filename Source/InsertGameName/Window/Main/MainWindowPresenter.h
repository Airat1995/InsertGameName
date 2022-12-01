// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainWindowView.h"
#include "Interface/AbstractWindowPresenter.h"

#include "MainWindowPresenter.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UMainWindowPresenter : public UAbstractWindowPresenter
{
	GENERATED_BODY()

	friend class FMainWindowFactory;

	void Init(TObjectPtr<UMainWindowView> View);
	
public:
	
	virtual ~UMainWindowPresenter() override;

	virtual void Open() override;

	virtual void Close() override;

protected:

	UPROPERTY()
	TObjectPtr<UMainWindowView> WindowView;
};
