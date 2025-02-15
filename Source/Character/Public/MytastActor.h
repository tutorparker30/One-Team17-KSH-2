#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MytastActor.generated.h"

UCLASS()
class CHARACTER_API AMytastActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AMytastActor();

	virtual void BeginPlay() override;
};
