// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProjectSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API UProjectSaveGame : public USaveGame
{
	GENERATED_BODY()
private:
	UPROPERTY()
	FString SaveSlotName = TEXT("SaveSoundValue");
	UPROPERTY()
	int32 SoundIndex = 0;
	UPROPERTY()
	float MusicVolume;
	UPROPERTY()
	float SoundFXVolume;
public:
	UFUNCTION()
	FORCEINLINE FString GetSaveSlotName()
	{
		return SaveSlotName;
	}
	UFUNCTION()
	FORCEINLINE int32 GetSoundIndex()
	{
		return SoundIndex;
	}
	UFUNCTION()
	FORCEINLINE float GetMusicVolume()
	{
		return MusicVolume;
	}
	UFUNCTION()
	FORCEINLINE float GetSoundFXVolume()
	{
		return SoundFXVolume;
	}
	UFUNCTION()
	FORCEINLINE void SetMusicVolume(float Value)
	{
		MusicVolume = Value;
	}
	UFUNCTION()
	FORCEINLINE void SetSoundFXVolume(float Value)
	{
		SoundFXVolume = Value;
	}
};
