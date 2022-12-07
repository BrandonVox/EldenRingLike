#include "EldenCharacter.h"
#include "GameFramework/SpringArmComponent.h" // CameraBoom
#include "Camera/CameraComponent.h" // FollowCamera

#include "GameFramework/CharacterMovementComponent.h" // GetCharacterMovement()

AEldenCharacter::AEldenCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	// Camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Character Configs
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 1.75f;
	GetCharacterMovement()->AirControl = 0.35f;

}

void AEldenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Pressed
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACombatCharacter::AttackButtonPressed);

	// Axises
	PlayerInputComponent->BindAxis("MoveForward", this, &AEldenCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEldenCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AEldenCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AEldenCharacter::Turn);
}


void AEldenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AEldenCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

/*
* Axes
*/
void AEldenCharacter::MoveForward(float Value)
{
	const FRotator& ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AEldenCharacter::MoveRight(float Value)
{
	const FRotator& ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AEldenCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AEldenCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}




