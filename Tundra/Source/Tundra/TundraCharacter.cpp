#include "TundraCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Controllers/TundraController.h"
#include "Tundra/Widgets/PlayerHUD.h"
#include "Kismet/KismetMathLibrary.h"

ATundraCharacter::ATundraCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 0.f;
	GetCharacterMovement()->AirControl = 0.0;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 300.f;
	GetCharacterMovement()->MaxAcceleration = 0;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ATundraCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(ATundraController* controller = Cast<ATundraController>(Controller))
	{
		controller->SetInputMode(FInputModeGameAndUI{});
		controller->SetShowMouseCursor(true);
	}
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (IsLocallyControlled() && PlayerHUDAsset)
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(GetController<ATundraController>(), PlayerHUDAsset.Get());
		PlayerHUD->AddToPlayerScreen();
	}
}

void ATundraCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATundraCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATundraCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATundraCharacter::Look);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATundraCharacter::Zoom);
		EnhancedInputComponent->BindAction(PitchAction, ETriggerEvent::Triggered, this, &ATundraCharacter::PitchCamera);
		EnhancedInputComponent->BindAction(FreeLookAction, ETriggerEvent::Triggered, this, &ATundraCharacter::FreeLook);
		EnhancedInputComponent->BindAction(FreeLookAction, ETriggerEvent::Completed, this, &ATundraCharacter::StopFreeLook);
	}
}

void ATundraCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator controlRotation = GetControlRotation();
		const FRotator bokenRotation {0,controlRotation.Yaw,0};
		AddMovementInput(UKismetMathLibrary::GetForwardVector(bokenRotation), MovementVector.Y);

		
		AddMovementInput(UKismetMathLibrary::GetRightVector(bokenRotation), MovementVector.X);
	}
}

void ATundraCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (IsFreeLook)
		{
			AddControllerPitchInput(LookAxisVector.Y);
			AddControllerYawInput(LookAxisVector.X);
		}
	}

	
}

void ATundraCharacter::PitchCamera(const FInputActionValue& Value)
{
	float LookAxisVector = Value.Get<float>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector);
	}
}

void ATundraCharacter::FreeLook()
{
	IsFreeLook = true;

	if(ATundraController* controller = Cast<ATundraController>(Controller))
	{
		controller->SetInputMode(FInputModeGameOnly{});
		controller->SetShowMouseCursor(false);
	}
}

void ATundraCharacter::StopFreeLook()
{
	IsFreeLook = false;

	if(ATundraController* controller = Cast<ATundraController>(Controller))
	{
		FInputModeGameAndUI inputMode{};
		inputMode.SetHideCursorDuringCapture(false);
		controller->SetInputMode(inputMode);
		controller->SetShowMouseCursor(true);
	}
}

void ATundraCharacter::Zoom(const FInputActionValue& Value)
{
	float zoomAxis = -Value.Get<float>();

	if (Controller != nullptr)
	{
		CameraBoom->TargetArmLength = FMath::Clamp((zoomAxis * 10.0f) + CameraBoom->TargetArmLength, MinZoom, 2000);

		GetCharacterMovement()->MaxWalkSpeed = (CameraBoom->TargetArmLength / MinZoom) * InitialMoveSpeed;
	}
}




