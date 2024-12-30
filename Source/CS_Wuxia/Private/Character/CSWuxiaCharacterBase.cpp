// Copyright CS_WUXIA 


#include "Character/CSWuxiaCharacterBase.h" 

#include "DataRegistrySubsystem.h"
#include "AbilitySystem/CSWuxiaAbilitySystemComponent.h"
#include "AbilitySystem/CSWuxiaAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Data/CharacterRow.h"

struct FCharacterRow;
// Sets default values
ACSWuxiaCharacterBase::ACSWuxiaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 設置 WidgetComponent
	InteractableWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractableWidget"));
	InteractableWidget->SetupAttachment(RootComponent);
	// InteractableWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractableWidget->SetRelativeLocation(FVector(0, 0, 100.f));
	// 預設隱藏
	InteractableWidget->SetVisibility(false);


	AbilitySystemComponent = CreateDefaultSubobject<UCSWuxiaAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(false);
	// AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UCSWuxiaAttributeSet>(TEXT("AttributeSet"));
	
}

UAbilitySystemComponent* ACSWuxiaCharacterBase::GetAbilitySystemComponent() const
{	
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ACSWuxiaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetOutlineMaterialInstance();
	if (CharacterRowID.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterRowID is None"));
		return;
	}
	UDataRegistrySubsystem* DataRegistrySubsystem = GEngine->GetEngineSubsystem<UDataRegistrySubsystem>();

	if (DataRegistrySubsystem)
	{
		// 定義要獲取的DataRegistry ID
		const FDataRegistryId DataId = FDataRegistryId(TEXT("DR_Character"), CharacterRowID);

		// 從Data Registry中獲取已快取的數據
		const FCharacterRow* CachedData = DataRegistrySubsystem->GetCachedItem<FCharacterRow>( DataId );
		if (CachedData)
		{
			if (CachedData)
			{
				// 處理數據
				UE_LOG(LogTemp, Log, TEXT("Data retrieved successfully"));
				// 您可以在此處對CachedData進行進一步處理

				
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No cached data found"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to retrieve data from registry"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get DataRegistrySubsystem"));
	}
	
	// if (const UDataRegistrySubsystem* SubSystem = GEngine->GetEngineSubsystem<UDataRegistrySubsystem>())
	// {
	// 	UDataRegistry* DataRegistry = SubSystem->GetRegistryForType( "DR_Character" );
	// 	FDataRegistryId Id;
	// 	Id.ItemName = CharacterRowID;
	// 	Id.RegistryType = "DR_Character";
	// 	if ( const FCharacterRow* Data = DataRegistry->GetCachedItem<FCharacterRow>( Id ) )
	// 	{
	// 		auto Name = Data->NameID.ToString();
	// 		UE_LOG(LogTemp, Warning, TEXT("CharacterRowID %s"),*Name);
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("CharacterRowID %s not found"), *CharacterRowID.ToString());
	// 	}
	// }
	
}

// Called every frame
void ACSWuxiaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void ACSWuxiaCharacterBase::ShowInteractionWidget_Implementation()
{
	if (!InteractableWidget)return;
	InteractableWidget->SetVisibility(true);
}

void ACSWuxiaCharacterBase::HideInteractionWidget_Implementation()
{
	if (!InteractableWidget)return;
	InteractableWidget->SetVisibility(false);
}
