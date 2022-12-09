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


UENUM(BlueprintType)
enum class EStrafeSide : uint8
{
	ESS_Forward UMETA(DisplayName = "Forward"),
	ESS_Backward UMETA(DisplayName = "Backward"),
	ESS_Right UMETA(DisplayName = "Right"),
	ESS_Left UMETA(DisplayName = "Left"),

	ESS_ForwardRight UMETA(DisplayName = "ForwardRight"),
	ESS_ForwardLeft UMETA(DisplayName = "ForwardLeft"),
	ESS_BackwardRight UMETA(DisplayName = "BackwardRight"),
	ESS_BackwardLeft UMETA(DisplayName = "BackwardLeft")
};