#include "BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
{
	// Character does not rotate based on controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character does not rotate when moving
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh());
}

void ABaseCharacter::MoveCharacter(const FVector& Direction, float Scale)
{
	AddMovementInput(Direction, Scale);
}

void ABaseCharacter::RotateCharacter(const FVector& LookAtTarget)
{
	FVector DirectionToTarget = LookAtTarget - GetActorLocation();

	FRotator LookAtRotation = FRotator(0.0f, DirectionToTarget.Rotation().Yaw, 0.0f);

	FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
	SetActorRotation(InterpolatedRotation);
}

void ABaseCharacter::Fire()
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	if (Projectile)
	{
		Projectile->SetOwner(this);
	}
}
