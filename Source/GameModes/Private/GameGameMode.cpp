// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

AGameGameMode::AGameGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (GameOverWidgetAsset.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetAsset.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> GameWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameWidget.BP_GameWidget_C'"));
	if (GameWidgetAsset.Succeeded())
	{
		GameWidgetClass = GameWidgetAsset.Class;
	}
}

void AGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GameWidgetClass != nullptr)
	{
		GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
		GameWidget->AddToViewport();
	}

	if (GameOverWidgetClass != nullptr)
	{
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
		GameOverWidget->SetVisibility(ESlateVisibility::Hidden); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª º˚∞‹¡‹
	}
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnGameOverDelegate.AddUObject(this, &AGameGameMode::OnGameOver);
	}

}

void AGameGameMode::OnGameOver()
{
	//∏∂øÏΩ∫∏¶ ∫∏ø©¡‹
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameOverWidget->SetVisibility(ESlateVisibility::Visible); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª ∫∏ø©¡‹
}
