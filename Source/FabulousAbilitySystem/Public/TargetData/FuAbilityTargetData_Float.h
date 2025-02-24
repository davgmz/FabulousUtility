﻿#pragma once

#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FuAbilityTargetData_Float.generated.h"

USTRUCT(BlueprintType, DisplayName = "Fu Float Target Data")
struct FABULOUSABILITYSYSTEM_API FFuAbilityTargetData_Float : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fabulous Utility")
	float Value{0.0f};

public:
	virtual UScriptStruct* GetScriptStruct() const override;

	virtual FString ToString() const override;

	bool NetSerialize(FArchive& Archive, UPackageMap* Map, bool& bSuccess);
};

template <>
struct TStructOpsTypeTraits<FFuAbilityTargetData_Float> : public TStructOpsTypeTraitsBase2<FFuAbilityTargetData_Float>
{
	enum
	{
		WithNetSerializer = true
	};
};

UCLASS()
class FABULOUSABILITYSYSTEM_API UFuFloatTargetDataUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Float Target Data Utility",
		Meta = (AutoCreateRefTerm = "TargetData", ReturnDisplayName = "Target Data Handle"))
	static FGameplayAbilityTargetDataHandle MakeFloatTargetData(const FFuAbilityTargetData_Float& TargetData);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Float Target Data Utility", Meta = (ReturnDisplayName = "Target Data"))
	static FFuAbilityTargetData_Float GetFloatTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, int32 Index);
};
