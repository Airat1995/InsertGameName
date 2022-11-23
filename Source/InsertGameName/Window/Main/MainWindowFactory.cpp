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
	UClass* PresenterClass = DataAsset->GetWindowPresenter().LoadSynchronous();
	UClass* ControllerClass = DataAsset->GetWindowController().LoadSynchronous();

	UMapAssetManager& AssetManager = UMapAssetManager::Get();
	TObjectPtr<UMainWindowController> Controller =  NewObject<UMainWindowController>(World, ControllerClass);
	TObjectPtr<UMainWindowPresenter> Presenter = NewObject<UMainWindowPresenter>(World, PresenterClass);
	TObjectPtr<UMainWindowView> View = Cast<UMainWindowView>(World->SpawnActor(ViewClass));
	Presenter->Init(View);
	Controller->Init(Presenter);

	return Controller;
}
