// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainClass.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"


void UUI_MainClass::NativeConstruct()
{
	Super::NativeConstruct();

	//Try to fond the game object actor in the world
	AActor* TryScoreManager = UGameplayStatics::GetActorOfClass(GetWorld(), AScoreManager::StaticClass());

	if (TryScoreManager)
	{
		ScoreManagerReference = Cast<AScoreManager>(TryScoreManager);
	}
}

void UUI_MainClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(ScoreManagerReference)
	{
		float Percent = (ScoreManagerReference->GetPoints());
		int MaxPercent = (ScoreManagerReference->GetMaxPoints());
	
		FoodBar->SetPercent(Percent/MaxPercent);	//Set progress bar value
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Crouch."));
	}
	
}
