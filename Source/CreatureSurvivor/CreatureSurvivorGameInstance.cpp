// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureSurvivorGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UCreatureSurvivorGameInstance::ChangeLevel(int32 Index)
{
	if (Index > 0 && Index <= LastLevelIndex)
	{
		CurrentLevelIndex = Index;

		FString LevelNameString = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *LevelNameString);
	}
}

void UCreatureSurvivorGameInstance::LoadNextLevel()
{
	if (CurrentLevelIndex < LastLevelIndex)
	{
		ChangeLevel(CurrentLevelIndex + 1);
	}
	else
	{
		RestartGame();
	}
}

void UCreatureSurvivorGameInstance::RestartCurrentLevel()
{
	ChangeLevel(CurrentLevelIndex);
}

void UCreatureSurvivorGameInstance::RestartGame()
{
	ChangeLevel(1);
}
