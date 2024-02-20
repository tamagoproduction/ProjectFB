// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WhaleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API AWhaleGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWhaleGameMode();
public:
	virtual void BeginPlay() override;
public:
	UPROPERTY()
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> GameOverWidget;

	UPROPERTY()
	TSubclassOf<UUserWidget> WhaleWidgetClass;
	UPROPERTY()
	TObjectPtr<class UWhaleWidget> WhaleWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> OptionWidgetClass;
	UPROPERTY()
	TObjectPtr<class UOptionWidget> OptionWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAudioComponent> BackGroundAudio;
	UPROPERTY()
	TObjectPtr<class UWhaleGameInstance> WhaleGameInstance;
	UPROPERTY()
	TObjectPtr<class UWhaleSaveGame> SaveGameClass;
public:
	UFUNCTION()
	void OnGameOver();
private:
	UFUNCTION()
	void OnMusicValueChange(float Value);
	UFUNCTION()
	void OnSoundValueChange(float Value);
public:
	UFUNCTION()
	void Save();
	UFUNCTION()
	void Load();
};
