/* Copyright © Noé Perard-Gayot 2021. Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php */
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UAIAction.generated.h"

/** Simple multicast type for Actions */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionEvent);

/**
 * 	@struct UAIConsideration
 * 	@brief	This struct contains the necessary information for the Weighting of condition in Actions
 * 	@note	check if instanced is ruining performance
 */
USTRUCT(BlueprintType)
struct FUAIConsideration
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UUAICondition* ConditionObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCurveFloat* WeightCurve 		= nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 1.f;


	friend inline uint32 GetTypeHash(const FUAIConsideration& InHashValue) { return GetTypeHash(InHashValue.ConditionObject) + GetTypeHash(InHashValue.WeightCurve) + GetTypeHash(InHashValue.Weight); }

};

/**
 * 	@class	UAIAction
 * 	@brief	An Action is a thing the AI can do with a way to calculate it's utility value
 */
UCLASS(Abstract, Category = "UUAI|Base", Blueprintable, BlueprintType, EditInlineNew)
class UUAI_API UUAIAction : public UObject
{
	GENERATED_BODY()

public:
	// CTR
	UUAIAction(const FObjectInitializer& ObjectInitializer);

public:

	/**
	 * 	@brief this is the weighted score of this action
	 */
	UFUNCTION(BlueprintCallable, Category ="Utility AI")
	float GetUtilityScore(const UObject* ContextObject) const;


	/**
	 * 	@brief	check if this can run and start execute
	 * 			This is meant to implement further checks, 
	 * 	@note 	Instead of using this, use the broadcast event to implement tasks in actors instead
	 * 	@note	this will appear as a function and not as a Event due to constness
	 */
	UFUNCTION(BlueprintCallable, Category ="Utility AI")
	bool RequestExecute(const UObject* ContextObject) const;

	/**
	 * 	@brief	stop executing this action
	* 	@todo	Add a "Reason" 
	 */
	UFUNCTION(BlueprintCallable, Category ="Utility AI")
	void EndExecute() const;


protected:

	/**
	 * 	@brief	Execute this action command
	 */
	virtual void NativeExecute(const UObject* ContextObject) const;



	/**
	 * 	@brief	Execute this action command
	 * 			This is meant to implement how this action is done, bells and whistle to the system
	 * 	@note 	Instead of using this, use the broadcast event to implement tasks in actors instead
	 * 	@note	this will appear as a function and not as a Event due to constness
	 */
	UFUNCTION(BlueprintImplementableEvent, Category ="Utility AI")
	void Execute(const UObject* ContextObject) const;

	/**
	 * 	@brief	Simple function to test if action can be executed
	 * 	@note	this will appear as a function and not as a Event due to constness
	 */
	UFUNCTION(BlueprintNativeEvent, Category ="Utility AI")
	bool CanExecute(const UObject* ContextObject) const;
	virtual bool  CanExecute_Implementation(const UObject* ContextObject) const;


protected:

	/**
	 * 	@brief a simple UID/Name for this action, not gameplay related
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ActionName;

	/**
	 * 	@brief Considerations to evaluate for this action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FUAIConsideration> Considerations;

	/** Event to broacast execution of this action */
	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FOnActionEvent OnStartExecution;

	/** Event to broacast the end of execution of this action */
	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FOnActionEvent OnStopExecution;

};
