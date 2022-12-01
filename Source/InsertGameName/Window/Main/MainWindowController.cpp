// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWindowController.h"


UMainWindowController::~UMainWindowController()
{
}

void UMainWindowController::Init(const TObjectPtr<UMainWindowPresenter>& Object, const bool bShowCursor)
{
	Presenter = Object;
	bShouldShowCursor = bShowCursor;

	PlayerController = GetWorld()->GetFirstPlayerController();
}

void UMainWindowController::Open()
{
	Presenter->Open();
	PlayerController->bShowMouseCursor = bShouldShowCursor;
	PlayerController->bEnableClickEvents = bShouldShowCursor;
	PlayerController->bEnableMouseOverEvents = bShouldShowCursor;
}

void UMainWindowController::Close()
{
	Presenter->Close();
	PlayerController->bShowMouseCursor = false;
	PlayerController->bEnableClickEvents = false;
	PlayerController->bEnableMouseOverEvents = false;

}

void UMainWindowController::DestroyWindow()
{
	Presenter->DestroyWindow();
}
