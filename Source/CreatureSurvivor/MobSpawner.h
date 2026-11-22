// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MobSpawner.generated.h"

UCLASS()
class CREATURESURVIVOR_API AMobSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMobSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Spawning | Enemy")
	TSubclassOf<ACharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning | Settings")
	float SpawnInterval = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning | Settings")
	int32 MaxAliveEnemies = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float MinSpawnRadius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float MaxSpawnRadius = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	bool bStartSpawningOnBeginPlay = true;

	UPROPERTY()
	TArray<TObjectPtr<ACharacter>> AliveEnemies;

	FTimerHandle SpawnTimerHandle;

	void TrySpawnEnemy();

	FVector GetRandomSpawnLocation() const;

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);

public:

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StopSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnEnemy();

	UFUNCTION(BlueprintPure, Category = "Spawner")
	int32 GetAliveEnemyCount() const;
};
