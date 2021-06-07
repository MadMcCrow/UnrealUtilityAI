/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "UAIComponent.h"


// Sets default values
UUAIComponent::UUAIComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}


UUAIAction* UUAIComponent::GetBestAction() const
{
    UUAIAction* BestAction = nullptr;
    for (auto& itr : Actions)
    {
        if (itr != nullptr)
        {
            // An action is better than no action
            if (BestAction == nullptr)
            {
                BestAction = itr;
                continue;
            }

            // if we have met a better action, it's now the best !
            if (BestAction->GetUtilityScore(this) < itr->GetUtilityScore(this))
            {
               BestAction = itr;
            }
        }
    }
    return BestAction;
}

void UUAIComponent::ExecuteAction(UUAIAction* Todo)
{
    
}
