#include "CreatureSurvivorEnemySpawner.h"
#include "CreatureSurvivorEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

ACreatureSurvivorEnemySpawner::ACreatureSurvivorEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACreatureSurvivorEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ACreatureSurvivorEnemySpawner::SpawnEnemy,
		SpawnInterval,
		true
	);
}

void ACreatureSurvivorEnemySpawner::SpawnEnemy()
{
	if (EnemyClass == nullptr)
	{
		return;
	}

	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);

	if (Player == nullptr)
	{
		return;
	}

	const FVector PlayerLocation = Player->GetActorLocation();

	const FVector SpawnLocation = PlayerLocation + FVector(
		FMath::RandRange(-SpawnRadius, SpawnRadius),
		FMath::RandRange(-SpawnRadius, SpawnRadius),
		0.0f
	);

	FActorSpawnParameters SpawnParameters;

	GetWorld()->SpawnActor<ACreatureSurvivorEnemy>(
		EnemyClass,
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParameters
	);
}