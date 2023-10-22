// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyWhaleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMODES_API AFlappyWhaleGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFlappyWhaleGameMode();
public:
	virtual void BeginPlay() override;
public:
	UPROPERTY()
		TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY()
		TObjectPtr<UUserWidget> GameOverWidget;

	UPROPERTY()
		TSubclassOf<UUserWidget> FlappyWhaleWidgetClass;
	UPROPERTY()
		TObjectPtr<class UFlappyWhaleWidget> FlappyWhaleWidget;
	UPROPERTY()
		TSubclassOf<UUserWidget> OptionWidgetClass;
	UPROPERTY()
		TObjectPtr<class UOptionWidget> OptionWidget;
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<class UAudioComponent> BackGroundAudio;
	UPROPERTY()
		TObjectPtr<class UProjectGameInstance> ProjectGameInstance;
	UPROPERTY()
		TObjectPtr<class UProjectSaveGame> SaveGameClass;
public:
	UFUNCTION()
		void OnGameOver();
	UFUNCTION()
		void OnBackGroundSoundValueChange(float Value);
};
