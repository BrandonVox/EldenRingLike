#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EldenRingLike/Types/Types.h"
#include "EldenAnimInstance.generated.h"

class ACharacter;

UCLASS()
class ELDENRINGLIKE_API UEldenAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ACharacter* Character;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsJumping = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating = false;

	/*
	* Strafe
	*/

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator StrafeRotation;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float StrafeValue;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EStrafeSide StrafeSide;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsTargeting = false;

public:
	FORCEINLINE void SetIsTargeting(const bool& Value) { bIsTargeting = Value; }
};
