// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

AGameGameMode::AGameGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		GameoverWidgetClass = WidgetAsset.Class;
	}
}

void AGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GameoverWidgetClass != nullptr)
	{
		GameoverWidget = CreateWidget<UUserWidget>(GetWorld(), GameoverWidgetClass);
		GameoverWidget->AddToViewport();
		GameoverWidget->SetVisibility(ESlateVisibility::Hidden); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª º˚∞‹¡‹
	}
}

void AGameGameMode::OnGameOver()
{
	//∏∂øÏΩ∫∏¶ ∫∏ø©¡‹
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameoverWidget->SetVisibility(ESlateVisibility::Visible); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª ∫∏ø©¡‹
}
