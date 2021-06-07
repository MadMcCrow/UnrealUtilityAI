/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#include "UAIComponent.h"


// Sets default values
UUAIComponent::UUAIComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), 	bCanExecuteSimultaneous(), bCanStopRunningAction(),  MinUtilityScore(0.f)
{
	
}


void UUAIComponent::TickComponent(float DeltaTime,  ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent( DeltaTime,  TickType, ThisTickFunction);

    // if we are not doing anything, check if we should
    if (!IsExecutingAction())
    {
        UUAIAction* Action = GetBestAction();
        if (Action->GetUtilityScore(this)  >= MinUtilityScore)
        {
            ExecuteAction(Action);
        }
    }
    else 
    {
        if (bCanExecuteSimultaneous || bCanStopRunningAction) // those two situations are exclusives, for now
        {
           UUAIAction* Action = GetBestAction();
            if (Action != CurrentlyRunningAction)
            {
                if (bCanStopRunningAction)
                {
                    CurrentlyRunningAction->EndExecute();
                }
                ExecuteAction(Action);
            }
        }
    }
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
    if (Todo)
    {
        Todo->RequestExecute(this);
        CurrentlyRunningAction = Todo;
    }
}
