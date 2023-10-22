// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyWhaleGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "FlappyWhaleWidget.h"
#include "OptionWidget.h"
#include "ProjectGameInstance.h"
#include "ProjectSaveGame.h"

AFlappyWhaleGameMode::AFlappyWhaleGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();

	// * ∞‘¿”√¢ ¿ß¡¨
	static ConstructorHelpers::FClassFinder<UUserWidget> FlappyWhaleWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_FlappyWhaleWidget.BP_FlappyWhaleWidget_C'"));
	if (FlappyWhaleWidgetAsset.Succeeded())
	{
		FlappyWhaleWidgetClass = FlappyWhaleWidgetAsset.Class;
	}
	// * ∞‘¿”¡æ∑· ¿ß¡¨
	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (GameOverWidgetAsset.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetAsset.Class;
	}
	// * ø…º«√¢ ¿ß¡¨
	static ConstructorHelpers::FClassFinder<UUserWidget> OptionWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_OptionWidget.BP_OptionWidget_C'"));
	if (OptionWidgetAsset.Succeeded())
	{
		OptionWidgetClass = OptionWidgetAsset.Class;
	}

	// * ªÁøÓµÂ
	BackGroundAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BackGroundAudio"));

	static ConstructorHelpers::FObjectFinder<USoundWave> AudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/BackGround/GameBackGroundSound.GameBackGroundSound'"));
	if (AudioAsset.Succeeded())
	{
		BackGroundAudio->SetSound(AudioAsset.Object);
	}
}

void AFlappyWhaleGameMode::BeginPlay()
{
	Super::BeginPlay();
	//∏∂øÏΩ∫∏¶ ∫∏ø©¡‹
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	if (FlappyWhaleWidgetClass != nullptr)
	{
		FlappyWhaleWidget = CreateWidget<UFlappyWhaleWidget>(GetWorld(), FlappyWhaleWidgetClass);
		FlappyWhaleWidget->AddToViewport();
	}

	if (GameOverWidgetClass != nullptr)
	{
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
		GameOverWidget->SetVisibility(ESlateVisibility::Hidden); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª º˚∞‹¡‹
	}

	if (OptionWidgetClass != nullptr)
	{
		OptionWidget = CreateWidget<UOptionWidget>(GetWorld(), OptionWidgetClass);
		OptionWidget->AddToViewport();
		FlappyWhaleWidget->OptionWidget = OptionWidget;
		OptionWidget->SetVisibility(ESlateVisibility::Hidden);
		OptionWidget->OnBackGroundSoundValueChange.AddUObject(this, &AFlappyWhaleGameMode::OnBackGroundSoundValueChange);
	}

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnGameOverDelegate.AddUObject(this, &AFlappyWhaleGameMode::OnGameOver);
	}

	 ProjectGameInstance = Cast<UProjectGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	 SaveGameClass = Cast<UProjectSaveGame>(UGameplayStatics::CreateSaveGameObject(UProjectSaveGame::StaticClass()));
	 SaveGameClass = Cast<UProjectSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameClass->GetSaveSlotName(), SaveGameClass->GetSoundIndex()));
	 BackGroundAudio->SetVolumeMultiplier(SaveGameClass->GetMusicVolume());
}

void AFlappyWhaleGameMode::OnGameOver()
{
	GameOverWidget->SetVisibility(ESlateVisibility::Visible); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª ∫∏ø©¡‹
}

void AFlappyWhaleGameMode::OnBackGroundSoundValueChange(float Value)
{
	ProjectGameInstance->BackGroundSoundValue = Value;
	BackGroundAudio->SetVolumeMultiplier(Value != 0 ? Value : 0.001f);
	if (Value == 0)
		BackGroundAudio->SetAutoActivate(false);
	else
		BackGroundAudio->SetAutoActivate(true);

}
