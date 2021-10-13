// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_TryPuttingFoodOnSpot.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_TryPuttingFoodOnSpot : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	/* Execute this function each time this Task is going to fire */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
