// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureSurvivorGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "CreatureSurvivorEnemy.h"

void ACreatureSurvivorGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreatureSurvivorEnemy::StaticClass(), Enemies);
	EnemyCount = Enemies.Num();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(PlayerCharacter)
	{
		Player = Cast<ACreatureSurvivorPlayer>(PlayerCharacter);
		if(!Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to find Player Actor"));
		}
	}

	int32 LoopIndex = 0;
	while (LoopIndex < EnemyCount)
	{
		AActor* EnemyActor = Enemies[LoopIndex];
		if (EnemyActor)
		{
			ACreatureSurvivorEnemy* Enemy = Cast<ACreatureSurvivorEnemy>(EnemyActor);
			if(Enemy && Player)
			{
				Enemy->Player = Player;
			}
		}

		LoopIndex++;
	}
}

void ACreatureSurvivorGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Player)
	{
		UE_LOG(LogTemp, Display, TEXT("Player died, Defeated!"));
	}
	else
	{
		ACreatureSurvivorEnemy* DeadEnemy = Cast<ACreatureSurvivorEnemy>(DeadActor);
		if (DeadEnemy)
		{
			//DeadTower
			DeadEnemy->Destroy();
			UE_LOG(LogTemp, Display, TEXT(" A Enemy just died"));
			EnemyCount--;
			if (EnemyCount == 0)
			{
				UE_LOG(LogTemp, Display, TEXT("All enemies destroyed, You won!"));
			}
		}
	}
}

