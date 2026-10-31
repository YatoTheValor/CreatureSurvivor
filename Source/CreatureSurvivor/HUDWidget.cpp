// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::SetHealthBarPercent(float NewPercent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(FMath::Clamp(NewPercent, 0.0f, 1.0f));
	}
}

void UHUDWidget::SetExperienceBarPercent(float NewPercent)
{
	if (ExperienceBar)
	{
		ExperienceBar->SetPercent(FMath::Clamp(NewPercent, 0.0f, 1.0f));
	}
}

void UHUDWidget::SetLevelText(int32 NewLevel)
{
	if (LevelText)
	{
		LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level %d"), NewLevel)));
	}
}

void UHUDWidget::SetExperienceText(int32 CurrentExperience, int32 ExperienceToNextLevel)
{
	if (ExperienceText)
	{
		ExperienceText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d XP"), CurrentExperience, ExperienceToNextLevel)));
	}
}
