// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Utile/Keys.h"
#include "Game/WhaleGameInstance.h"
#include "Widget/OptionWidget.h"
#include "Components/Slider.h"


void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartButton->OnClicked.AddDynamic(this, &UMainWidget::OnStartGame);
	OptionButton->OnClicked.AddDynamic(this, &UMainWidget::OnOptionWidget);
}

void UMainWidget::OnStartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("FlappyWhaleMap"));
}

void UMainWidget::OnOptionWidget()
{
	if (OptionWidget != nullptr)
	{
		OptionWidget->SetVisibility(ESlateVisibility::Visible);
	}
	UWhaleGameInstance* Instance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UOptionWidget* Option = Cast<UOptionWidget>(OptionWidget);
	Option->BackgroundSoundSlider->SetValue(Instance->MusicVolume);
	Option->EffectSoundSlider->SetValue(Instance->SoundVolume);
}
