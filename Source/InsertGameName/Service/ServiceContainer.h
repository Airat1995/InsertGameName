// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Service.h"
#include "Misc/TypeContainer.h"
#include "UObject/Object.h"
#include "Misc/TypeContainer.h"
#include "ServiceContainer.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UServiceContainer : public UObject
{
	GENERATED_BODY()

public:

	template<typename Type,
	         std::enable_if_t<std::is_base_of_v<IService, Type>>* = nullptr>
	Type& GetService()
	{
		 return IOCContainer.GetInstance<Type>().Get();
	}

	template<typename BaseType, typename ConcreteType,
				std::enable_if_t<std::is_base_of_v<BaseType, ConcreteType>>* = nullptr>
	void RegisterService()
	{
		IOCContainer.RegisterClass<BaseType, ConcreteType>(ETypeContainerScope::Process);
	}

	template<typename Type,
			std::enable_if_t<std::is_base_of_v<IService, Type>>* = nullptr>
	void UnregisterService()
	{
		IOCContainer.Unregister<Type>();
	}

private:

	TTypeContainer<> IOCContainer;
};