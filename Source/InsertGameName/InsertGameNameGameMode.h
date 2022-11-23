// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArenaGameState.h"
#include "MapDataAsset.h"
#include "AssetLoadingState.h"
#include "UObject/ConstructorHelpers.h"
#include "InsertGameNameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayerController.h"
#include "MapAssetManager.h"
#include "PowerUpSystem.h"
#include "InsertGameNameGameMode.generated.h"

UCLASS(minimalapi)
class AInsertGameNameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInsertGameNameGameMode();
	
	void MapAssetsLoaded(const UMapDataAsset* LoadedMapDataAsset);
	void TargetLoaded(const UTargetDataAsset* TargetDataAsset);
	void PowerUpsLoaded(const TArray<UPowerUpPrimaryDataAsset*> PowerUpPrimaryDataAssets);
	virtual void BeginPlay() override;
	
	virtual void StartPlay() override;
	FORCEINLINE bool GameReadyToStart()
	{
		return !bGameStarted && AllAssetsLoaded();
	}

protected:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnTimerEnd();

	FORCEINLINE bool AllAssetsLoaded()
	{
		bool bLoaded = true;
		for (const auto State : AssetLoadingState)
		{
			bLoaded &= State.Value == EAssetLoadingState::Loaded;
		}

		return bLoaded;
	}
	UFUNCTION(BlueprintCallable)
	void SetTimer(float time);

	UFUNCTION(BlueprintCallable)
	void AddTime(float time);
	
	UFUNCTION(BlueprintCallable)
	void ScoreCount(float Score);

	template< class UserClass >
	void SubscribeOnTimerEnd(UserClass* Object, typename FInputActionHandlerSignature::TMethodPtr< UserClass > Func )
	{
		GameTimer->SubscribeOnTimerEnd(Object, Func);
	}
	
private:
	void AssignPredefinedWeapons(const UMapDataAsset* LoadedMapDataAsset) const;
	void LoadTargets(const UMapDataAsset* LoadedMapDataAsset, UMapAssetManager& AssetManager);
	void LoadPowerUps(const UMapDataAsset* LoadedMapDataAsset, UMapAssetManager& AssetManager);
	
	bool bGameStarted = false;
	FMapDataAssetLoaded MapDataLoadDelegate;
	FTargetDataAssetLoaded TargetDataAssetLoaded;
	FPowerUpsAssetsLoaded PowerUpsAssetsLoaded;
	TObjectPtr<UScoreCounter> ScoreCounter;
	TObjectPtr<UTargetSpawner> TargetSpawner;
	TObjectPtr<UPowerUpSystem> PowerUpSystem;
	TObjectPtr<UGlobalTimer> GameTimer;
	TMap<FPrimaryAssetType, EAssetLoadingState> AssetLoadingState;
};



