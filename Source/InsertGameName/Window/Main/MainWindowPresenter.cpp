// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWindowPresenter.h"

UMainWindowPresenter::~UMainWindowPresenter()
{
}

void UMainWindowPresenter::Open()
{
	WindowView->Open();
}

void UMainWindowPresenter::Close()
{
	WindowView->Close();
}

void UMainWindowPresenter::Init(TObjectPtr<UMainWindowView> View)
{
	WindowView = View;
}
