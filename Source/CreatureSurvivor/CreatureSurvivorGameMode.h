// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CreatureSurvivorPlayer.h"

#include "CreatureSurvivorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CREATURESURVIVOR_API ACreatureSurvivorGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ACreatureSurvivorPlayer* Player;
	int32 EnemyCount;

	void ActorDied(AActor* DeadActor);
};
