// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class INSERTGAMENAME_API UPoolObject
{
	DECLARE_DELEGATE_OneParam(FPoolReturnObject, UPoolObject*)

public:
	virtual ~UPoolObject() = default;

	/**
	* This function MUST be called in order to return object to assigned pool
	*/
	void ReturnToPool()
	{
		OnPoolReturn.Execute(this);
	}
	
	// template<typename UserClass, typename FunctorType>
	// void SubscribeToPoolReturn(UserClass* Object, FunctorType&& InFunctor)
	// {
	// 	// No need to rebound onpoolreturn 
	// 	if(OnPoolReturn.IsBound())
	// 		return;
	// 	OnPoolReturn.BindRaw(Object, InFunctor);
	// }
	FPoolReturnObject OnPoolReturn;
protected:

	/**
	 * This method used to fully destroy object
	 */
	virtual void InternalDestroy() = 0;
	
private:

};
