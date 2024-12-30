// Copyright CS_WUXIA 


#include "Character/CSWuxiaCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/CSWuxiaInputComponent.h"

ACSWuxiaCharacter::ACSWuxiaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom , USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
	//轉向移動
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//轉向速率
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	//只能在地板 因為top down game
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->InitSphereRadius(TraceDistance); // 可自行設定範圍大小

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->InitBoxExtent(FVector(TraceDistance*0.5f, TraceDistance*0.5f, TraceDistance)); // 可自行設定範圍大小
}

void ACSWuxiaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ACSWuxiaCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsUseSphere)
	{
		InteractionSphere->InitSphereRadius(TraceDistance);
		// 設定 InteractionSphere 的 BeginOverlap 與 EndOverlap 事件
		InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACSWuxiaCharacter::OnBeginOverlap);
		InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ACSWuxiaCharacter::OnEndOverlap);
	}else
	{
		InteractionBox->InitBoxExtent(FVector(TraceDistance/2, TraceDistance/2, TraceDistance));
		// 設定 InteractionBox 的 BeginOverlap 與 EndOverlap 事件
		InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ACSWuxiaCharacter::OnBeginOverlap);
		InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ACSWuxiaCharacter::OnEndOverlap);
	}
}


void ACSWuxiaCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UnInteractActor(OtherActor);
	
}
void ACSWuxiaCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractActor(OtherActor);
}



void ACSWuxiaCharacter::InteractActor(AActor* Actor)
{
	if (!IsPlayerControlled()) return;
	// 判斷 OtherActor 是否實作了 IInteractable
	if (Actor && Actor->Implements<UInteractableInterface>())
	{
		// 呼叫 ShowInteractionWidget()
		IInteractableInterface::Execute_ShowInteractionWidget(Actor);
	}

	if(IsValid(Actor)&& Actor->Implements<UHightlightInterface>())
	{
		IHightlightInterface::Execute_HighlightActor(Actor);
	}
}

void ACSWuxiaCharacter::UnInteractActor(AActor* Actor)
{
	if (!IsPlayerControlled()) return;
	// 判斷 OtherActor 是否實作了 IInteractable
	if (Actor && Actor->Implements<UInteractableInterface>())
	{
		// 呼叫 ShowInteractionWidget()
		IInteractableInterface::Execute_HideInteractionWidget(Actor);
	}
	if(Actor && Actor->Implements<UHightlightInterface>())
	{
		IHightlightInterface::Execute_UnHighlightActor(Actor);
	}
}
