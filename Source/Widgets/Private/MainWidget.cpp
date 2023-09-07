// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartButton->OnClicked.AddDynamic(this, &UMainWidget::OnStartGame);
}

void UMainWidget::OnStartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameLevel"));
}
