// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (GameMode)
	{
		CreatureSurvivorGameMode = Cast<ACreatureSurvivorGameMode>(GameMode);
	}
	
	UpdateHUD();
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	UpdateHUD();

	if (Health <= 0.0f && CreatureSurvivorGameMode)
	{
		CreatureSurvivorGameMode->ActorDied(DamagedActor, InstigatedBy);
	}
}

void UHealthComponent::UpdateHUD()
{
	if (!CreatureSurvivorGameMode ||
		!CreatureSurvivorGameMode->HUDWidget ||
		!CreatureSurvivorGameMode->Player ||
		GetOwner() != CreatureSurvivorGameMode->Player ||
		MaxHealth <= 0.0f)
	{
		return;
	}

	const float HealthPercent = Health / MaxHealth;
	CreatureSurvivorGameMode->HUDWidget->SetHealthBarPercent(HealthPercent);
}

