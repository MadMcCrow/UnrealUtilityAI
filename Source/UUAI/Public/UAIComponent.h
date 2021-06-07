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
UCLASS(ClassGroup = UUAI, Category = "UUAI|Base",  meta=(BlueprintSpawnableComponent))
class UUAI_API UUAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UUAIComponent(const FObjectInitializer& ObjectInitializer);

	/**
	 * 	@brief Actions this component can perform
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Utility AI", Instanced)
	TSet<UUAIAction*> Actions;

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

};
