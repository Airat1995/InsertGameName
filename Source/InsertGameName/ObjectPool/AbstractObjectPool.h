// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolObjectFactory.h"

/**
 * 
 */
template<class Type,
			class = std::enable_if_t<std::is_base_of_v<UPoolObject, Type>>>
class INSERTGAMENAME_API AbstractObjectPool
{
	static constexpr uint8 Default_Pool_Size = 50;
public:
	explicit AbstractObjectPool(PoolObjectFactory<Type>& ObjectFactory): PoolSize(Default_Pool_Size), LastRequestedElement(0), bAllowGrowth(false), Factory(ObjectFactory)
	{
		/*
		 * Resize at pool initialization to prevent stutters in midgame and
		 * ensure that all objects will lay on line 
		 */
		InitializePool();
	}
	
	AbstractObjectPool(PoolObjectFactory<Type>& ObjectFactory, const int MaxElementsCount, const bool AllowGrowth = false): PoolSize(MaxElementsCount), LastRequestedElement(0), bAllowGrowth(AllowGrowth), Factory(ObjectFactory)
	{
		/*
		 * Resize at pool initialization to prevent stutters in midgame and
		 * ensure that all objects will lay on line 
		 */
		InitializePool();
	}

	virtual ~AbstractObjectPool()
	{
		for (auto Object : FreeObjectsArray)
		{
			if(Object != nullptr)
				Factory.Destroy(Object);
		}
		FreeObjectsArray.Empty();

		for (int RequestedIndex = 0; RequestedIndex < Default_Pool_Size; RequestedIndex++)
		{
			if(RequestedObjectsArray[RequestedIndex] != nullptr)
			{
				Factory.Destroy(RequestedObjectsArray[RequestedIndex]);
			}
		}
		RequestedObjectsArray.Empty();
	}

	Type* GetObjectInstance()
	{
		if(LastRequestedElement >= PoolSize)
		{
			if(!bAllowGrowth)
			{
				UE_LOG(LogTemp, Error, TEXT("Requested more elements than pool contain. Please resize it manually!"));
				return nullptr;
			}
			else
			{
				FreeObjectsArray.Add(Factory.Make());
				RequestedObjectsArray.SetNum(LastRequestedElement);
			}
		}

		Type* RequestedElement = FreeObjectsArray[LastRequestedElement];
		FreeObjectsArray[LastRequestedElement] = nullptr;
		RequestedObjectsArray.Add(RequestedElement);
		LastRequestedElement += 1;
		
		InitializeObject(RequestedElement);
		
		return RequestedElement;
	}

protected:

	/**
	 * Initialize object before returning it from the pool
	 */
	virtual void InitializeObject(Type* RequestedObject)
	{
		
	}

	/**
 	* Set all required data to object before returning it to the pool
 	*/
	virtual void DeinitializeObject(Type* ObjectToReturn)
	{
		
	}

	UFUNCTION()
	void ObjectReturn(UPoolObject* ObjectToReturn)
	{
		Type* CastedObject = static_cast<Type*>(ObjectToReturn);
		const int RequestedIndex = RequestedObjectsArray.Remove(CastedObject);
		if(RequestedIndex == -1)
		{
			UE_LOG(LogTemp, Error, TEXT("Trying to return object that wasnt requested from the pool!"));
			return;
		}
		
		LastRequestedElement -= 1;
		FreeObjectsArray[LastRequestedElement] = CastedObject;
		DeinitializeObject(CastedObject);
	}

private:

	void InitializePool()
	{
		FreeObjectsArray.SetNum(PoolSize);
		for (int Index = 0; Index < PoolSize; Index++)
		{
			Type* PoolObject = Factory.Make();
			PoolObject->OnPoolReturn.BindRaw(this, &AbstractObjectPool::ObjectReturn);
			DeinitializeObject(PoolObject);
			FreeObjectsArray[Index] = PoolObject;
		}
		RequestedObjectsArray.SetNum(PoolSize);
	}

	int PoolSize;
	int LastRequestedElement;
	bool bAllowGrowth;
	TArray<Type*> FreeObjectsArray;
	TArray<Type*> RequestedObjectsArray;

	PoolObjectFactory<Type>& Factory;
};
