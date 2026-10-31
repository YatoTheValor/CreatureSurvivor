// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CREATURESURVIVOR_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ExperienceBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ExperienceText;

	void SetHealthBarPercent(float NewPercent);

	void SetExperienceBarPercent(float NewPercent);

	void SetLevelText(int32 NewLevel);

	void SetExperienceText(int32 CurrentExperience, int32 ExperienceToNextLevel);

};
