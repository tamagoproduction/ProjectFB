// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


void UGameWidget::NativeOnInitialized()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnUpdateScoreDelegate.AddUObject(this, &UGameWidget::OnUpdateScore);
	}
	ScoreText->SetText(FText::FromString(TEXT("0")));
}

void UGameWidget::OnUpdateScore(int32 Score)
{
	FString ScoreStr = FString::Printf(TEXT("%d"), Score);
	ScoreText->SetText(FText::FromString(ScoreStr));
}