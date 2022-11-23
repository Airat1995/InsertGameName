// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetDataAsset.h"
#include "PowerUpPrimaryDataAsset.h"
#include "InsertGameName/Weapon.h"
#include "MapDataAsset.generated.h"


/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UMapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset", meta = (AllowPrivateAccess = true))
	FPrimaryAssetType Type;
	
	UPROPERTY(EditAnywhere, Category = "Info", meta = (AllowPrivateAccess = true))
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UWorld> LoadLevel;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (UIMin = 0.0, UIMax = 10000000.0, AllowPrivateAccess = true))
	float LevelTime;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta =(AllowPrivateAccess = true, AssetBundles = "Targets"))
	TSoftObjectPtr<UTargetDataAsset> LevelTargetInfo;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (AllowPrivateAccess = true,  AssetBundles = "PowerUps"))
	TArray<TSoftObjectPtr<UPowerUpPrimaryDataAsset>> MapPowerUps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AWeapon>> PredefinedWeapons;

public:

	FORCEINLINE FName GetLevelName() const noexcept
	{
		return LevelName;
	}

	FORCEINLINE float GetLevelTime() const noexcept
	{
		return LevelTime;
	}
	
	FORCEINLINE TAssetPtr<UWorld> GetLoadLevel() const noexcept
	{
		return LoadLevel;
	}

	FORCEINLINE TAssetPtr<UTargetDataAsset> GetLevelTargetInfo() const noexcept
	{
		return LevelTargetInfo;
	}
	
	FORCEINLINE const TArray<TAssetPtr<UPowerUpPrimaryDataAsset>>& GetMapsPowerUps() const noexcept
	{
		return MapPowerUps;
	}

	FORCEINLINE TArray<TSubclassOf<AWeapon>> GetPredefinedWeapon() const noexcept
	{
		return PredefinedWeapons;
	}

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(Type, GetFName());
	}

	FString GetIdentifierString() const
	{
		return GetPrimaryAssetId().ToString();
	}
};
