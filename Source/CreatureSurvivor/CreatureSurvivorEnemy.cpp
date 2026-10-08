// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureSurvivorEnemy.h"

void ACreatureSurvivorEnemy::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ACreatureSurvivorEnemy::CheckFireCondition, FireRate, true);

}

void ACreatureSurvivorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player)
	{
		RotateCharacter(Player->GetActorLocation());
	}
}

void ACreatureSurvivorEnemy::CheckFireCondition()
{
	if (Player)
	{
		Fire();
	}
}