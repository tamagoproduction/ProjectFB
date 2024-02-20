// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WhaleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API UWhaleGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UWhaleGameInstance();
public:
	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	float MusicVolume; //배경음
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	float SoundVolume; //효과음
};
