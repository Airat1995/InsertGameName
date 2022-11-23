// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanHitWeapon.h"

#include "Target.h"

AScanHitWeapon::AScanHitWeapon()
{
	SetActorTickEnabled(true);
}

void AScanHitWeapon::Firing()
{
	Super::Firing();
	FHitResult HitResult;
	FCollisionQueryParams HitParams;
	const FVector SpawnLocation = MeshComponent->GetSocketLocation(WeaponDataAsset->MuzzleSocket);
	const FVector EndLocation = SpawnLocation + MeshComponent->GetRightVector() * HIT_DISTANCE;
	if(CurrentWorld->LineTraceSingleByChannel(HitResult, SpawnLocation, EndLocation, ECC_Visibility, HitParams))
	{
		bool isTargetActor = HitResult.GetActor()->IsA<ATarget>();
		if(isTargetActor)
		{
			ATarget* target = Cast<ATarget>(HitResult.GetActor());
			target->Damage(ScanHitWeaponDataAsset->GetDamage(), HitResult.Location);
		}
	}
}

void AScanHitWeapon::AttachWeapon(const APlayerController* const Controller, UAnimInstance* const AnimInstance)
{
	Super::AttachWeapon(Controller, AnimInstance);
	ScanHitWeaponDataAsset = Cast<UScanHitWeaponDataAsset>(WeaponDataAsset);
	check(ScanHitWeaponDataAsset != nullptr);
}
