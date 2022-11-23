// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetPlaceActor.h"
#include "Engine/LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "MapActor.generated.h"

UCLASS()
class INSERTGAMENAME_API AMapActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapActor();

	FORCEINLINE TArray<ATargetPlaceActor*> GetTargetPoints()
	{
		if(!bCached)
			FillTargetPoints();
		return TargetPoints;
	}

protected:

	void FillTargetPoints();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<ATargetPlaceActor*> TargetPoints;
	
	bool bCached = false;
};
