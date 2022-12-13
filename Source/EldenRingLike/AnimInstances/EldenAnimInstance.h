#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EldenRingLike/Types/Types.h"
#include "EldenAnimInstance.generated.h"

class AEldenCharacter;

UCLASS()
class ELDENRINGLIKE_API UEldenAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AEldenCharacter* EldenCharacter;

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

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsDefending = false;

public:
	/*
	* Setters
	*/
	FORCEINLINE void SetIsTargeting(const bool& bValue) { bIsTargeting = bValue; }
	FORCEINLINE void SetIsDefending(bool bValue) { bIsDefending = bValue; }
};
