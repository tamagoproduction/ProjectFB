// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WhaleWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Whale.h"
#include "Game/WhaleGameInstance.h"
#include "Widget/OptionWidget.h"
#include "Components/Slider.h"

void UWhaleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	AWhale* Whale = Cast<AWhale>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Whale))
	{
		Whale->OnUpdateScore.AddUObject(this, &UWhaleWidget::OnUpdateScore);
	}
	ScoreText->SetText(FText::FromString(TEXT("0")));

	OptionButton->OnClicked.AddDynamic(this, &UWhaleWidget::OnOptionWidget);
}

void UWhaleWidget::OnUpdateScore(int32 Score)
{
	FString ScoreStr = FString::Printf(TEXT("%d"), Score);
	ScoreText->SetText(FText::FromString(ScoreStr));
}

void UWhaleWidget::OnOptionWidget()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	OptionWidget->SetVisibility(ESlateVisibility::Visible);
	UWhaleGameInstance* Instance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UOptionWidget* Option = Cast<UOptionWidget>(OptionWidget);
	Option->BackgroundSoundSlider->SetValue(Instance->MusicVolume);
	Option->EffectSoundSlider->SetValue(Instance->SoundVolume);
}
