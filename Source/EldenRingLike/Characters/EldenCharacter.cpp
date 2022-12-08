#include "EldenCharacter.h"
#include "GameFramework/SpringArmComponent.h" // CameraBoom
#include "Camera/CameraComponent.h" // FollowCamera

#include "GameFramework/CharacterMovementComponent.h" // GetCharacterMovement()
#include "EldenRingLike/CustomComponents/CombatComponent.h" // CombatComponent

#include "Animation/AnimInstance.h"

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
	GetCharacterMovement()->MaxWalkSpeed = 700;

	// Components
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

}

void AEldenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Pressed
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEldenCharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AEldenCharacter::AttackButtonPressed);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AEldenCharacter::RollButtonPressed);

	// Axises
	PlayerInputComponent->BindAxis("MoveForward", this, &AEldenCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEldenCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AEldenCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AEldenCharacter::Turn);
}

void AEldenCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (CombatComponent)
	{
		CombatComponent->SetCharacter(this);
	}
}

void AEldenCharacter::Combo()
{
	if (CombatComponent)
	{
		CombatComponent->Combo();
	}
}

void AEldenCharacter::ResetCombat()
{
	if (CombatComponent)
	{
		CombatComponent->ResetCombat();
	}
}

void AEldenCharacter::RotateCharacter(const float& DeltaTime)
{
	if (CombatComponent)
	{
		CombatComponent->RotateCharacter(DeltaTime);
	}
}

void AEldenCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Landed"));


	// Cancel attack when landing
	if (GetMesh() == nullptr || CombatComponent == nullptr)
	{
		return;
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (CombatComponent->IsAttacking() && AnimInstance)
	{
		AnimInstance->StopAllMontages(0.3f);
		CombatComponent->ResetCombat();
	}
	

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

void AEldenCharacter::Jump()
{
	if (CombatComponent && CombatComponent->IsAttacking())
	{
		return;
	}
	Super::Jump();
}

/*
* Actions
* Pressed
*/
void AEldenCharacter::AttackButtonPressed()
{
	if (CombatComponent == nullptr)
	{
		return;
	}

	if (GetCharacterMovement() && GetCharacterMovement()->IsFalling())
	{
		CombatComponent->RequestAttack(EAttackType::EAT_AirAttack);
	}
	else
	{
		CombatComponent->RequestAttack(EAttackType::EAT_NormalAttack);
	}
}

void AEldenCharacter::RollButtonPressed()
{
	if (CombatComponent)
	{
		CombatComponent->RequestRoll();
	}
}

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




