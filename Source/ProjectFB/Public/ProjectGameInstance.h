// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API UProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UProjectGameInstance();
private:
	UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 BestScore;
public:
	UPROPERTY(VisibleAnywhere, Category = "Sound")
		float BackGroundSoundValue;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
		float EffectSoundValue;
public:
	FORCEINLINE void SetBestScore(int32 value)
	{
		BestScore = value;
	}
	FORCEINLINE int32 GetBestScore()
	{
		return BestScore;
	}
};
