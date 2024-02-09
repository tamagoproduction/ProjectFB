// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WhaleSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API UWhaleSaveGame : public USaveGame
{
	GENERATED_BODY()
private:
	UPROPERTY()
	FString SaveSlotName = TEXT("MyFlappyWhale");
	UPROPERTY()
	int32 SoundIndex = 0;
	UPROPERTY()
	float MusicVolume;
	UPROPERTY()
	float SoundFXVolume;
	UPROPERTY()
	int32 Score;
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
	UFUNCTION()
	FORCEINLINE void SetScore(int Value)
	{
		Score = Value;
	}
	UFUNCTION()
	FORCEINLINE int GetScore()
	{
		return Score;
	}
};
