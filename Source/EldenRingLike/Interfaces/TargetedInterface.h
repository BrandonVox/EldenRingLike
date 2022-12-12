
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetedInterface.generated.h"

UINTERFACE(MinimalAPI)
class UTargetedInterface : public UInterface
{
	GENERATED_BODY()
};


class ELDENRINGLIKE_API ITargetedInterface
{
	GENERATED_BODY()

public:
	virtual FVector GetTargetLocation() = 0;
	virtual void FocusBack(AActor* EnemyActor);
	virtual void UnTargeted();
};
