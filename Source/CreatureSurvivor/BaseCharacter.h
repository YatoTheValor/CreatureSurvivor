#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class CREATURESURVIVOR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	void MoveCharacter(const FVector& Direction, float Scale);

public:
	UPROPERTY(VisibleAnywhere, Category="Combat")
	USceneComponent* ProjectileSpawnPoint;

	void RotateCharacter(const FVector& LookAtTarget);

	void Fire();
};