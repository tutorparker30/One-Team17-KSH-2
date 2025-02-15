#include "MyGameState.h"
#include "MyGameInstance.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AMyGameState::AMyGameState()
	:Score (0),
	SpawnedCoinCount (0),
	CollectedCoinCount (0),

	// Level 관리
	LevelDuration (25.0f),
	CurrentLevelIndex (0),
	MaxLevels (3),

	// Wave 관리
	CurrentWaveIndex (0),
	MaxWaves (3),
	WaveDuration (20.f),
	CoinsToSpawnPerWave({ 20, 30, 40 })
{

}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AMyGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	if (UMyGameInstance* GameInstance = GetMyGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{ 
			MyGameInstance->AddToScore(Amount);
		}
	}
}

void AMyGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			MyPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			CurrentLevelIndex = MyGameInstance->CurrentLevelIndex;
		}
	}

	CurrentWaveIndex = 0;
	StartWave();

	//SpawnedCoinCount = 0;
	//CollectedCoinCount = 0;

	//TArray<AActor*> FoundVolumes;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	//const int32 ItemToSpawn = 40;

	//for (int32 i = 0; i < ItemToSpawn; i++)
	//{
	//	if (FoundVolumes.Num() > 0)
	//	{
	//		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
	//		if (SpawnVolume)
	//		{
	//			AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
	//			if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
	//			{
	//				SpawnedCoinCount++;
	//			}
	//		}
	//	}
	//}

	//GetWorldTimerManager().SetTimer(
	//	LevelTimerHandle,
	//	this,
	//	&AMyGameState::OnLevelTimeUp,
	//	LevelDuration,
	//	false
	//);
}

void AMyGameState::StartWave()
{
	// 코인 카운트 리셋
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	// 이전 Wave 아이템 제거
	for (AActor* Item : CurrentWaveItems)
	{
		if (Item && Item->IsValidLowLevelFast())
		{
			Item->Destroy();
		}
	}
	CurrentWaveItems.Empty();

	// Wave에 스폰할 코인 개수 결정
	int32 CoinsToSpawn = (CoinsToSpawnPerWave.IsValidIndex(CurrentWaveIndex)) ? CoinsToSpawnPerWave[CurrentWaveIndex] : 20;

	// SpawnVolume을 이용해 코인 스폰
	if (ASpawnVolume* SpawnVolume = GetSpawnVolume())
	{
		for (int32 i = 0; i < CoinsToSpawn; i++)
		{
			if (AActor* SpawnedActor = SpawnVolume->SpawnRandomItem())
			{
				if (SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
					CurrentWaveItems.Add(SpawnedActor);
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(			//GEngine->AddOnScreenDebugMessage(스크린 상애 찍히는 로그함수)
		-1,										//그때그때 아이디 생성
		2.0f,									//지속시간
		FColor::Green,							//글씨 색
		FString::Printf(TEXT("Wave Start")));	//출력

	// 4. Wave별 환경 변화
	//if (CurrentWaveIndex == 1)
	//{
	//	EnableWave2Environment();
	//}
	//else if (CurrentWaveIndex == 2)
	//{
	//	EnableWave3Environment();
	//}

	// 5. Wave 타이머 시작 (WaveDuration 후 OnWaveTimeUp 호출)
	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&AMyGameState::OnWaveTimeUp,
		WaveDuration,
		false
	);
}

void AMyGameState::EndWave()
{
	// 남은 Wave 타이머 제거
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	// Wave3에서 활성화한 코인 궤도 회전 비활성화
	//if (CurrentWaveIndex == 2)
	//{
	//	SetAllCoinsOrbit(false);
	//}

	// 다음 Wave 진행 또는 Level 종료
	++CurrentWaveIndex;
	if (CurrentWaveIndex >= MaxWaves)
	{
		EndLevel();
	}
	else
	{
		StartWave();
	}
}

void AMyGameState::OnWaveTimeUp()
{
	EndWave();
}

//void AMyGameState::OnLevelTimeUp()
//{
//	EndLevel();
//}

void AMyGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), 
		CollectedCoinCount,

		SpawnedCoinCount)
		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount) 
		{
			EndLevel();
		}
}

void AMyGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			AddScore(Score);
			CurrentLevelIndex++;
			MyGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void AMyGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			MyPlayerController->SetPause(true);
			MyPlayerController->ShowMainMenu(true);
		}
	}
}

void AMyGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = MyPlayerController->GetHUDWidget())
			{
				// WaveTimerHandle 로 변경
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"),RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetMyGameInstance())
					{
						UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
						if (MyGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"),MyGameInstance->TotalScore)));
						}
					}
				}

				// Wave 업데이트
				if (UTextBlock* WaveText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
				{
					WaveText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d / %d"), CurrentWaveIndex + 1, MaxWaves)));
				}

				// Level 업데이트
				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"),CurrentLevelIndex + 1)));
				}
			}
		}
	}
}

//void AMyGameState::EnableWave2Environment()
//{
//	const FString Msg = TEXT("Wave2: Spawning and activating 5 Spike Traps!");
//	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
//	if (GEngine)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Msg);
//	}
//
//	//if (ASpawnVolume* SpawnVolume = GetSpawnVolume())
//	//{
//	//	if (SpikeTrapClass)
//	//	{
//	//		for (int32 i = 0; i < 5; i++)
//	//		{
//	//			if (AActor* SpawnedActor = SpawnVolume->SpawnActorAtRandomLocation(SpikeTrapClass))
//	//			{
//	//				if (ASpikeTrap* Trap = Cast<ASpikeTrap>(SpawnedActor))
//	//				{
//	//					Trap->ActivateTrap();
//	//				}
//	//			}
//	//		}
//	//	}
//	//}
//}

//void AMyGameState::EnableWave3Environment()
//{
//	SetAllCoinsOrbit(true);
//}
//
//void AMyGameState::SetAllCoinsOrbit(bool bActive)
//{
//	TArray<AActor*> AllCoins;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoinItem::StaticClass(), AllCoins);
//
//	//for (AActor* CoinActor : AllCoins)
//	//{
//	//	if (ACoinItem* Coin = Cast<ACoinItem>(CoinActor))
//	//	{
//	//		Coin->SetWave3OrbitActive(bActive);
//	//	}
//	//}
//}

ASpawnVolume* AMyGameState::GetSpawnVolume() const
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	return (FoundVolumes.Num() > 0) ? Cast<ASpawnVolume>(FoundVolumes[0]) : nullptr;
}

AMyPlayerController* AMyGameState::GetMyPlayerController() const
{
	return Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

UMyGameInstance* AMyGameState::GetMyGameInstance() const
{
	return Cast<UMyGameInstance>(GetGameInstance());
}