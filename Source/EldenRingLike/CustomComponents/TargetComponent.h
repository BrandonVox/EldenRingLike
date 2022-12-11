
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EldenRingLike/Interfaces/TargetInterface.h"
#include "EldenRingLike/Interfaces/TargetedInterface.h"
#include "TargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDENRINGLIKE_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Target();
	void UnTarget();

protected:
	virtual void BeginPlay() override;

private:
	void LookTarget(const float& DeltaTime);
	void FindTarget();

private:
	ITargetInterface* TargetableObject = nullptr;
	ITargetedInterface* TargetedObject = nullptr;



	bool bIsTargeting = false;


	// Trace
	UPROPERTY(EditAnywhere)
	float TraceRadius = 20.f;

	UPROPERTY(EditAnywhere)
	float TraceLength = 500.f;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditAnywhere)
	bool bDebug;

	UPROPERTY(EditAnywhere)
	float Offset_Z = 50.f;

	UPROPERTY(EditAnywhere)
	float MaxTargetLength = 500.f;

	UPROPERTY(EditAnywhere)
	float RotateObjectSpeed = 2.f;

	UPROPERTY()
	FRotator CurrentRotation_Object;

public:	
	FORCEINLINE void SetTargetableObject(ITargetInterface* Value) { TargetableObject = Value; }
	FORCEINLINE const bool IsTargeting() { return bIsTargeting; }
};
