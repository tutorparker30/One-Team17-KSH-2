#include "MytastActor.h"


AMytastActor::AMytastActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMytastActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Written by Team!!!."));
}
