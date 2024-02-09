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
	BackgroundSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnBackGroundSoundSlider);
	BackgroundSoundSlider->OnMouseCaptureEnd.AddDynamic(this, &UOptionWidget::OnSaveMusicSound);
	EffectSoundSlider->OnValueChanged.AddDynamic(this, &UOptionWidget::OnEffectSoundSlider);
	EffectSoundSlider->OnMouseCaptureEnd.AddDynamic(this, &UOptionWidget::OnSaveSoundFX);
}

void UOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WhaleGameInstance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	SaveGameClass = WhaleGameInstance->Load();
	if (SaveGameClass != nullptr)
	{
		/*FString Message = FString::Printf(TEXT("Music : %f / SoundFx : %f"), SaveGameClass->GetMusicVolume(), SaveGameClass->GetSoundFXVolume());
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Message);*/
		BackgroundSoundSlider->SetValue(SaveGameClass->GetMusicVolume());
		EffectSoundSlider->SetValue(SaveGameClass->GetSoundFXVolume());
	}
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
	WhaleGameInstance->MusicSave(BackgroundSoundSlider->GetValue());
}

void UOptionWidget::OnSaveSoundFX()
{
	WhaleGameInstance->SoundFxSave(EffectSoundSlider->GetValue());
}
