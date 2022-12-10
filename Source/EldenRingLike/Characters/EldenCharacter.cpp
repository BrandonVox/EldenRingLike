#include "EldenCharacter.h"
#include "GameFramework/SpringArmComponent.h" // CameraBoom
#include "Camera/CameraComponent.h" // FollowCamera

#include "GameFramework/CharacterMovementComponent.h" // GetCharacterMovement()
#include "EldenRingLike/CustomComponents/CombatComponent.h" // CombatComponent
#include "EldenRingLike/CustomComponents/TargetComponent.h" // TargetComponent
#include "EldenRingLike/CustomComponents/CollisionComponent.h"

#include "EldenRingLike/AnimInstances/EldenAnimInstance.h"


#include "Kismet/GameplayStatics.h"

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

	/*
	* Components
	*/
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	TargetComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetComponent"));
	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComponent"));
}

void AEldenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Pressed
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEldenCharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AEldenCharacter::AttackButtonPressed);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AEldenCharacter::RollButtonPressed);
	PlayerInputComponent->BindAction("Target", IE_Pressed, this, &AEldenCharacter::TargetButtonPressed);

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

	if (TargetComponent)
	{
		TargetComponent->SetTargetableObject(Cast<ITargetInterface>(this));
	}

	if (CollisionComponent)
	{
		CollisionComponent->SetAttackableObject(Cast<IAttackInterface>(this));
	}
}

void AEldenCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComponent)
	{
		CollisionComponent->HitActorDelegate.AddDynamic(this, &AEldenCharacter::OnHitActor);
	}

	OnTakePointDamage.AddDynamic(this, &AEldenCharacter::OnTakeDamage);
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

/*
* Target Interface
*/
FVector AEldenCharacter::GetLocation()
{
	return GetActorLocation(); 
}

FVector AEldenCharacter::GetCameraDirection()
{
	if (FollowCamera == nullptr)
	{
		return FVector();
	}
	return FollowCamera->GetForwardVector();
}

void AEldenCharacter::SetupTarget(const bool& bDoTarget)
{
	if (GetMesh() == nullptr)
	{
		return;
	}

	UEldenAnimInstance* EldenAnimInstance = Cast<UEldenAnimInstance>(GetMesh()->GetAnimInstance());
	if (EldenAnimInstance)
	{
		EldenAnimInstance->SetIsTargeting(bDoTarget);
	}

	if (bDoTarget)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AEldenCharacter::SetControllerRotation(const FRotator& NewRotation)
{
	if (Controller)
	{
		Controller->SetControlRotation(NewRotation);
	}
}

float AEldenCharacter::GetDistanceTo(const AActor* OtherActor)
{
	return GetDistanceTo(OtherActor);
}

bool AEldenCharacter::IsTargeting()
{
	if (TargetComponent == nullptr)
	{
		return false;
	}

	return TargetComponent->IsTargeting();
}

FVector AEldenCharacter::GetTargetLocation()
{
	if (GetMesh() == nullptr)
	{
		return FVector();
	}

	return GetMesh()->GetSocketLocation(TargetSocketName);
}

FVector AEldenCharacter::StartHitLocation()
{
	if (GetMesh() == nullptr)
	{
		return FVector();
	}
	return GetMesh()->GetSocketLocation(StartHitSocket);
}

FVector AEldenCharacter::EndHitLocation()
{
	if (GetMesh() == nullptr)
	{
		return FVector();
	}
	return GetMesh()->GetSocketLocation(EndHitSocket);
}

void AEldenCharacter::SetupHitDetection()
{
	if (CollisionComponent)
	{
		CollisionComponent->ClearHittedActors();
	}
	
}

void AEldenCharacter::DetectHit()
{
	if (CollisionComponent)
	{
		CollisionComponent->DetectHit();
	}
}



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

void AEldenCharacter::TargetButtonPressed()
{
	if (TargetComponent == nullptr)
	{
		return;
	}

	if (TargetComponent->IsTargeting())
	{
		TargetComponent->UnTarget();
	}
	else
	{
		TargetComponent->Target();
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



void AEldenCharacter::OnHitActor(const FHitResult& HitResult)
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "Hit Actor");
	UGameplayStatics::ApplyPointDamage(
		HitResult.GetActor(),
		20.f, //GetDamageOfLastAttack(),
		GetActorForwardVector(),
		HitResult,
		GetController(),
		this,
		UDamageType::StaticClass()
	);
}

void AEldenCharacter::OnTakeDamage(AActor* DamagedActor, float Damage,
	AController* InstigatedBy, FVector HitLocation,
	UPrimitiveComponent* FHitComponent, FName BoneName,
	FVector ShotFromDirection, const UDamageType* DamageType,
	AActor* DamageCauser)
{

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, BoneName.ToString());
	if (BoneName == TEXT("weapon_r"))
	{
		// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "SWORD STRIKE");

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SwordStrikeImpact, HitLocation, FRotator());
		UGameplayStatics::PlaySoundAtLocation(this, SwordStrikeSound, HitLocation);
		return;
	}
	
	
	HandleHitted(HitLocation, ShotFromDirection);

}

void AEldenCharacter::HandleHitted(const FVector& HitLocation, const FVector& ShotFromDirection)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpact, HitLocation, FRotator());
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, HitLocation);
	PlayAnimMontage(HitMontage_Front);

	if (CombatComponent)
	{
		CombatComponent->SetCombatState(ECombatState::ECS_Hitted);
	}

}
