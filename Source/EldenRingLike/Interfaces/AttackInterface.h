
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAttackInterface : public UInterface
{
	GENERATED_BODY()
};


class ELDENRINGLIKE_API IAttackInterface
{
	GENERATED_BODY()

public:
	virtual FVector StartHitLocation() = 0;
	virtual FVector EndHitLocation() = 0;

	virtual void SetupHitDetection() = 0;
	virtual void DetectHit() = 0;

};
