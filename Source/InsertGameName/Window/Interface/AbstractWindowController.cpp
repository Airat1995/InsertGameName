// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractWindowController.h"

void UAbstractWindowController::Open()
{
	WindowPresenter->Open();
}

void UAbstractWindowController::Close()
{
}

void UAbstractWindowController::DestroyWindow()
{
}
