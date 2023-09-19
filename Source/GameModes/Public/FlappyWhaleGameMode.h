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
		class UUserWidget* GameOverWidget;

	UPROPERTY()
		TSubclassOf<UUserWidget> FlappyWhaleWidgetClass;
	UPROPERTY()
		class UUserWidget* FlappyWhaleWidget;
public:
	UFUNCTION()
		void OnGameOver();
};
