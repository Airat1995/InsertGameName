// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWindowController.h"


UMainWindowController::~UMainWindowController()
{
}

void UMainWindowController::Init(const TObjectPtr<UMainWindowPresenter>& Object)
{
	Presenter = Object;
}
