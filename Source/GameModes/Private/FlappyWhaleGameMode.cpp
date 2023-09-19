// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyWhaleGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

AFlappyWhaleGameMode::AFlappyWhaleGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> FlappyWhaleWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_FlappyWhaleWidget.BP_FlappyWhaleWidget_C'"));
	if (FlappyWhaleWidgetAsset.Succeeded())
	{
		FlappyWhaleWidgetClass = FlappyWhaleWidgetAsset.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (GameOverWidgetAsset.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetAsset.Class;
	}
}

void AFlappyWhaleGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (FlappyWhaleWidgetClass != nullptr)
	{
		FlappyWhaleWidget = CreateWidget<UUserWidget>(GetWorld(), FlappyWhaleWidgetClass);
		FlappyWhaleWidget->AddToViewport();
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
		Player->OnGameOverDelegate.AddUObject(this, &AFlappyWhaleGameMode::OnGameOver);
	}

}

void AFlappyWhaleGameMode::OnGameOver()
{
	//∏∂øÏΩ∫∏¶ ∫∏ø©¡‹
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameOverWidget->SetVisibility(ESlateVisibility::Visible); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª ∫∏ø©¡‹
}
