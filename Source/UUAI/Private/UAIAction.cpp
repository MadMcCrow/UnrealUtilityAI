/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "UAIAction.h"
#include "Curves/RichCurve.h"
#include "UAICondition.h"


UUAIAction::UUAIAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

float UUAIAction::GetUtilityScore(const UObject* ContextObject) const
{
    // the total value
    float utility_value_sum = 0.f;
    // evaluate each consideration
    for (const FUAIConsideration& itr: Considerations)
    {
        if (itr.ConditionObject != nullptr)
        {
            const float raw_value = itr.ConditionObject->Eval(ContextObject);
            float curve_adjusted_value = raw_value;
            if (itr.WeightCurve != nullptr)
            {
                curve_adjusted_value = itr.WeightCurve->GetFloatValue(raw_value);
            }
            const float weighted_value = curve_adjusted_value * itr.Weight;
            utility_value_sum += weighted_value;
        }
    }
    return utility_value_sum;
}