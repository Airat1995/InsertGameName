// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"


TObjectPtr<UTargetSpawner> UTargetSpawner::Make(const TObjectPtr<UObject> Parent, TArray<ATargetPlaceActor*> targetSpawnPositions, TSubclassOf<ATarget> targetType, const FMapDifficultyZones& DifficultyZones, float TargetHP)
{
	const TObjectPtr<UTargetSpawner> TargetSpawner = NewObject<UTargetSpawner>(Parent);
	
	TargetSpawner->TargetSpawnPositions = targetSpawnPositions;

	TargetSpawner->MainTarget = ATarget::Make(Parent, targetType.Get(), DifficultyZones, TargetHP);
	TargetSpawner->MainTarget->Enable(false);
	TargetSpawner->CurrentTargetId = 0;
	TargetSpawner->MainTarget->SubscribeToDestroy(TargetSpawner.Get(), &UTargetSpawner::TargetDestroyed);

	return TargetSpawner;
}

void UTargetSpawner::BeginPlay()
{
	MainTarget->Enable(true);
	SpawnNextTarget();
}

void UTargetSpawner::StopPlay()
{
	MainTarget->Enable(false);
}

void UTargetSpawner::TargetDestroyed(float score)
{
	SpawnNextTarget();
}

void UTargetSpawner::SpawnNextTarget()
{
	const FTransform NewTargetPosition = TargetSpawnPositions[CurrentTargetId]->GetSpawnTargetPosition();
	MainTarget->ResetTarget(NewTargetPosition);
	CurrentTargetId++;
	CurrentTargetId = CurrentTargetId % TargetSpawnPositions.Num();
}


