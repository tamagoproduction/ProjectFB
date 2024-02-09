// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Game/WhaleGameInstance.h"
#include "Character/Whale.h"
#include "Utile/Keys.h"

void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestart);
	MainButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMain);

	AWhale* Player = Cast<AWhale>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnUpdateScore.AddUObject(this, &UGameOverWidget::OnUpdateScore);
		Player->OnGameOver.AddUObject(this, &UGameOverWidget::OnUpdateBestScore);
	}
	ScoreText->SetText(FText::FromString(TEXT("0")));
	FString MainGameModePath = TEXT("");
	FString WhaleGameModePath = TEXT("");
}

void UGameOverWidget::OnRestart()
{
	//TODO : ���� �����ֱ�

	// MainGameMode���� ���� ���� �� �̸� �ε��� ���鱤�� �����ֱ�
	// ���������� �ε��ߴ��� && ���� ��� �������� üũ
	/*if (UKismetSystemLibrary::IsInterstitialAdRequested() &&
		UKismetSystemLibrary::IsInterstitialAdAvailable())
	{
		UKismetSystemLibrary::ShowInterstitialAd();
	}*/

	UGameplayStatics::OpenLevel(GetWorld(), Keys::LevelKeys::FlappyWhaleMap);
}

void UGameOverWidget::OnMain()
{
	UGameplayStatics::OpenLevel(GetWorld(), Keys::LevelKeys::MainMap);
}

void UGameOverWidget::OnUpdateScore(int32 Score)
{
	FString ScoreStr = FString::Printf(TEXT("%d"), Score);
	ScoreText->SetText(FText::FromString(ScoreStr));
}

void UGameOverWidget::OnUpdateBestScore()
{
	UWhaleGameInstance* Instance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Instance != nullptr)
	{
		FString BestScoreStr = FString::Printf(TEXT("%d"), Instance->GetBestScore());
		BestScoreText->SetText(FText::FromString(BestScoreStr));
	}
}
