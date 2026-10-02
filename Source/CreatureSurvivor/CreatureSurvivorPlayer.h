#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

#include "CreatureSurvivorPlayer.generated.h"

UCLASS()
class CREATURESURVIVOR_API ACreatureSurvivorPlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ACreatureSurvivorPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* TopDownCamera;

	void MoveInput(const FInputActionValue& Value);

	void RotateToMouse();
};
