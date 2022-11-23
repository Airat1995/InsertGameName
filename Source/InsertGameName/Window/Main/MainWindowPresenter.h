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
public:
	
	virtual ~UMainWindowPresenter() override;

	virtual void Open() override;

	virtual void Close() override;

	void Init(TObjectPtr<UMainWindowView> View);

protected:

	TObjectPtr<UMainWindowView> WindowView;
};
