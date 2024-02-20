// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/WhaleGameInstance.h"
#include "Game/WhaleSaveGame.h"
#include "Kismet/GameplayStatics.h"

UWhaleGameInstance::UWhaleGameInstance()
{
	MusicVolume = 0;
	SoundVolume = 0;
	Score = 0;
}

//void UWhaleGameInstance::Init()
//{
//	Super::Init();
//}

//void UWhaleGameInstance::SetBestScore(int32 value)
//{
//	if(SaveGameClass == nullptr)
//		SaveGameClass = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
//
//	if (BestScore < value)
//	{
//		BestScore = value;
//		SaveGameClass->SetScore(BestScore);
//		UGameplayStatics::SaveGameToSlot(SaveGameClass, SaveGameClass->SaveSlotName, SaveGameClass->Index);
//	}
//}

//void UWhaleGameInstance::MusicSave(float InMusicValue)
//{
//	BackGroundSoundValue = InMusicValue;
//	if (SaveGameClass == nullptr)
//	{
//		SaveGameClass = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
//	}
//	SaveGameClass->SetMusicVolume(InMusicValue);
//	UGameplayStatics::SaveGameToSlot(SaveGameClass, SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex());
//}
//
//void UWhaleGameInstance::SoundFxSave(float InSoundFx)
//{
//	EffectSoundValue = InSoundFx;
//	
//	if (SaveGameClass == nullptr)
//	{
//		SaveGameClass = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
//	}
//	SaveGameClass->SetSoundFXVolume(InSoundFx);
//	UGameplayStatics::SaveGameToSlot(SaveGameClass, SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex());
//}
//
//void UWhaleGameInstance::ScoreSave(int InScore)
//{
//	if (SaveGameClass == nullptr)
//	{
//		SaveGameClass = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
//	}
//	SaveGameClass->SetScore(InScore);
//	UGameplayStatics::SaveGameToSlot(SaveGameClass, SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex());
//}
//
//TObjectPtr<class UWhaleSaveGame> UWhaleGameInstance::Load()
//{
//	if (SaveGameClass == nullptr)
//	{
//		SaveGameClass = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
//	}
//	SaveGameClass = Cast<UWhaleSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex()));
//	EffectSoundValue = SaveGameClass->GetSoundFXVolume();
//	BackGroundSoundValue = SaveGameClass->GetMusicVolume();
//	return SaveGameClass;
//}
