// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelingComponent.h"

// Sets default values for this component's properties
ULevelingComponent::ULevelingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevelingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULevelingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULevelingComponent::AddExperience(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	CurrentExperience += Amount;

	while (CurrentExperience >= ExperienceToNextLevel)
	{
		CurrentExperience -= ExperienceToNextLevel;
		CurrentLevel++;

		ExperienceToNextLevel = FMath::FloorToInt(ExperienceToNextLevel * 1.25f);
	}
}

