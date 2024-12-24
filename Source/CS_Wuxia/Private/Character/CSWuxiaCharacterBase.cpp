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
	
}

// Called every frame
void ACSWuxiaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACSWuxiaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

