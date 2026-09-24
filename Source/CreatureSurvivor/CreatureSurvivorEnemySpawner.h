#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreatureSurvivorEnemySpawner.generated.h"

class ACreatureSurvivorEnemy;

UCLASS()
class ACreatureSurvivorEnemySpawner : public AActor
{
	GENERATED_BODY()

public:

	ACreatureSurvivorEnemySpawner();

protected:

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<ACreatureSurvivorEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnRadius = 1000.0f;

	FTimerHandle SpawnTimerHandle;

	virtual void BeginPlay() override;

	void SpawnEnemy();
};