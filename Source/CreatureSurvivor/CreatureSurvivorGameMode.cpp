// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureSurvivorGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "CreatureSurvivorEnemy.h"
#include "CreatureSurvivorGameInstance.h"
#include "LevelingComponent.h"

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

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageClass);
		if (ScreenMessageWidget)
		{
			ScreenMessageWidget->AddToPlayerScreen();
			ScreenMessageWidget->SetMessageText("Get Ready!");
		}
	}

	CountdownSeconds = CountdownDelay;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACreatureSurvivorGameMode::OnCountdownTimerTimeout, 1.0f, true);

	HUDWidget = CreateWidget<UHUDWidget>(PlayerController, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToPlayerScreen();
		UpdatePlayerLevelHUD();
	}
}

void ACreatureSurvivorGameMode::OnCountdownTimerTimeout()
{
	CountdownSeconds -= 1;

	if (CountdownSeconds > 0)
	{
		ScreenMessageWidget->SetMessageText(FString::FromInt(CountdownSeconds));
	}
	else if (CountdownSeconds == 0)
	{
		ScreenMessageWidget->SetMessageText("Go!");
		Player->SetPlayerEnabled(true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ACreatureSurvivorGameMode::ActorDied(AActor* DeadActor, AController* KillerController)
{
	bool IsGameOver = false;

	if (DeadActor == Player)
	{
		Player->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		ACreatureSurvivorEnemy* DeadEnemy = Cast<ACreatureSurvivorEnemy>(DeadActor);
		if (DeadEnemy)
		{
			DeadEnemy->HandleDestruction();

			if (Player && KillerController == Player->GetController())
			{
				ULevelingComponent* LevelingComponent = Player->FindComponentByClass<ULevelingComponent>();
				if (LevelingComponent)
				{
					LevelingComponent->AddExperience(DeadEnemy->ExperienceReward);
					UpdatePlayerLevelHUD();
				}
			}

			EnemyCount--;
			if (EnemyCount == 0)
			{
				IsGameOver = true;
				IsVictory = true;
			}
		}
	}

	if (IsGameOver)
	{
		FString GameOverString = IsVictory ? "Victory!" : "Defeat!";

		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		ScreenMessageWidget->SetMessageText(GameOverString);

		FTimerHandle FireTimerHandle;
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ACreatureSurvivorGameMode::OnGameOverTimerTimeout, GameOverDelay, false);
	}
}

void ACreatureSurvivorGameMode::UpdatePlayerLevelHUD()
{
	if (!Player || !HUDWidget)
	{
		return;
	}

	ULevelingComponent* LevelingComponent = Player->FindComponentByClass<ULevelingComponent>();
	if (!LevelingComponent || LevelingComponent->ExperienceToNextLevel <= 0)
	{
		return;
	}

	const float ExperiencePercent =
		static_cast<float>(LevelingComponent->CurrentExperience) /
		static_cast<float>(LevelingComponent->ExperienceToNextLevel);

	HUDWidget->SetExperienceBarPercent(ExperiencePercent);
	HUDWidget->SetLevelText(LevelingComponent->CurrentLevel);
	HUDWidget->SetExperienceText(LevelingComponent->CurrentExperience,LevelingComponent->ExperienceToNextLevel);
}

void ACreatureSurvivorGameMode::OnGameOverTimerTimeout()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UCreatureSurvivorGameInstance* CreatureSurvivorGameInstance = Cast<UCreatureSurvivorGameInstance>(GameInstance);
		if (CreatureSurvivorGameInstance)
		{
			if (IsVictory)
			{
				CreatureSurvivorGameInstance->LoadNextLevel();
			}
			else
			{
				CreatureSurvivorGameInstance->RestartCurrentLevel();
			}
		}
	}
}



