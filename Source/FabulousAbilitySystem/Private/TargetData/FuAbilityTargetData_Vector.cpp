#include "TargetData/FuAbilityTargetData_Vector.h"

#include "FuMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FuAbilityTargetData_Vector)

bool FFuAbilityTargetData_Vector::HasOrigin() const
{
	return true;
}

FTransform FFuAbilityTargetData_Vector::GetOrigin() const
{
	return FTransform{Vector};
}

UScriptStruct* FFuAbilityTargetData_Vector::GetScriptStruct() const
{
	return StaticStruct();
}

FString FFuAbilityTargetData_Vector::ToString() const
{
	return FString{FU_GET_TYPE_STRING(FFuAbilityTargetData_Vector)};
}

bool FFuAbilityTargetData_Vector::NetSerialize(FArchive& Archive, UPackageMap* Map, bool& bSuccess)
{
	bSuccess = true;

	bSuccess &= SerializePackedVector<100, 30>(Vector, Archive);

	return bSuccess;
}

FGameplayAbilityTargetDataHandle UFuVectorTargetDataUtility::MakeVectorTargetData(const FFuAbilityTargetData_Vector& TargetData)
{
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	TargetDataHandle.Data.Emplace(MakeShared<FFuAbilityTargetData_Vector>(TargetData));

	return TargetDataHandle;
}

FFuAbilityTargetData_Vector UFuVectorTargetDataUtility::GetVectorTargetData(
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, const int32 Index)
{
	if (!TargetDataHandle.Data.IsValidIndex(Index) ||
	    !FU_ENSURE(TargetDataHandle.Data[Index].Get()->GetScriptStruct()->IsChildOf(FFuAbilityTargetData_Vector::StaticStruct())))
	{
		return {};
	}

	return *static_cast<FFuAbilityTargetData_Vector*>(TargetDataHandle.Data[Index].Get());
}
