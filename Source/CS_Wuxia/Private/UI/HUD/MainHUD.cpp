// Copyright CS_WUXIA 


#include "UI/HUD/MainHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/ViewModel/MainViewModel.h"
#include "UI/Widget/MainWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	ViewModel = NewObject<UMainViewModel>(this, ViewModelClass);
	// LoadScreenViewModel->InitializeLoadSlots();

	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
	MainWidget->AddToViewport();
	
	
}
