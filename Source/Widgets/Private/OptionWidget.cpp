// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"

void UOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CloseButton->OnClicked.AddDynamic(this, &UOptionWidget::OnCloseWidget);
	BackgroundSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnBackgroundSoundValueChange);

}

void UOptionWidget::OnCloseWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);

}

void UOptionWidget::OnBackgroundSoundValueChange(float Value)
{
	OnBackGroundValue.Broadcast(Value);
}

void UOptionWidget::OnEffectSoundSlider(float Value)
{
	OnEffectValue.Broadcast(Value);
}
