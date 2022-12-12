// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EldenCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRINGLIKE_API AEnemyCharacter : public AEldenCharacter
{
	GENERATED_BODY()

public:
	/*
	* Targeted Interface
	*/
	virtual void FocusBack(AActor* EnemyActor) override;
	virtual void UnTargeted() override;
};
