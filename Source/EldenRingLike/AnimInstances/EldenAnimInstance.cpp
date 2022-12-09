#include "EldenAnimInstance.h"
#include "GameFramework/Character.h" // Character
#include "GameFramework/CharacterMovementComponent.h" // Character->GetCharacterMovement()
#include "Kismet/KismetMathLibrary.h"

void UEldenAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacter>(TryGetPawnOwner());
}

void UEldenAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
	{
		Character = Cast<ACharacter>(TryGetPawnOwner());
	}

	if (Character == nullptr)
	{
		return;
	}

	// Speed
	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	// Jump
	bIsJumping = Character->IsJumpProvidingForce();
	bIsInAir = Character->GetCharacterMovement()->IsFalling();
	
	// Accelerating
	bIsAccelerating = Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;

	/*
	* Strafe
	*/
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
	const FRotator& AimRotation = Character->GetBaseAimRotation();

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
