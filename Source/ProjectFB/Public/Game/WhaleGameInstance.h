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

	virtual void Init() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 BestScore;
public:
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	float BackGroundSoundValue;
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	float EffectSoundValue;
private:
	UPROPERTY()
	TObjectPtr<class UWhaleSaveGame> SaveGameClass;
public:
	void SetBestScore(int32 value);

	FORCEINLINE int32 GetBestScore()
	{
		return BestScore;
	}
	
	void MusicSave(float InMusicValue);
	void SoundFxSave(float InSoundFx);
	void ScoreSave(int InScore);
	TObjectPtr<class UWhaleSaveGame> Load();
};
