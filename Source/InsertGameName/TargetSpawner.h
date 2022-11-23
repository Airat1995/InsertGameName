// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "TargetPlaceActor.h"
#include "UObject/Object.h"
#include "TargetSpawner.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UTargetSpawner : public UObject
{
	GENERATED_BODY()

public:

	static TObjectPtr<UTargetSpawner> Make(const TObjectPtr<UObject> Parent, TArray<ATargetPlaceActor*> targetSpawnPositions, TSubclassOf<ATarget> targetType, const FMapDifficultyZones& DifficultyZones, float TargetHP);

	virtual void BeginPlay();
	virtual void StopPlay();

	UFUNCTION()
	void TargetDestroyed(float score);

	template< class UserClass >
	void SubscribeOnScoreCount(UserClass* Object, typename TBaseDynamicDelegate<FWeakObjectPtr, void, float>::template TMethodPtrResolver< UserClass >::FMethodPtr Func)
	{
		MainTarget->SubscribeToDestroy(Object, Func);
	}

private:

	UPROPERTY(EditAnywhere, Category = "Target", meta = (AllowPrivateAccess = true))
	TArray<ATargetPlaceActor*> TargetSpawnPositions;

	UPROPERTY(EditAnywhere, Category = "Target", meta = (AllowPrivateAccess = true))
	ATarget* MainTarget;
	
	void SpawnNextTarget();

	int CurrentTargetId;
};
