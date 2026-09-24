// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreatureSurvivorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

#include "TimerManager.h"
#include "CreatureSurvivorProjectile.h"
#include "CreatureSurvivorEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

ACreatureSurvivorCharacter::ACreatureSurvivorCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create the camera boom component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create the camera component
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACreatureSurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&ACreatureSurvivorCharacter::AutoAttack,
		AttackInterval,
		true
	);

	// stub
}

void ACreatureSurvivorCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	// stub
}

void ACreatureSurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&ACreatureSurvivorCharacter::Move
		);
	}
}

void ACreatureSurvivorCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();

	const FRotator YawRotation(
		0.0f,
		ControlRotation.Yaw,
		0.0f
	);

	const FVector ForwardDirection =
		FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection =
		FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ACreatureSurvivorCharacter::AutoAttack()
{
	TArray<AActor*> Enemies;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ACreatureSurvivorEnemy::StaticClass(),
		Enemies
	);

	if (Enemies.Num() == 0)
	{
		return;
	}

	ACreatureSurvivorEnemy* ClosestEnemy = nullptr;
	float ClosestDistance = FLT_MAX;

	for (AActor* EnemyActor : Enemies)
	{
		const float Distance = FVector::Dist(
			GetActorLocation(),
			EnemyActor->GetActorLocation()
		);

		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestEnemy = Cast<ACreatureSurvivorEnemy>(EnemyActor);
		}
	}

	if (ClosestEnemy == nullptr || ProjectileClass == nullptr)
	{
		return;
	}

	const FVector StartLocation = GetActorLocation();

	const FVector Direction =
		(ClosestEnemy->GetActorLocation() - StartLocation).GetSafeNormal();

	const FRotator ProjectileRotation =
		Direction.Rotation();

	FActorSpawnParameters SpawnParameters;

	GetWorld()->SpawnActor<ACreatureSurvivorProjectile>(
		ProjectileClass,
		StartLocation,
		ProjectileRotation,
		SpawnParameters
	);
}
