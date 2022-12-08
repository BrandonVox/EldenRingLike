#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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
	
};
