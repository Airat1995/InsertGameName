// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowOnlyGameModeBase.h"

#include "AbstractWindowService.h"
#include "InsertGameName/InsertGameNameInstance.h"
#include "InsertGameName/MapAssetManager.h"
#include "Main/MainWindowFactory.h"

void AWindowOnlyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const UMapAssetManager& AssetManager = UMapAssetManager::Get();
	const UInsertGameNameInstance* GameInstance = GetGameInstance<UInsertGameNameInstance>();
	
	AbstractWindowService& WindowService = GameInstance->GetServiceContainer()->GetService<AbstractWindowService>();

	TArray<TObjectPtr<UWindowDataAsset>> WindowDataAssets = AssetManager.GetAllWindows();
	
	FMainWindowFactory* MainWindowFactory = new FMainWindowFactory(GetWorld(), WindowDataAssets[0]);
	WindowService.RegisterWindowFactory(MainWindowFactory);

	WindowService.OpenWindow(UMainWindowController::StaticClass());
}
