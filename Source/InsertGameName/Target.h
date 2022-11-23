// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDifficultyZones.h"
#include "Components/BoxComponent.h"
#include "Target.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetHit, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetDestroyed, float);

UCLASS()
class INSERTGAMENAME_API ATarget : public AActor
{
	GENERATED_BODY()

	inline static const FName NoCollisionProfileName = FName("No Collision");

public:

	static ATarget* Make(const UObject* Parent, UClass* TargetType, FMapDifficultyZones DifficultyZones, float MaxHealth);
	
	ATarget();

	template< class UserClass >
	void SubscribeToHit(UserClass* Object, typename TBaseDynamicDelegate<FWeakObjectPtr, void>::template TMethodPtrResolver< UserClass >::FMethodPtr Func )
	{
		TargetHit.AddUFunction(Object, Func);
	}

	template< class UserClass >
	void SubscribeToDestroy(UserClass* Object, typename TBaseDynamicDelegate<FWeakObjectPtr, void, float>::template TMethodPtrResolver< UserClass >::FMethodPtr Func )
	{
		TargetDestroyed.AddUObject(Object, Func);
	}

	/** Check is applied position valid to damage target and deal it if it is. Returns was damage applied to the target */
	void Damage(float Damage, FVector3d WorldDamagePosition);

	void ResetTarget(const FTransform& Transform);

	void Enable(bool bEnabled) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	UStaticMeshComponent* MeshComponent;
	
	FOnTargetHit TargetHit;
	FOnTargetDestroyed TargetDestroyed;

private:
	float Score;
	float CurrentHP;
	float MaxHP;
	float Distance;
	FName DefaultCollisionProfileName;
	FVector3d Center;
	FMapDifficultyZones CurrentZones;

};