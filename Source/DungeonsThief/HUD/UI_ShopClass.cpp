// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_ShopClass.h"

#include "Components/Button.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"

void UUI_ShopClass::NativeConstruct()
{
	Super::NativeConstruct();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No game instance was found"));
		return;
	}

	GrantLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousGrantSkin);
	GrantRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextGrantSkin);
	GrantValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentGrantSkin);

	NomadLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousNomadSkin);
	NomadRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextNomadSkin);
	NomadValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentNomadSkin);

	EvaLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousEvaSkin);
	EvaRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextEvaSkin);
	EvaValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentEvaSkin);

}

void UUI_ShopClass::ChooseNextGrantSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("NEXT GRANT"));
	//CurrentGrantIndex = CurrentEvaIndex % GrantSkins.Num()
}

void UUI_ShopClass::ChoosePreviousGrantSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("PREVIOUS GRANT"));
}

void UUI_ShopClass::SelectCurrentGrantSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("SELECT GRANT"));
}

void UUI_ShopClass::ChooseNextNomadSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("NEXT NOMAD"));
}

void UUI_ShopClass::ChoosePreviousNomadSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("PREVIOUS NOMAD"));
}

void UUI_ShopClass::SelectCurrentNomadSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("SELECT NOMAD"));
}

void UUI_ShopClass::ChooseNextEvaSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("NEXT EVA"));
}

void UUI_ShopClass::ChoosePreviousEvaSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("PREVIOUS EVA"));
}

void UUI_ShopClass::SelectCurrentEvaSkin()
{
	UE_LOG(LogTemp, Warning, TEXT("SELECT EVA"));
}
