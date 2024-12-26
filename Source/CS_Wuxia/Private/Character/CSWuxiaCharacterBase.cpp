// Copyright CS_WUXIA 


#include "Character/CSWuxiaCharacterBase.h"

// Sets default values
ACSWuxiaCharacterBase::ACSWuxiaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACSWuxiaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetOutlineMaterialInstance();
}

// Called every frame
void ACSWuxiaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACSWuxiaCharacterBase::GetHightlightDuration() const
{
	return HightlightDuration;
}

UMaterialInstanceDynamic* ACSWuxiaCharacterBase::GetOutlineMaterialInstance()
{
	if (DynamicOutlineMaterialInstance == nullptr && OutlineMaterialInterface)
	{
		DynamicOutlineMaterialInstance = UMaterialInstanceDynamic::Create(OutlineMaterialInterface, this);
	}
	return DynamicOutlineMaterialInstance;
}

void ACSWuxiaCharacterBase::HighlightActor_Implementation()
{
	if (GetMesh()->GetOverlayMaterial())
	{
		UE_LOG(LogTemp, Warning, TEXT("HighlightActor_Implementation: Already OverlayMaterial"));
		return;
	}
	if (UMaterialInstanceDynamic* MaterialInstance = GetOutlineMaterialInstance() )
	{
		UE_LOG(LogTemp, Warning, TEXT("HighlightActor_Implementation: MaterialInstance %s"), *MaterialInstance->GetName());
		GetMesh()->SetOverlayMaterial(MaterialInstance);
	}
}

void ACSWuxiaCharacterBase::UnHighlightActor_Implementation()
{
	if (GetMesh()->GetOverlayMaterial() == Cast<UMaterialInstanceDynamic>(GetOutlineMaterialInstance()))
	{
		GetMesh()->SetOverlayMaterial( nullptr );
	}
}

void ACSWuxiaCharacterBase::MoveToLocation_Implementation(FVector& OutLocation)
{
	OutLocation = GetActorLocation();
}

