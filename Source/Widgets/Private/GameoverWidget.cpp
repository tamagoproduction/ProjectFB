// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGameInstance.h"
#include "PlayerCharacter.h"
#include "Keys.h"

void UGameOverWidget::NativeOnInitialized()
{
	RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestart);
	MainButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMain);

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnUpdateScoreDelegate.AddUObject(this, &UGameOverWidget::OnUpdateScore);
		Player->OnGameOverDelegate.AddUObject(this, &UGameOverWidget::OnUpdateBestScore);
	}
	ScoreText->SetText(FText::FromString(TEXT("0")));
}

void UGameOverWidget::OnRestart()
{
	UGameplayStatics::OpenLevel(GetWorld(), Keys::LevelKeys::GameMap);
	//TODO : 광고 보여주기
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
	UProjectGameInstance* Instance = Cast<UProjectGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Instance != nullptr)
	{
		FString BestScoreStr = FString::Printf(TEXT("%d"), Instance->GetBestScore());
		BestScoreText->SetText(FText::FromString(BestScoreStr));
	}
}
