// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DungeonsThief/Managers/ScoreManager.h"
#include "UI_MainClass.generated.h"


/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_MainClass : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* FoodBar;

	UPROPERTY(VisibleAnywhere)
	AScoreManager* ScoreManagerReference;
	
	
};
