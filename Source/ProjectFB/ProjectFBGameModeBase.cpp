// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectFBGameModeBase.h"

#include "MainCharacter.h"
#include "GameoverWidget.h"
#include "Kismet/GameplayStatics.h"

AProjectFBGameModeBase::AProjectFBGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameoverWidget.BP_GameoverWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		GameoverWidgetClass = WidgetAsset.Class;
	}
}

void AProjectFBGameModeBase::GameOver()
{
	//마우스를 보여줌
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (GameoverWidgetClass != nullptr)
	{
		GameoverWidget = CreateWidget<UUserWidget>(GetWorld(), GameoverWidgetClass);
		GameoverWidget->AddToViewport();
	}
}