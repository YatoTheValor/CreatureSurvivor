#include "CreatureSurvivorPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACreatureSurvivorPlayer::ACreatureSurvivorPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	// Character does not rotate based on controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character does not rotate when moving
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	// Create the Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

	// Don't let the camera boom collide with objects
	CameraBoom->bDoCollisionTest = false;

	// Don't inherit the character's rotation
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	// Create camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);

	TopDownCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ACreatureSurvivorPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}


// Called to bind functionality to input
void ACreatureSurvivorPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ACreatureSurvivorPlayer::MoveInput);
	}
}

void ACreatureSurvivorPlayer::MoveInput(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();

	AddMovementInput(FVector::ForwardVector, InputVector.Y);
	AddMovementInput(FVector::RightVector, InputVector.X);
}



