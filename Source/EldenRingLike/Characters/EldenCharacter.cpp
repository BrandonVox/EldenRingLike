#include "EldenCharacter.h"

#include "EldenRingLike/AnimInstances/EldenAnimInstance.h"
#include "EldenRingLike/CustomComponents/CombatComponent.h"
#include "EldenRingLike/CustomComponents/TargetComponent.h"
#include "EldenRingLike/CustomComponents/CollisionComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEldenCharacter::AEldenCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	/*
	* Configs
	*/
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



void AEldenCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (CombatComponent)
	{
		CombatComponent->SetCharacter(this);
	}

	if (TargetComponent)
	{
		TargetComponent->SetFocusObject(Cast<ITargetInterface>(this));
	}

	if (CollisionComponent)
	{
		CollisionComponent->SetAttackableObject(Cast<IAttackInterface>(this));
	}
}

void AEldenCharacter::BeginPlay()
{
	Super::BeginPlay();

	// EldenAnimInstance
	if (GetMesh())
	{
		EldenAnimInstance = Cast<UEldenAnimInstance>(GetMesh()->GetAnimInstance());
	}

	if (CollisionComponent)
	{
		CollisionComponent->HitActorDelegate.AddDynamic(this, &AEldenCharacter::OnHitActor);
	}

	OnTakePointDamage.AddDynamic(this, &AEldenCharacter::OnTakeDamage);
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


	if (CombatComponent && CombatComponent->IsAttacking_Air())
	{
		StopAllMontages();
		ResetCombat();
	}

}

/*
* Target Interface
*/
FVector AEldenCharacter::GetLocation()
{
	return GetActorLocation(); 
}

FVector AEldenCharacter::EndLocationToFindTarget()
{
	return FVector();
}

void AEldenCharacter::StartFocusing(const bool& bDoTarget)
{
	if (EldenAnimInstance)
	{
		EldenAnimInstance->SetIsTargeting(bDoTarget);
	}
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = !bDoTarget;
	}
}

void AEldenCharacter::SetControllerRotation(const FRotator& NewRotation)
{
	if (Controller)
	{
		Controller->SetControlRotation(NewRotation);
	}
}

void AEldenCharacter::SetObjectRotation(const FRotator& NewRotation)
{
	SetActorRotation(NewRotation);
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

bool AEldenCharacter::IsRolling()
{
	if (CombatComponent == nullptr)
	{
		return false;
	}
	return CombatComponent->IsRolling();
}

FRotator AEldenCharacter::GetControllerRotation()
{
	return Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator;
}

FRotator AEldenCharacter::GetObjectRotation()
{
	return GetActorRotation();
}

FRotator AEldenCharacter::ControllerYawRotation()
{
	return FRotator(
		GetActorRotation().Pitch,
		GetControllerRotation().Yaw,
		GetActorRotation().Roll);
}

FVector AEldenCharacter::GetTargetLocation()
{
	if (GetMesh() == nullptr)
	{
		return FVector();
	}

	return GetMesh()->GetSocketLocation(TargetSocketName);
}

/*
* Attack Interface
*/
void AEldenCharacter::Combo()
{
	if (CombatComponent)
	{
		CombatComponent->Combo();
	}
}

void AEldenCharacter::ChargeAttack()
{
	if (CombatComponent)
	{
		CombatComponent->ChargeAttack();
	}
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


void AEldenCharacter::Guard()
{
	if (CombatComponent == nullptr || EldenAnimInstance == nullptr)
		return;

	if (CombatComponent->CanGuard())
	{
		CombatComponent->ToggleGuard(true);
		EldenAnimInstance->SetIsDefending(true);
	}
}

void AEldenCharacter::EndGuard()
{
	PlayAnimMontage(EndGuardMontage);
}

void AEldenCharacter::Jump()
{
	if (IsAttacking())
	{
		StopAllMontages();
		ResetCombat();
	}

	if (IsDefending() && CombatComponent && EldenAnimInstance)
	{
		CombatComponent->ToggleGuard(false);
		ResetCombat();
		EldenAnimInstance->SetIsDefending(false);
	}

	Super::Jump();
}

void AEldenCharacter::OnHitActor(const FHitResult& HitResult)
{
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

// when some one hit you
void AEldenCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
	FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName,
	FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{

	if (IsDefending())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SwordDeflectImpact, HitLocation);
		UGameplayStatics::PlaySoundAtLocation(this, SwordDeflectSound, HitLocation);
		PlayAnimMontage(GuardReactMontage);
		if (CombatComponent)
		{
			CombatComponent->SetCombatState(ECombatState::ECS_Guard);
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("defending hit"));
		return;
	}

	// If not defending but hitted weapon
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, BoneName.ToString());
	if (BoneName == TEXT("weapon_r"))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SwordDeflectImpact, HitLocation);
		UGameplayStatics::PlaySoundAtLocation(this, SwordDeflectSound, HitLocation);
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

bool AEldenCharacter::IsAttacking() const
{
	if (CombatComponent == nullptr)
	{
		return false;
	}
	return CombatComponent->IsAttacking();
}

bool AEldenCharacter::IsDefending() const
{
	if (CombatComponent == nullptr)
	{
		return false;
	}
	return CombatComponent->IsDefending();
}

void AEldenCharacter::StopAllMontages(const float& BlendOutSeconds)
{
	if (EldenAnimInstance)
	{
		EldenAnimInstance->StopAllMontages(BlendOutSeconds);
	}
}




