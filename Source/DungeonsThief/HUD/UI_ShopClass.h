// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_ShopClass.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterSkin
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnywhere)
	class USkeletalMesh* CurrentMesh;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTexture2D* CurrentSkinPreview;
};

UCLASS()
class DUNGEONSTHIEF_API UUI_ShopClass : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct() override;

	class UMyGameInstance* MyGameInstance;
	
	UPROPERTY(EditAnywhere, Category = "Custom Mesh")
	TArray<FCharacterSkin> GrantSkins;
	int CurrentGrantIndex;

	UPROPERTY(EditAnywhere, Category = "Custom Mesh")
	TArray<FCharacterSkin> NomadSkins;
	int CurrentNomadIndex;

	UPROPERTY(EditAnywhere, Category = "Custom Mesh")
	TArray<FCharacterSkin> EvaSkins;
	int CurrentEvaIndex;
	
	/* Change Grant skins buttons */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* GrantPreview;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* GrantLeftSelection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* GrantRightSelection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* GrantValidateSelection;

	/* Change Nomad skins buttons */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* NomadPreview;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* NomadLeftSelection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* NomadRightSelection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* NomadValidateSelection;

	/* Change Eva skins buttons */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* EvaPreview;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* EvaLeftSelection;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* EvaRightSelection;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* EvaValidateSelection;

protected:
	/* Method to change current skin selected*/
	void ChooseNextSkin(int &CurrentIndex, TArray<FCharacterSkin> Skins, UImage* Preview);
	void ChoosePreviousSkin(int &CurrentIndex, TArray<FCharacterSkin> Skins, UImage* Preview);
	class USkeletalMesh* SelectSkin(int CurrentIndex, TArray<FCharacterSkin> Skins);
	
	UFUNCTION()
	void ChooseNextGrantSkin();

	UFUNCTION()
	void ChoosePreviousGrantSkin();

	UFUNCTION()
	void SelectCurrentGrantSkin();

	UFUNCTION()
	void ChooseNextNomadSkin();

	UFUNCTION()
	void ChoosePreviousNomadSkin();

	UFUNCTION()
	void SelectCurrentNomadSkin();

	UFUNCTION()
	void ChooseNextEvaSkin();

	UFUNCTION()
	void ChoosePreviousEvaSkin();

	UFUNCTION()
	void SelectCurrentEvaSkin();
};
