#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreatureSurvivorProjectile.generated.h"

class USphereComponent;

UCLASS()
class ACreatureSurvivorProjectile : public AActor
{
	GENERATED_BODY()

public:

	ACreatureSurvivorProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Damage = 25.0f;

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};