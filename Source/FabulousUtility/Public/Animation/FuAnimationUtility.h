#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FuAnimationUtility.generated.h"

class UAnimSequenceBase;

UCLASS()
class FABULOUSUTILITY_API UFuAnimationUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Animation Utility", Meta = (ReturnDisplayName = "Play Length"))
	static float GetScaledPlayLength(const UAnimSequenceBase* Sequence);
};
