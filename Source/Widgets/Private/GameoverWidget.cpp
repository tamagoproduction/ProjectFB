// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Keys.h"

void UGameOverWidget::NativeOnInitialized()
{
	RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestart);
	MainButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMain);

}

void UGameOverWidget::OnRestart()
{
	UGameplayStatics::OpenLevel(GetWorld(), Keys::LevelKeys::MainLevel);
}

void UGameOverWidget::OnMain()
{
	UGameplayStatics::OpenLevel(GetWorld(), Keys::LevelKeys::StartLevel);
}
