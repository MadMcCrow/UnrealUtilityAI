/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "UAICondition.h"


// Sets default values
UUAICondition::UUAICondition(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}


float UUAICondition::NativeEvaluateCondition(const UObject* ContextObject) const
{
    return EvaluateCondition(ContextObject);
}