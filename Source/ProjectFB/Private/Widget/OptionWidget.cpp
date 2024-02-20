// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OptionWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Game/WhaleSaveGame.h"
#include "Game/WhaleGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CloseButton->OnClicked.AddDynamic(this, &UOptionWidget::OnCloseWidget);
	BackgroundSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnMusicSlider);
	BackgroundSoundSlider->OnMouseCaptureEnd.AddDynamic(this, &UOptionWidget::OnSaveMusicSound);
	EffectSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnSoundSlider);
	EffectSoundSlider->OnMouseCaptureEnd.AddDynamic(this, &UOptionWidget::OnSaveSoundFX);
}

void UOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//WhaleGameInstance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//SaveGameClass = WhaleGameInstance->Load();
	//if (SaveGameClass != nullptr)
	//{
	//	BackgroundSoundSlider->SetValue(SaveGameClass->GetMusicVolume());
	//	EffectSoundSlider->SetValue(SaveGameClass->GetSoundFXVolume());
	//}
}

void UOptionWidget::OnCloseWidget()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UOptionWidget::OnMusicSlider(float Value)
{
	if (OnMusicValueChange.IsBound())
	{
		OnMusicValueChange.Broadcast(Value);
	}
}

void UOptionWidget::OnSoundSlider(float Value)
{
	if (OnSoundValueChange.IsBound())
	{
		OnSoundValueChange.Broadcast(Value);
	}
}

void UOptionWidget::OnSaveMusicSound()
{
	UWhaleGameInstance* Instance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Instance != nullptr)
	{
		Instance->MusicVolume = BackgroundSoundSlider->GetValue();
	}
	
}

void UOptionWidget::OnSaveSoundFX()
{
	UWhaleGameInstance* Instance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Instance != nullptr)
	{
		Instance->SoundVolume = EffectSoundSlider->GetValue();
	}
}
