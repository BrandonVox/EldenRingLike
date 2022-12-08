#include "EldenAnimInstance.h"
#include "GameFramework/Character.h" // Character
#include "GameFramework/CharacterMovementComponent.h" // Character->GetCharacterMovement()

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
}
