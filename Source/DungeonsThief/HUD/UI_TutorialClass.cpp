#include "DungeonsThief/HUD/UI_TutorialClass.h"

#include "MainMenuController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UUI_TutorialClass::NativeConstruct()
{
	Super::NativeConstruct();
	
	BtnBack->OnClicked.AddUniqueDynamic(this, &UUI_TutorialClass::Back);

}

void UUI_TutorialClass::Back()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}





