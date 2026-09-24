// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatureSurvivorEnemy.generated.h"

UCLASS()
class ACreatureSurvivorEnemy : public ACharacter
{
	GENERATED_BODY()

public:

	ACreatureSurvivorEnemy();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float Health = 100.0f;
};
