// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureSurvivorEnemy.h"
#include "Kismet/GameplayStatics.h"

void ACreatureSurvivorEnemy::BeginPlay()
{
    Super::BeginPlay();

    // Find the player
    Player = Cast<ACreatureSurvivorPlayer>(
        UGameplayStatics::GetPlayerCharacter(this, 0)
    );

    if (!Player)
    {
        UE_LOG(LogTemp,Error,TEXT("Enemy could not find player!"));

        return;
    }

    // Start shooting timer
    if (FireRate > 0.0f)
    {
        GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ACreatureSurvivorEnemy::CheckFireCondition, FireRate, true);
    }
    
}

void ACreatureSurvivorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!IsValid(Player))
    {
        Player = Cast<ACreatureSurvivorPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
    }

    if (IsValid(Player))
    {
        RotateCharacter(Player->GetActorLocation());
    }
}

void ACreatureSurvivorEnemy::CheckFireCondition()
{

    if (!IsValid(Player))
    {
        Player = Cast<ACreatureSurvivorPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
    }

	if (IsValid(Player))
	{
		Fire();
	}
}

void ACreatureSurvivorEnemy::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}