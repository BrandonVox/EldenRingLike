
#include "EldenAnimInstance.h"
#include "EldenRingLike/Characters/EldenCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UEldenAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EldenCharacter = Cast<AEldenCharacter>(TryGetPawnOwner());

	// listen elden?????
}

void UEldenAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (EldenCharacter == nullptr)
	{
		EldenCharacter = Cast<AEldenCharacter>(TryGetPawnOwner());
	}

	if (EldenCharacter == nullptr)
	{
		return;
	}

	// Speed
	FVector Velocity = EldenCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	// Jump
	bIsJumping = EldenCharacter->IsJumpProvidingForce();
	bIsInAir = EldenCharacter->GetCharacterMovement()->IsFalling();
	
	// Accelerating
	bIsAccelerating = EldenCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;

	/*
	* Strafe
	*/
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
	const FRotator& AimRotation = EldenCharacter->GetBaseAimRotation();

	if (Speed > 0.f)
	{
		StrafeValue = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
	
	//FString TheFloatStr = FString::SanitizeFloat(StrafeValue);
	//if (Character->IsLocallyControlled())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TheFloatStr);
	//}

	// StrafeSide
	if (StrafeValue > 70.f && StrafeValue < 110.f)
	{
		StrafeSide = EStrafeSide::ESS_Right;
	}
	else if (StrafeValue > -110 && StrafeValue < - 70.f)
	{
		StrafeSide = EStrafeSide::ESS_Left;
	}
	
	else if (StrafeValue > -20.f && StrafeValue < 20.f)
	{
		StrafeSide = EStrafeSide::ESS_Forward;
	}

	// FR
	else if (StrafeValue >= 20.f && StrafeValue <= 70.f)
	{
		StrafeSide = EStrafeSide::ESS_ForwardRight;
	}

	// FL
	else if (StrafeValue >= -70.f && StrafeValue <= -20.f)
	{
		StrafeSide = EStrafeSide::ESS_ForwardLeft;
	}

	// BR
	else if (StrafeValue >= 110.f && StrafeValue <= 160.f)
	{
		StrafeSide = EStrafeSide::ESS_BackwardRight;
	}

	// BL
	else if (StrafeValue >= -160.f && StrafeValue <= -110.f)
	{
		StrafeSide = EStrafeSide::ESS_BackwardLeft;
	}

	else
	{
		StrafeSide = EStrafeSide::ESS_Backward;
	}
}
