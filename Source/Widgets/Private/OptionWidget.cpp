// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"

void UOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CloseButton->OnClicked.AddDynamic(this, &UOptionWidget::OnCloseWidget);
	BackgroundSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnBackGroundSoundSlider);
	EffectSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnEffectSoundSlider);
}

void UOptionWidget::OnCloseWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UOptionWidget::OnBackGroundSoundSlider(float Value)
{
	if (OnBackGroundSoundValueChange.IsBound())
	{
		OnBackGroundSoundValueChange.Broadcast(Value);
	}
}

void UOptionWidget::OnEffectSoundSlider(float Value)
{
	if (OnEffectSoundValueChange.IsBound())
	{
		OnEffectSoundValueChange.Broadcast(Value);
	}
}
