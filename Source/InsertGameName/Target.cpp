// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

ATarget* ATarget::Make(const UObject* Parent, UClass* TargetType, FMapDifficultyZones DifficultyZones, float MaxHealth)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ATarget* Target = Parent->GetWorld()->SpawnActor<ATarget>(TargetType, FVector3d::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	Target->CurrentZones = DifficultyZones;
	Target->MaxHP = MaxHealth;
	Target->CurrentHP = MaxHealth; 
	return Target;
}

// Sets default values for this component's properties
ATarget::ATarget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you tdon't need them.
	SetActorTickEnabled(false);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	DefaultCollisionProfileName = MeshComponent->GetCollisionProfileName();
}

// Called when the game starts
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	Center = MeshComponent->Bounds.GetBox().GetCenter();
	Distance = MeshComponent->Bounds.GetBox().GetSize().X;
	CurrentHP = MaxHP;
}

void ATarget::Damage(float Damage, FVector3d WorldDamagePosition)
{
	FVector3d localPosition = GetTransform().InverseTransformPosition(WorldDamagePosition);
	//Remove depth because pivot point in the center of the target
	localPosition.Y = 0;
	const float damageDistance = FVector3d::Distance(FVector::Zero(), localPosition);
	const float distancePercent = damageDistance/Distance;

	for (const auto it : CurrentZones.Zones)
	{
		if(it.MinRadius < distancePercent && it.MaxRadius >= distancePercent)
		{
			const float scoreCount = Damage * it.PointsScale;
			Score += scoreCount;
			CurrentHP -= Damage;
			TargetHit.Broadcast(CurrentHP);

			if (CurrentHP <= 0)
				TargetDestroyed.Broadcast(Score);
			GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, FString::Printf(TEXT("DAMAGE DEALT %f"), scoreCount));
			break;
		}
	}
}

void ATarget::ResetTarget(const FTransform& Transform)
{
	SetActorTransform(Transform);
	CurrentHP = MaxHP;
	Score = 0;
}

void ATarget::Enable(bool bEnabled) const
{
	RootComponent->SetVisibility(bEnabled, true);
	MeshComponent->SetCollisionProfileName(bEnabled ? DefaultCollisionProfileName : NoCollisionProfileName);
}
