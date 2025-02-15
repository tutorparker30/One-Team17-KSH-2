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
		UPrimitiveComponent* OverlappedComp,	//�������� �߻��� �ڱ��ڽ�(���Ǿ� ������Ʈ)
		AActor* OtherActor,						//�ε�ģ ���(���Ǿ� ������Ʈ�� �� ��ü(�÷��̾�))
		UPrimitiveComponent* OtherComp,			//�ε�ģ ����� �浹 ������Ʈ(�÷��̾��� �ν�������Ʈ)
		int32 OtherBodyIndex,					//���� �ù�
		bool bFromSweep,						//���� �ù�
		const FHitResult& SweepResult			//���� �ù�
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
