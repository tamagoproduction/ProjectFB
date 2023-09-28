// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Keys.h"

void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartButton->OnClicked.AddDynamic(this, &UMainWidget::OnStartGame);
	OptionButton->OnClicked.AddDynamic(this, &UMainWidget::OnOptionWidget);
}

void UMainWidget::OnStartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), Keys::LevelKeys::FlappyWhaleMap);
}

void UMainWidget::OnOptionWidget()
{
	OptionWidget->SetVisibility(ESlateVisibility::Visible);
}
