// Fill out your copyright notice in the Description page of Project Settings.

#include "GameoverWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "Keys.h"

void UGameoverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RestartButton->OnClicked.AddDynamic(this, &UGameoverWidget::OnRestart);
	MainButton->OnClicked.AddDynamic(this, &UGameoverWidget::OnMain);
}

void UGameoverWidget::OnRestart()
{
	// 재시작 로직 구현
}

void UGameoverWidget::OnMain()
{
	UGameplayStatics::OpenLevel(GetWorld(), Keys::LevelKeys::StartLevel);
}
