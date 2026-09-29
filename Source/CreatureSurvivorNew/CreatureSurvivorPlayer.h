#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "CreatureSurvivorPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

UCLASS()
class CREATURESURVIVORNEW_API ACreatureSurvivorPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACreatureSurvivorPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* TopDownCamera;

	void MoveInput(const FInputActionValue& Value);

};
