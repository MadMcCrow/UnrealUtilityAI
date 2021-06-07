/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UAICondition.generated.h"

UCLASS(Abstract, Category = "UUAI|Base", BlueprintType, Blueprintable, EditInlineNew)
class UUAI_API UUAICondition : public UObject
{
	GENERATED_BODY()

public:
	// CTR
	UUAICondition(const FObjectInitializer& ObjectInitializer);


protected:

	/**
	 * 	@fn NativeEvaluateCondition
	 * 	@brief will give you the raw value of that condition
	 */
	virtual float NativeEvaluateCondition(const UObject* ContextObject) const;

	/**
	 * 	@fn EvaluateCondition
	 * 	@brief will give you the raw value of that condition
	 * 	@note Blueprint event for @see NativeEvaluateCondition
	 */
	UFUNCTION(BlueprintImplementableEvent, Category ="Utility AI")
	float EvaluateCondition(const UObject* ContextObject) const;

public:

	FORCEINLINE float Evaluate(const UObject* ContextObject) const {return NativeEvaluateCondition(ContextObject);} 
	

};
