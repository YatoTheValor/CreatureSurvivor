// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"

#include "CreatureSurvivorPlayer.h"

#include "CreatureSurvivorEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CREATURESURVIVOR_API ACreatureSurvivorEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	ACreatureSurvivorPlayer* Player;
};
