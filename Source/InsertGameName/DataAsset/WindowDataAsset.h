// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/AbstractWindowController.h"
#include "Interface/AbstractWindowPresenter.h"
#include "Interface/AbstractWindowView.h"

#include "WindowDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UWindowDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset", meta = (AllowPrivateAccess = true))
	FPrimaryAssetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window", meta = (AllowPrivateAccess = true))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window", meta = (AllowPrivateAccess = true, AssetBundles = "Window"))
	TSoftClassPtr<UAbstractWindowView> View;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window", meta = (AllowPrivateAccess = true, AssetBundles = "Window"))
	TSoftClassPtr<UAbstractWindowPresenter> Preset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window", meta = (AllowPrivateAccess = true, AssetBundles = "Window"))
	TSoftClassPtr<UAbstractWindowController> Controller;

public:

	FName GetWindowName() const noexcept
	{
		return Name;
	}

	TSoftClassPtr<UAbstractWindowView> GetWindowView() const noexcept
	{
		return View;
	}

	TSoftClassPtr<UAbstractWindowPresenter> GetWindowPresenter() const noexcept
	{
		return Preset;
	}

	TSoftClassPtr<UAbstractWindowController> GetWindowController() const noexcept
	{
		return Controller;
	}

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(Type, Name);
	}

	FString GetIdentifierString() const
	{
		return GetPrimaryAssetId().ToString();
	}
};
