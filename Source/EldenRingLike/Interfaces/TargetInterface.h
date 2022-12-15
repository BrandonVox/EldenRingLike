// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ELDENRINGLIKE_API ITargetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetLocation() = 0;

	virtual FVector EndLocationToFindTarget() = 0;

	virtual void StartFocusing(const bool& bDoTarget) = 0;

	virtual void SetControllerRotation(const FRotator& NewRotation) = 0;
	virtual void SetObjectRotation(const FRotator& NewRotation) = 0;

	virtual FRotator GetControllerRotation() = 0;
	virtual FRotator GetObjectRotation() = 0;

	virtual FRotator ControllerYawRotation() = 0;

	virtual float GetDistanceTo_Custom(AActor* OtherActor) = 0;

	virtual bool IsTargeting() = 0;

	virtual bool IsRolling() = 0;
	
};
