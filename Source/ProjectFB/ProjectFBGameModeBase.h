// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectFBGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API AProjectFBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AProjectFBGameModeBase();

	void GameOver();
	virtual void BeginPlay() override;
public:
	UPROPERTY()
	TSubclassOf<UUserWidget> GameoverWidgetClass;
	UPROPERTY()
	class UUserWidget* GameoverWidget;
};
