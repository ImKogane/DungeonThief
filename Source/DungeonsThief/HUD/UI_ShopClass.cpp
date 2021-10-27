// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_ShopClass.h"

#include "Components/Button.h"
#include "Components/Image.h"
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

	BackToMenu->OnClicked.AddDynamic(this, &UUI_ShopClass::Back);

	GrantLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousGrantSkin);
	GrantRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextGrantSkin);
	GrantValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentGrantSkin);

	NomadLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousNomadSkin);
	NomadRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextNomadSkin);
	NomadValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentNomadSkin);

	EvaLeftSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChoosePreviousEvaSkin);
	EvaRightSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::ChooseNextEvaSkin);
	EvaValidateSelection->OnClicked.AddDynamic(this, &UUI_ShopClass::SelectCurrentEvaSkin);

	GrantPreview->SetBrushFromTexture(GrantSkins[0].CurrentSkinPreview);
	NomadPreview->SetBrushFromTexture(NomadSkins[0].CurrentSkinPreview);
	EvaPreview->SetBrushFromTexture(EvaSkins[0].CurrentSkinPreview);
}

void UUI_ShopClass::Back()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_ShopClass::ChooseNextSkin(int &CurrentIndex, TArray<FCharacterSkin> Skins, UImage* Preview)
{
	CurrentIndex = (CurrentIndex + 1) % Skins.Num();

	Preview->SetBrushFromTexture(Skins[CurrentIndex].CurrentSkinPreview);	
}

void UUI_ShopClass::ChoosePreviousSkin(int &CurrentIndex, TArray<FCharacterSkin> Skins, UImage* Preview)
{
	CurrentIndex--;
	if (CurrentIndex < 0)
	{
		CurrentIndex = Skins.Num() - 1;
	}

	Preview->SetBrushFromTexture(Skins[CurrentIndex].CurrentSkinPreview);	
}

USkeletalMesh* UUI_ShopClass::SelectSkin(int CurrentIndex, TArray<FCharacterSkin> Skins)
{
	FCharacterSkin SkinChosen = Skins[CurrentIndex];
	if (SkinChosen.CurrentMesh == nullptr && SkinChosen.CurrentSkinPreview == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Skeletal Mesh Or Image is null"));
		return nullptr;
	}

	return SkinChosen.CurrentMesh;
}

#pragma region GrantSkinSelection
void UUI_ShopClass::ChooseNextGrantSkin()
{
	ChooseNextSkin(CurrentGrantIndex, GrantSkins, GrantPreview);
}

void UUI_ShopClass::ChoosePreviousGrantSkin()
{
	ChoosePreviousSkin(CurrentGrantIndex, GrantSkins, GrantPreview);
}

void UUI_ShopClass::SelectCurrentGrantSkin()
{	
	MyGameInstance->SetCurrentGrantSkin(SelectSkin(CurrentGrantIndex, GrantSkins));
}
#pragma endregion 

#pragma region NomadSkinSelection
void UUI_ShopClass::ChooseNextNomadSkin()
{
	ChooseNextSkin(CurrentNomadIndex, NomadSkins, NomadPreview);
}

void UUI_ShopClass::ChoosePreviousNomadSkin()
{
	ChoosePreviousSkin(CurrentNomadIndex, NomadSkins, NomadPreview);
}

void UUI_ShopClass::SelectCurrentNomadSkin()
{
	MyGameInstance->SetCurrentNomadSkin(SelectSkin(CurrentNomadIndex, NomadSkins));
}
#pragma endregion 

#pragma region EvaSkinSelection
void UUI_ShopClass::ChooseNextEvaSkin()
{
	ChooseNextSkin(CurrentEvaIndex, EvaSkins, EvaPreview);
}

void UUI_ShopClass::ChoosePreviousEvaSkin()
{
	ChoosePreviousSkin(CurrentEvaIndex, EvaSkins, EvaPreview);
}

void UUI_ShopClass::SelectCurrentEvaSkin()
{
	MyGameInstance->SetCurrentEvaSkin(SelectSkin(CurrentEvaIndex, EvaSkins));
}
#pragma endregion 
