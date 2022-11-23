// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InsertGameNameProjectile.h"
#include "PoolObjectFactory.h"

/**
* 
*/
class INSERTGAMENAME_API ProjectileFactory : public PoolObjectFactory<AInsertGameNameProjectile>
{
public:
	
	ProjectileFactory(TObjectPtr<UWorld> SpawnWorld, TSubclassOf<AInsertGameNameProjectile> Projectile)
	{
		ProjectileSpawnWorld = SpawnWorld;
		SpawnProjectile = Projectile;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	}

	virtual ~ProjectileFactory() override
	{
		ProjectileSpawnWorld = nullptr;
	}

	virtual AInsertGameNameProjectile* Make() override
	{
		AInsertGameNameProjectile* Projectile = ProjectileSpawnWorld->SpawnActor<AInsertGameNameProjectile>(SpawnProjectile, FVector(-1000, -1000, -1000), FRotator::ZeroRotator, ActorSpawnParams);
		Projectile->SetMove(false);
		return Projectile;
	}
	
	virtual void Destroy(AInsertGameNameProjectile* Object) override
	{
		Object->MarkAsGarbage();
	}

private:

	FActorSpawnParameters ActorSpawnParams;
	TObjectPtr<UWorld> ProjectileSpawnWorld;
	TSubclassOf<AInsertGameNameProjectile> SpawnProjectile;
};
