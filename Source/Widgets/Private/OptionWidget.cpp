// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "ProjectSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CloseButton->OnClicked.AddDynamic(this, &UOptionWidget::OnCloseWidget);
	BackgroundSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnBackGroundSoundSlider);
	BackgroundSoundSlider->OnMouseCaptureEnd.AddDynamic(this, &UOptionWidget::OnSaveMusicSound);
	EffectSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnEffectSoundSlider);
	EffectSoundSlider->OnMouseCaptureEnd.AddDynamic(this, &UOptionWidget::OnSaveSoundFX);
}

void UOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SaveGameClass = Cast<UProjectSaveGame>(UGameplayStatics::CreateSaveGameObject(UProjectSaveGame::StaticClass()));
	SaveGameClass = Cast<UProjectSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex()));
	BackgroundSoundSlider->SetValue(SaveGameClass->GetMusicVolume());
	EffectSoundSlider->SetValue(SaveGameClass->GetSoundFXVolume());
}

void UOptionWidget::OnCloseWidget()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
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

void UOptionWidget::OnSaveMusicSound()
{
	if (SaveGameClass != nullptr)
	{
		SaveGameClass->SetMusicVolume(BackgroundSoundSlider->Value);
		UGameplayStatics::SaveGameToSlot(SaveGameClass, SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex());
	}
}

void UOptionWidget::OnSaveSoundFX()
{
	if (SaveGameClass != nullptr)
	{
		SaveGameClass->SetSoundFXVolume(EffectSoundSlider->Value);
		UGameplayStatics::SaveGameToSlot(SaveGameClass, SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex());
	}
}
