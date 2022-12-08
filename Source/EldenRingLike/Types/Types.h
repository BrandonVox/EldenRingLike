#pragma once
UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_Free UMETA(DisplayName = "Free"),
	ECS_Attack UMETA(DisplayName = "Attack"),
	ECS_Roll UMETA(DisplayName = "Roll")
};


UENUM(BlueprintType)
enum class EAttackType : uint8
{
	EAT_NormalAttack UMETA(DisplayName = "NormalAttack"),
	EAT_AirAttack UMETA(DisplayName = "AirAttack"),
	EAT_ChargeAttack UMETA(DisplayName = "ChargeAttack")
};