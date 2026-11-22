// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSpawner.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AMobSpawner::AMobSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMobSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (bStartSpawningOnBeginPlay)
	{
		StartSpawning();
	}
	
}

void AMobSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopSpawning();

	Super::EndPlay(EndPlayReason);
}

void AMobSpawner::StartSpawning()
{
	if (!GetWorld())
	{
		return;
	}

	if (GetWorldTimerManager().IsTimerActive(SpawnTimerHandle))
	{
		return;
	}

	if (SpawnInterval <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("MobSpawner: SpawnInterval must be greater than zero!"));
		return;
	}

	TrySpawnEnemy();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this,&AMobSpawner::TrySpawnEnemy,SpawnInterval,true);
}

void AMobSpawner::StopSpawning()
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void AMobSpawner::TrySpawnEnemy()
{
	if (!EnemyClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("MobSpawner: No EnemyClass assigned!"));
		return;
	}

	if(GetAliveEnemyCount() >= MaxAliveEnemies)
	{
		return;
	}
	
	SpawnEnemy();
}

void AMobSpawner::SpawnEnemy()
{

	if (!GetWorld() || !EnemyClass) return;

	FVector SpawnLocation = GetRandomSpawnLocation();

	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ACharacter* SpawnedEnemy = GetWorld()->SpawnActor<ACharacter>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedEnemy)
	{
		AliveEnemies.Add(SpawnedEnemy);

		SpawnedEnemy->OnDestroyed.AddDynamic(this, &AMobSpawner::OnEnemyDestroyed);
	}

}

FVector AMobSpawner::GetRandomSpawnLocation() const
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (!PlayerCharacter)
	{
		return GetActorLocation();
	}

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	// Random direction around the player.
	FVector2D RandomDirection = FMath::RandPointInCircle(1.0f);

	RandomDirection.Normalize();

	// Random radius with uniform distribution across the area.
	float MinRadiusSquared = FMath::Square(MinSpawnRadius);
	float MaxRadiusSquared = FMath::Square(MaxSpawnRadius);

	float RandomRadius = FMath::Sqrt(FMath::FRandRange(MinRadiusSquared, MaxRadiusSquared));

	FVector SpawnOffset(RandomDirection.X * RandomRadius, RandomDirection.Y * RandomRadius, 0.0f);

	return PlayerLocation + SpawnOffset;
}

void AMobSpawner::OnEnemyDestroyed(AActor* DestroyedActor)
{
	AliveEnemies.RemoveAll([DestroyedActor](const TObjectPtr<ACharacter>& Enemy)
		{
			return !IsValid(Enemy) || Enemy == DestroyedActor;
		}
	);
}

int32 AMobSpawner::GetAliveEnemyCount() const
{
	int32 Count = 0;

	for (const TObjectPtr<ACharacter>& Enemy : AliveEnemies)
	{
		if (IsValid(Enemy))
		{
			++Count;
		}
	}

	return Count;
}



