// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolObject.h"

/**
 * 
 */
template<class PoolObjectType,
			class = std::enable_if_t<std::is_base_of_v<UPoolObject, PoolObjectType>>>
class INSERTGAMENAME_API PoolObjectFactory
{
public:
	virtual ~PoolObjectFactory()
	{
	}

	virtual PoolObjectType* Make() = 0;

	virtual void Destroy(PoolObjectType* Object) = 0;
	
};
