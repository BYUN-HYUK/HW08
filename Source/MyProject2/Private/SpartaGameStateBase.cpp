
#include "SpartaGameStateBase.h"
#include "SpartaPlayerController.h"
#include "SpartaGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

ASpartaGameStateBase::ASpartaGameStateBase()
{
    Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f; // �� ������ 30��
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void ASpartaGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	UpdateHUD();
	// ���� ���� �� ù �������� ����
	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASpartaGameStateBase::UpdateHUD,
		0.1f,
		true
	);
}
int32 ASpartaGameStateBase::GetScore() const
{
    return Score;
}

void ASpartaGameStateBase::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			SpartaGameInstance->AddToScore(Amount);
		}
	}
}

void ASpartaGameStateBase::StartLevel()
{
	// ���� ���� ��, ���� ���� �ʱ�ȭ
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	// ���� �ʿ� ��ġ�� ��� SpawnVolume�� ã�� ������ 40���� ����
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				// ���� ������ ���Ͱ� ���� Ÿ���̶�� SpawnedCoinCount ����
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	// 30�� �Ŀ� OnLevelTimeUp()�� ȣ��ǵ��� Ÿ�̸� ����
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameStateBase::OnLevelTimeUp,
		LevelDuration,
		false
	);

	UpdateHUD();

	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coin"),
		CurrentLevelIndex + 1,
		SpawnedCoinCount);
}

void ASpartaGameStateBase::OnLevelTimeUp()
{
	// �ð��� �� �Ǹ� ������ ����
	EndLevel();
}

void ASpartaGameStateBase::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount)

		// ���� �������� ������ ������ ���� �ֿ��ٸ� ��� ���� ����
		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
		{
			EndLevel();
		}
}

void ASpartaGameStateBase::EndLevel()
{
	// Ÿ�̸� ����
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	// ���� ���� �ε�����
	CurrentLevelIndex++;

	// ��� ������ �� ���Ҵٸ� ���� ���� ó��
	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	// ���� �� �̸��� �ִٸ� �ش� �� �ҷ�����
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		// �� �̸��� ������ ���ӿ���
		OnGameOver();
	}
}

void ASpartaGameStateBase::OnGameOver()
{
	UpdateHUD();
	UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));
	// ���⼭ UI�� ���ٰų�, ����� ����� ���� ���� ����
}

void ASpartaGameStateBase::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController);
		{
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					UE_LOG(LogTemp, Warning, TEXT("Score Check 1"));
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						UE_LOG(LogTemp, Warning, TEXT("Score Check 2"));
						USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
						if (SpartaGameInstance)
						{
							UE_LOG(LogTemp, Warning, TEXT("Score Check 3"));
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
						}
					}
				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
				}
			}
		}
	}
}