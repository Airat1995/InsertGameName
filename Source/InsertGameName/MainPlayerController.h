// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/InputSettings.h"
#include "InsertGameNameCharacter.h"
#include "Character/PBPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class AInsertGameNameGameMode;
/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMainPlayerController();

protected:
	
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	void Jump();
	void StopJumping();

	void Crouching();
	void UnCrouching();

	void StartSprint();
	void StopSprint();

	void StartPlay();
	
	void OnPrimaryActionStart();
	void OnPrimaryActionEnd();
	
	void SwitchNextWeapon();
	void SwitchPreviousWeapon();
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void AddControllerYawInput(float Value);
	void AddControllerPitchInput(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);

private:
	/* 
	* Configures input for touchscreen devices if there is a valid touch interface for doing so 
	*
	* @param	InputComponent	The input component pointer to bind controls to
	* @returns true if touch controls were enabled.
	*/
	bool EnableTouchscreenMovement();

	UPROPERTY()
	TObjectPtr<AInsertGameNameCharacter> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<AInsertGameNameGameMode> InsertGameNameGameMode;

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
};