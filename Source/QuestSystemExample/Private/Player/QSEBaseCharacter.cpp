// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/QSEBaseCharacter.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"
#include "QuestSystemEntities/QSEBaseQuest.h"

DEFINE_LOG_CATEGORY_STATIC(LogQSEBaseCharacter, All, All);

AQSEBaseCharacter::AQSEBaseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AQSEBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) return;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AQSEBaseQuest::StaticClass(), Quests);
	UE_LOG(LogQSEBaseCharacter, Warning, TEXT("Quests setted"));
	if (Quests.Num() == 0)
	{
		UE_LOG(LogQSEBaseCharacter, Warning, TEXT("There are no quest in the world"));
	}
}

void AQSEBaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AQSEBaseCharacter::Interact);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AQSEBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AQSEBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AQSEBaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AQSEBaseCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AQSEBaseCharacter::Interact()
{
	FHitResult HitResult;
	
	FVector TraceStart = FollowCamera->GetComponentLocation();
	FVector TraceEnd = TraceStart + FollowCamera->GetForwardVector() * 500.0f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	if (!GetWorld()) return;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 1.0f);

	const auto Actor = HitResult.GetActor();
	if (!Actor) return;
	UE_LOG(LogQSEBaseCharacter, Warning, TEXT("Actor is hitted by trace"));
}

