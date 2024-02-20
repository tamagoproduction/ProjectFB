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
public:
	UWhaleSaveGame();
public:
	UPROPERTY()
	FString SaveSlotName;
	UPROPERTY()
	int32 Index;
	UPROPERTY()
	float MusicVolume;
	UPROPERTY()
	float SoundVolume;
	UPROPERTY()
	int32 Score;

};
