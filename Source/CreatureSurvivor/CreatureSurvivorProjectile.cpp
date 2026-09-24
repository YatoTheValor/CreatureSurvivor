#include "CreatureSurvivorProjectile.h"
#include "Components/SphereComponent.h"

ACreatureSurvivorProjectile::ACreatureSurvivorProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(
		TEXT("CollisionComponent")
	);

	RootComponent = CollisionComponent;

	CollisionComponent->SetSphereRadius(10.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ACreatureSurvivorProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ACreatureSurvivorProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector ForwardDirection = GetActorForwardVector();

	AddActorWorldOffset(
		ForwardDirection * Speed * DeltaTime,
		true
	);
}