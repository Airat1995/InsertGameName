// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDifficultyZones.generated.h"

USTRUCT(BlueprintType)
struct FZone
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PointsScale;
};

USTRUCT(BlueprintType)
struct FMapDifficultyZones
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FZone> Zones;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DifficultyScoreMultiplier;
};