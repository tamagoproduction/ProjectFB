// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectFBGameModeBase.h"

#include "MainCharacter.h"
#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"

AProjectFBGameModeBase::AProjectFBGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		GameoverWidgetClass = WidgetAsset.Class;
	}
}
void AProjectFBGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (GameoverWidgetClass != nullptr)
	{
		GameoverWidget = CreateWidget<UUserWidget>(GetWorld(), GameoverWidgetClass);
		GameoverWidget->AddToViewport();
		GameoverWidget->SetVisibility(ESlateVisibility::Hidden); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª º˚∞‹¡‹
	}
}
void AProjectFBGameModeBase::GameOver()
{
	//∏∂øÏΩ∫∏¶ ∫∏ø©¡‹
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameoverWidget->SetVisibility(ESlateVisibility::Visible); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª ∫∏ø©¡‹
	
}


