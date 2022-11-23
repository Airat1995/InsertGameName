// Copyright Epic Games, Inc. All Rights Reserved.

#include "InsertGameNameGameMode.h"

#include "MapActor.h"
#include "ServiceContainer.h"
#include "Main/MainWindowFactory.h"
#include "WindowService/AbstractWindowService.h"
#include "WindowService/MainWindowService.h"


AInsertGameNameGameMode::AInsertGameNameGameMode()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	GameStateClass = AArenaGameState::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	AssetLoadingState = TMap<FPrimaryAssetType, EAssetLoadingState>();
	AssetLoadingState.Add(UMapAssetManager::TargetAssetType, EAssetLoadingState::NotLoading);
	AssetLoadingState.Add(UMapAssetManager::MapAssetType, EAssetLoadingState::NotLoading);
	AssetLoadingState.Add(UMapAssetManager::PowerUpAssetType, EAssetLoadingState::NotLoading);

	MapDataLoadDelegate.BindUObject(this, &AInsertGameNameGameMode::MapAssetsLoaded);
	TargetDataAssetLoaded.BindUObject(this, &AInsertGameNameGameMode::TargetLoaded);
	PowerUpsAssetsLoaded.BindUObject(this, &AInsertGameNameGameMode::PowerUpsLoaded);
}

void AInsertGameNameGameMode::AssignPredefinedWeapons(const UMapDataAsset* LoadedMapDataAsset) const
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AInsertGameNameCharacter* Character = Cast<AInsertGameNameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	for (const auto Weapon : LoadedMapDataAsset->GetPredefinedWeapon())
	{
		AWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(Weapon.Get(), FVector3d::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
		Character->AttachWeapon(SpawnedWeapon);
	}
}

void AInsertGameNameGameMode::LoadTargets(const UMapDataAsset* LoadedMapDataAsset, UMapAssetManager& AssetManager)
{
	const TSoftObjectPtr<UTargetDataAsset> TargetDataAsset = LoadedMapDataAsset->GetLevelTargetInfo();
	AssetManager.LoadTargetData(TargetDataAsset->GetPrimaryAssetId(), TargetDataAssetLoaded);
	AssetLoadingState[UMapAssetManager::TargetAssetType] = EAssetLoadingState::Loading;
}

void AInsertGameNameGameMode::LoadPowerUps(const UMapDataAsset* LoadedMapDataAsset, UMapAssetManager& AssetManager)
{
	const TArray<TSoftObjectPtr<UPowerUpPrimaryDataAsset>>& PowerUpsDataAsset = LoadedMapDataAsset->GetMapsPowerUps();
	TArray<FPrimaryAssetId> PowerUpsAssetsId;
	for (const auto PowerUpAsset : PowerUpsDataAsset)
	{
		PowerUpsAssetsId.Add(PowerUpAsset->GetPrimaryAssetId());
	}
	AssetManager.LoadPowerUpsData(PowerUpsAssetsId, PowerUpsAssetsLoaded);
	AssetLoadingState[UMapAssetManager::PowerUpAssetType] = EAssetLoadingState::Loading;
}

void AInsertGameNameGameMode::MapAssetsLoaded(const UMapDataAsset* LoadedMapDataAsset)
{
	AssetLoadingState[UMapAssetManager::MapAssetType] = EAssetLoadingState::Loaded;
	UMapAssetManager& AssetManager = UMapAssetManager::Get();

	TArray<ATargetPlaceActor*> PlaceActors;
	SetTimer(LoadedMapDataAsset->GetLevelTime());

	AssignPredefinedWeapons(LoadedMapDataAsset);
	LoadTargets(LoadedMapDataAsset, AssetManager);
	LoadPowerUps(LoadedMapDataAsset, AssetManager);
}

void AInsertGameNameGameMode::TargetLoaded(const UTargetDataAsset* TargetDataAsset)
{
	AssetLoadingState[UMapAssetManager::TargetAssetType] = EAssetLoadingState::Loaded;
	AMapActor* MapActor = Cast<AMapActor>(GetWorld()->GetLevelScriptActor());

	const TObjectPtr<UInsertGameNameInstance> GameInstance = Cast<UInsertGameNameInstance>(GetGameInstance());
	const EDifficulty Difficulty = GameInstance->GetSelectedDifficulty();
	ScoreCounter->SetDifficulty(TargetDataAsset->GetZones()[Difficulty]);
	TargetSpawner = UTargetSpawner::Make(this, MapActor->GetTargetPoints(), TargetDataAsset->GetTargetType(), TargetDataAsset->GetZones()[Difficulty], TargetDataAsset->GetHealth());
	TargetSpawner->SubscribeOnScoreCount(this, &AInsertGameNameGameMode::ScoreCount);
}

void AInsertGameNameGameMode::PowerUpsLoaded(const TArray<UPowerUpPrimaryDataAsset*> PowerUpPrimaryDataAssets)
{
	PowerUpSystem = UPowerUpSystem::Make(this, GameTimer, ScoreCounter);
	for (auto PowerUpDataAsset : PowerUpPrimaryDataAssets)
	{
		PowerUpSystem->AddPowerUp(PowerUpDataAsset);
	}
	AssetLoadingState[UMapAssetManager::PowerUpAssetType] = EAssetLoadingState::Loaded;
}

void AInsertGameNameGameMode::SetTimer(float time)
{
	GameTimer->SetTimer(time);
}

void AInsertGameNameGameMode::AddTime(float time)
{
	GameTimer->AddTime(time);
}

void AInsertGameNameGameMode::ScoreCount(float Score)
{
	PowerUpSystem->ScoreTriggered(Score);
	ScoreCounter->AddScore(Score);
}

void AInsertGameNameGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GameTimer->Tick(DeltaSeconds);
	PowerUpSystem->Tick(DeltaSeconds);
}

void AInsertGameNameGameMode::BeginPlay()
{
	Super::BeginPlay();
	UMapAssetManager& AssetManager = UMapAssetManager::Get();

	UServiceContainer* ServiceContainer = NewObject<UServiceContainer>();
	ServiceContainer->RegisterService<AbstractWindowService, UMainWindowService>();
	AbstractWindowService& WindowService = ServiceContainer->GetService<AbstractWindowService>();

	TArray<TObjectPtr<UWindowDataAsset>> WindowDataAssets = AssetManager.GetAllWindows();
	
	FMainWindowFactory* MainWindowFactory = new FMainWindowFactory(GetWorld(), WindowDataAssets[0]);
	WindowService.RegisterWindowFactory(MainWindowFactory);

	WindowService.OpenWindow(UMainWindowController::StaticClass());
	
	
	PrimaryActorTick.SetTickFunctionEnable(false);
	ScoreCounter = UScoreCounter::Make(this);
	GameTimer = UGlobalTimer::Make(this);
	
	
	const TObjectPtr<UInsertGameNameInstance> GameInstance = Cast<UInsertGameNameInstance>(GetGameInstance());
	const TObjectPtr<UMapDataAsset> MapDataAsset = GameInstance->GetMapDataAsset();
	AssetManager.LoadMapData(MapDataAsset->GetPrimaryAssetId(), MapDataLoadDelegate);
	AssetLoadingState[UMapAssetManager::MapAssetType] = EAssetLoadingState::Loading;
} 

void AInsertGameNameGameMode::StartPlay()
{
	Super::StartPlay();
	if(!AllAssetsLoaded())
		return;
	bGameStarted = true;
	SubscribeOnTimerEnd(this, &AInsertGameNameGameMode::OnTimerEnd);
	GameTimer->Reset();
	GameTimer->Start();
	TargetSpawner->BeginPlay();
	PrimaryActorTick.SetTickFunctionEnable(true);
}

void AInsertGameNameGameMode::OnTimerEnd()
{
	TargetSpawner->StopPlay();
	bGameStarted = false;
	PrimaryActorTick.SetTickFunctionEnable(false);
}
