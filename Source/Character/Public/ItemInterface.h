#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class CHARACTER_API IItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,	//오버랩이 발생한 자기자신(스피어 컴포넌트)
		AActor* OtherActor,						//부딧친 상대(스피어 컴포넌트로 들어간 물체(플레이어))
		UPrimitiveComponent* OtherComp,			//부딧친 상대의 충돌 컴포넌트(플레이어의 켑슐컴포넌트)
		int32 OtherBodyIndex,					//물리 시뮬
		bool bFromSweep,						//물리 시뮬
		const FHitResult& SweepResult			//물리 시뮬
	) = 0;
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) = 0;
	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemType() const = 0;


};
