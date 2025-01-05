// Copyright CS_WUXIA 


#include "UI/Widget/MainProfileWidget.h"

void UMainProfileWidget::ShowActorProfile(const FProfileData& ProfileData) const
{

	
	OnShowProfileDelegate.Broadcast(ProfileData);
}