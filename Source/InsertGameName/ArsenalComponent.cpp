// Fill out your copyright notice in the Description page of Project Settings.


#include "ArsenalComponent.h"

// Sets default values for this component's properties
UArsenalComponent::UArsenalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UArsenalComponent* UArsenalComponent::Make(UObject* Parent, const APlayerController* const Controller, UAnimInstance* const AnimInstance)
{
	UArsenalComponent* ArsenalComponent = NewObject<UArsenalComponent>(Parent);
	ArsenalComponent->PlayerController = Controller;
	ArsenalComponent->Anim = AnimInstance;
	return ArsenalComponent;
}

// Called when the game starts
void UArsenalComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UArsenalComponent::WearNextWeapon()
{
	if(CurrentWeapon == nullptr || CurrentWeapon->IsReloading())
		return;
	ActivateCurrentWeapon(false);
	CurrentWeaponIndex += 1;
	if(CurrentWeaponIndex >= Weapons.Num())
	{
		CurrentWeaponIndex = 0;
	}
	ActivateCurrentWeapon(true);
}

void UArsenalComponent::WearPreviousWeapon()
{
	if(CurrentWeapon == nullptr || CurrentWeapon->IsReloading())
		return;
	ActivateCurrentWeapon(false);
	CurrentWeaponIndex -= 1;
	if(CurrentWeaponIndex < 0)
	{
		CurrentWeaponIndex = Weapons.Num() - 1;
	}
	ActivateCurrentWeapon(true);
}

void UArsenalComponent::WearWeaponIndex(int newWeaponIndex)
{
	if(newWeaponIndex > 0 && newWeaponIndex < Weapons.Num())
	{
		ActivateCurrentWeapon(false);
		CurrentWeaponIndex = newWeaponIndex;
		ActivateCurrentWeapon(true);
	}
}

void UArsenalComponent::AttachNewWeapon(AWeapon* newWeapon)
{
	// // Attach the weapon to the First Person Character
	// RegisterComponent();
	Weapons.Add(newWeapon);
	CurrentWeapon = newWeapon;
	CurrentWeaponIndex = Weapons.Num() - 1;
	newWeapon->AttachWeapon(PlayerController, Anim);
}

void UArsenalComponent::StartFiring()
{
	if(CurrentWeapon !=nullptr)
		CurrentWeapon->Fire();
}

void UArsenalComponent::StopFiring()
{
	if(CurrentWeapon !=nullptr)
		CurrentWeapon->FireStop();
}

void UArsenalComponent::ActivateCurrentWeapon(bool activate)
{
	if(activate)
	{
		Weapons[CurrentWeaponIndex]->Wear(true);
		CurrentWeapon = Weapons[CurrentWeaponIndex];
	}
	else
	{
		Weapons[CurrentWeaponIndex]->Wear(false);
		CurrentWeapon = nullptr;
	}
}
