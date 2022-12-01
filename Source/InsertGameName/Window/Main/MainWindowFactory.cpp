// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWindowFactory.h"

#include "MainWindowController.h"
#include "MainWindowPresenter.h"
#include "MainWindowView.h"
#include "InsertGameName/MapAssetManager.h"
#include "Interface/AbstractWindowController.h"

FMainWindowFactory::FMainWindowFactory(TObjectPtr<UWorld> SpawnObjectWorld,
                                       TObjectPtr<UWindowDataAsset> WindowDataAsset) : World(SpawnObjectWorld), DataAsset(WindowDataAsset)
{
}

FMainWindowFactory::~FMainWindowFactory()
{
}

UAbstractWindowController* FMainWindowFactory::CreateWindow()
{
	UClass* ViewClass =  DataAsset->GetWindowView().LoadSynchronous();
	const UClass* PresenterClass = DataAsset->GetWindowPresenter().LoadSynchronous();
	const UClass* ControllerClass = DataAsset->GetWindowController().LoadSynchronous();
	
	const TObjectPtr<UMainWindowController> Controller =  NewObject<UMainWindowController>(World, ControllerClass);
	const TObjectPtr<UMainWindowPresenter> Presenter = NewObject<UMainWindowPresenter>(World, PresenterClass);
	const TObjectPtr<UMainWindowView> View = CreateWidget<UMainWindowView>(World.Get(), ViewClass);
	Presenter->Init(View);
	Controller->Init(Presenter, DataAsset->GetShouldShowCursor());

	return Controller;
}
