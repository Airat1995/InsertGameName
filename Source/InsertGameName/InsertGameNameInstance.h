// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDataAsset.h"
#include "Engine/GameInstance.h"
#include "MapAssetManager.h"
#include "ServiceContainer.h"
#include "InsertGameNameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UInsertGameNameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UInsertGameNameInstance();

	void SetMapDataAsset(TObjectPtr<UMapDataAsset> DataAsset);
	TObjectPtr<UMapDataAsset> GetMapDataAsset() const noexcept;

	void SetSelectedDifficulty(EDifficulty Difficulty) noexcept;
	EDifficulty GetSelectedDifficulty() const noexcept;

	TObjectPtr<UServiceContainer> GetServiceContainer() const noexcept;

private:

	UPROPERTY()
	TObjectPtr<UMapDataAsset> MapDataAsset;

	UPROPERTY()
	TObjectPtr<UServiceContainer> ServiceContainer;
	
	EDifficulty SelectedDifficulty = EDifficulty::Normal;
	
};
