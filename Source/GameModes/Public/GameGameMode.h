// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMODES_API AGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameGameMode();
public:
	virtual void BeginPlay() override;
public:
	UPROPERTY()
		TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY()
		class UUserWidget* GameOverWidget;
	UPROPERTY()
		TSubclassOf<UUserWidget> GameWidgetClass;
	UPROPERTY()
		class UUserWidget* GameWidget;
public:
	void OnGameOver();
};
