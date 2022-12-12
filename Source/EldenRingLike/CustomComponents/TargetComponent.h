
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

	void RequestFocus();
	void UnFocus();
	void UnTargeted();

	// Enemy is focused and want to focus back
	void FocusBack(AActor* EnemyActor);

protected:
	virtual void BeginPlay() override;

private:
	void LookTarget(const float& DeltaTime);
	void FindTarget();

private:
	ITargetInterface* FocusObject = nullptr;
	ITargetedInterface* TargetObject = nullptr;

	bool bIsTargeting = false;

	// Trace
	UPROPERTY(EditAnywhere)
	float TraceRadius = 15.f;

	UPROPERTY(EditAnywhere)
	float TraceLength = 1500.f;

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
	float ObjectRotateSpeed = 6.f;
	UPROPERTY(EditAnywhere)
	float ControllerRotateSpeed = 11.f;

	UPROPERTY()
	FRotator ObjectRotation;
	UPROPERTY()
	FRotator ControllerRotation;

public:
	/*
	* Getters
	*/
	FORCEINLINE float GetTraceLength() const { return TraceLength; }
	FORCEINLINE bool IsTargeting() const { return bIsTargeting; }
	/*
	* Setters
	*/
	FORCEINLINE void SetFocusObject(ITargetInterface* Value) { FocusObject = Value; }
};
