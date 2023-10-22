// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMODES_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainGameMode();
public:
	virtual void BeginPlay() override;
public:
	UPROPERTY()
		TSubclassOf<UUserWidget> MainWidgetClass;
	UPROPERTY()
		TObjectPtr<class UMainWidget> MainWidget;
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
		void OnBackGroundSoundValueChange(float Value);
};
