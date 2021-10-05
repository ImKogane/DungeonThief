// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_HasSeenPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_HasSeenPlayer : public UBTService
{
	GENERATED_BODY()

protected:

	virtual void ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
