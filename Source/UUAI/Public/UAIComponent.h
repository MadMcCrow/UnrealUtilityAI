/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UAIAction.h"
#include "UAIComponent.generated.h"

// forward declaration
class UUAIAction;

/**
 * 	@brief Actor Component Class for UtilityAI
 * 	Adds UUAI Action hanling to any actor
 */
UCLASS(ClassGroup = UUAI, Category = "UUAI|Base",  meta=(BlueprintSpawnableComponent), HideCategories=("Collision", "Sockets"))
class UUAI_API UUAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UUAIComponent(const FObjectInitializer& ObjectInitializer);

	virtual void TickComponent( float DeltaTime,  ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override; 


public: 
	/**
	 * 	@brief find the action with the best utility score
	 */
	UFUNCTION(BlueprintPure, Category ="Utility AI")
	UUAIAction* GetBestAction() const;

	/**
	 * 	@brief execute a specific action
	 */
	UFUNCTION(BlueprintCallable, Category ="Utility AI")
	void ExecuteAction(UUAIAction* Todo);

	UFUNCTION(BlueprintPure, Category="Utility AI")
	bool IsExecutingAction() const
	{
		return CurrentlyRunningAction != nullptr;
	}


protected:

	/**
	 * 	@brief Actions this component can perform
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Utility AI", Instanced)
	TSet<UUAIAction*> Actions;

	/**
	 *	bCanExecuteSimultaneous
	 * 	@brief wether we allow starting multiple actions at once;
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Utility AI")
	bool bCanExecuteSimultaneous;

	/**
	 *	bCanStopRunningAction
	 * 	@brief wether we should kill an action when it's not the best one anymore
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Utility AI", meta = (EditCondition = "!bCanExecuteSimultaneous" ))
	bool bCanStopRunningAction;

	/**
	 *	MinUtilityScore
	 * 	@brief the minimum score an action should have to be executed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Utility AI")
	float MinUtilityScore;



private:

	UPROPERTY(Transient)
	UUAIAction* CurrentlyRunningAction;



};
