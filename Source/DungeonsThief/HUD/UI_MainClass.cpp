// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainClass.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "DungeonsThief/Managers/ScoreManager.h"


void UUI_MainClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Try to fond the game object actor in the world
	AActor* TryScoreManager = UGameplayStatics::GetActorOfClass(GetWorld(), AScoreManager::StaticClass());

	if (TryScoreManager)
	{
		AScoreManager* ScoreManager = Cast<AScoreManager>(TryScoreManager);

		if(ScoreManager)
		{
			float Percent = (ScoreManager->GetPoints());
			int MaxPercent = (ScoreManager->GetMaxPoints());
		
			FoodBar->SetPercent(Percent/MaxPercent);	//Set progress bar value
		}
	}
	
}
