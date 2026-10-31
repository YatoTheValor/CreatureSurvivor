// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CreatureSurvivorPlayer.h"
#include "ScreenMessage.h"
#include "HUDWidget.h"

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;

	UScreenMessage* ScreenMessageWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UHUDWidget* HUDWidget;

	ACreatureSurvivorPlayer* Player;
	int32 EnemyCount;

	float IsVictory = false;

	UPROPERTY(EditAnywhere)
	int32 CountdownDelay = 3;

	int32 CountdownSeconds;

	FTimerHandle CountdownTimerHandle;

	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.0f;

	void ActorDied(AActor* DeadActor, AController* KillerController);

	void UpdatePlayerLevelHUD();

	void OnGameOverTimerTimeout();

	void OnCountdownTimerTimeout();
};
