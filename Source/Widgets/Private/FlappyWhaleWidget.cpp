// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyWhaleWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


void UFlappyWhaleWidget::NativeOnInitialized()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnUpdateScoreDelegate.AddUObject(this, &UFlappyWhaleWidget::OnUpdateScore);
	}
	ScoreText->SetText(FText::FromString(TEXT("0")));

	OptionButton->OnClicked.AddDynamic(this, &UFlappyWhaleWidget::OnOptionWidget);
}

void UFlappyWhaleWidget::OnUpdateScore(int32 Score)
{
	FString ScoreStr = FString::Printf(TEXT("%d"), Score);
	ScoreText->SetText(FText::FromString(ScoreStr));
}

void UFlappyWhaleWidget::OnOptionWidget()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	OptionWidget->SetVisibility(ESlateVisibility::Visible);
}
