// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Utile/Keys.h"

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
	if (OptionWidget != nullptr)
	{
		OptionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
