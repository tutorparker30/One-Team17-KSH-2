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

	// Level 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	// Wave 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<int32> CoinsToSpawnPerWave;

	// 타이머 핸들
	FTimerHandle WaveTimerHandle;
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	// Level 관리
	void StartLevel();
	void OnLevelTimeUp();
	void EndLevel();

	// Wave 관리
	void StartWave();
	void EndWave();
	void OnWaveTimeUp();


	void UpdateHUD();
	void OnCoinCollected();

private:
	// 현재 Wave에 스폰된 아이템들 (Wave 종료 시 파괴)
	UPROPERTY()
	TArray<AActor*> CurrentWaveItems;

	//void EnableWave2Environment();
	//void EnableWave3Environment();
	//void SetAllCoinsOrbit(bool bActive);

	// 헬퍼 함수들 ???
	ASpawnVolume* GetSpawnVolume() const;
	AMyPlayerController* GetMyPlayerController() const;
	UMyGameInstance* GetMyGameInstance() const;
};
