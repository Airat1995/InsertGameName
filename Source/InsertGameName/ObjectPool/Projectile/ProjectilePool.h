// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractObjectPool.h"
#include "InsertGameNameProjectile.h"

/**
	* 
	*/
class INSERTGAMENAME_API ProjectilePool : public AbstractObjectPool<AInsertGameNameProjectile>
{
public:
	explicit ProjectilePool(PoolObjectFactory<AInsertGameNameProjectile>& ObjectFactory)
		: AbstractObjectPool<AInsertGameNameProjectile>(ObjectFactory)
	{
	}

	ProjectilePool(PoolObjectFactory<AInsertGameNameProjectile>& ObjectFactory, int MaxElementsCount, bool AllowGrowth)
		: AbstractObjectPool<AInsertGameNameProjectile>(ObjectFactory, MaxElementsCount, AllowGrowth)
	{
	}

	virtual  ~ProjectilePool() override
	{
		
	}

protected:

	virtual void InitializeObject(AInsertGameNameProjectile* RequestedObject) override
	{
		AbstractObjectPool<AInsertGameNameProjectile>::InitializeObject(RequestedObject);
		RequestedObject->SetActorEnableCollision(true);
		RequestedObject->SetActorHiddenInGame(false);
		RequestedObject->SetMove(true);
	}
	
	virtual void DeinitializeObject(AInsertGameNameProjectile* ObjectToReturn) override
	{
		AbstractObjectPool<AInsertGameNameProjectile>::DeinitializeObject(ObjectToReturn);
		ObjectToReturn->SetActorEnableCollision(false);
		ObjectToReturn->SetActorHiddenInGame(true);
		ObjectToReturn->SetMove(false);
	}
};
