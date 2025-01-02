// Copyright CS_WUXIA 


#include "UI/Widget/ShowNameWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"


void UShowNameWidget::SetOffsetMousePosition(const FVector2D& InPosition)
{
	OffsetMousePosition = InPosition;
}

void UShowNameWidget::SetNameText(const FText& InName)
{
	OnNameChangedEvent.Broadcast(InName);
}

void UShowNameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick( MyGeometry , InDeltaTime );
	if (!IsVisible())return;
	const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	
	SetPositionInViewport(MousePosition+OffsetMousePosition);
}

