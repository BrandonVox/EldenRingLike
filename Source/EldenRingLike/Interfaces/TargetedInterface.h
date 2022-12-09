// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetedInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetedInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ELDENRINGLIKE_API ITargetedInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetTargetLocation() = 0;
};
