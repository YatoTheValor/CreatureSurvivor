// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureSurvivorGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "CreatureSurvivorEnemy.h"
#include "LevelingComponent.h"
#include "MobSpawner.h"

void ACreatureSurvivorGameMode::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(PlayerCharacter)
	{
		Player = Cast<ACreatureSurvivorPlayer>(PlayerCharacter);
		if(!Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to find Player Actor"));
		}
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

		if (Player)
		{
			Player->SetPlayerEnabled(true);
		}

		// Start all mob spawners
		TArray<AActor*> Spawners;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMobSpawner::StaticClass(),Spawners);

		for (AActor* Actor : Spawners)
		{
			AMobSpawner* Spawner = Cast<AMobSpawner>(Actor);

			if (Spawner)
			{
				Spawner->StartSpawning();
			}
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ACreatureSurvivorGameMode::ActorDied(AActor* DeadActor,AController* KillerController)
{
	if (DeadActor == Player)
	{
		Player->HandleDestruction();

		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		ScreenMessageWidget->SetMessageText("Defeat!");

		GetWorldTimerManager().SetTimer(GameOverTimerHandle,this,&ACreatureSurvivorGameMode::OnGameOverTimerTimeout,GameOverDelay,false);

		return;
	}

	ACreatureSurvivorEnemy* DeadEnemy =
		Cast<ACreatureSurvivorEnemy>(DeadActor);

	if (!DeadEnemy)
	{
		return;
	}

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
	UGameplayStatics::OpenLevel(
		this,
		FName(*UGameplayStatics::GetCurrentLevelName(this, true))
	);
}



