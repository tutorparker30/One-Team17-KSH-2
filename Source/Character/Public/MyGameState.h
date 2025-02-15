#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

class ASpawnVolume;
class AMyPlayerController;
class UMyGameInstance;


UCLASS()
class CHARACTER_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:

	AMyGameState();

	virtual void BeginPlay() override;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;

	// Level ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	// Wave ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<int32> CoinsToSpawnPerWave;

	// Ÿ�̸� �ڵ�
	FTimerHandle WaveTimerHandle;
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	// Level ����
	void StartLevel();
	void OnLevelTimeUp();
	void EndLevel();

	// Wave ����
	void StartWave();
	void EndWave();
	void OnWaveTimeUp();


	void UpdateHUD();
	void OnCoinCollected();

private:
	// ���� Wave�� ������ �����۵� (Wave ���� �� �ı�)
	UPROPERTY()
	TArray<AActor*> CurrentWaveItems;

	//void EnableWave2Environment();
	//void EnableWave3Environment();
	//void SetAllCoinsOrbit(bool bActive);

	// ���� �Լ��� ???
	ASpawnVolume* GetSpawnVolume() const;
	AMyPlayerController* GetMyPlayerController() const;
	UMyGameInstance* GetMyGameInstance() const;
};
