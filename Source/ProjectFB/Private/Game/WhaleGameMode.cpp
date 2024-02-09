// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/WhaleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Whale.h"
#include "Components/AudioComponent.h"
#include "Widget/WhaleWidget.h"
#include "Widget/OptionWidget.h"
#include "Game/WhaleGameInstance.h"
#include "Game/WhaleSaveGame.h"
#include "Actor/Spawner.h"

AWhaleGameMode::AWhaleGameMode()
{
	// * ªÁøÓµÂ
	BackGroundAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BackGroundAudio"));
	static ConstructorHelpers::FObjectFinder<USoundWave> AudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/BackGround/GameBackGroundSound.GameBackGroundSound'"));
	if (AudioAsset.Succeeded())
	{
		BackGroundAudio->SetSound(AudioAsset.Object);
	}
	// * ∞‘¿”√¢ ¿ß¡¨
	static ConstructorHelpers::FClassFinder<UUserWidget> FlappyWhaleWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/WB_Whale.WB_Whale_C'"));
	if (FlappyWhaleWidgetAsset.Succeeded())
	{
		WhaleWidgetClass = FlappyWhaleWidgetAsset.Class;
	}
	// * ∞‘¿”¡æ∑· ¿ß¡¨
	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/WB_GameOver.WB_GameOver_C'"));
	if (GameOverWidgetAsset.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetAsset.Class;
	}

	// * ø…º«√¢ ¿ß¡¨
	static ConstructorHelpers::FClassFinder<UUserWidget> OptionWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/WB_Option.WB_Option_C'"));
	if (OptionWidgetAsset.Succeeded())
	{
		OptionWidgetClass = OptionWidgetAsset.Class;
	}


	DefaultPawnClass = AWhale::StaticClass();

}

void AWhaleGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	if (WhaleWidgetClass != nullptr)
	{
		WhaleWidget = CreateWidget<UWhaleWidget>(GetWorld(), WhaleWidgetClass);
		WhaleWidget->AddToViewport();
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
		WhaleWidget->OptionWidget = OptionWidget;
		OptionWidget->SetVisibility(ESlateVisibility::Hidden);
		OptionWidget->OnBackGroundSoundValueChange.AddUObject(this, &AWhaleGameMode::OnBackGroundSoundValueChange);
	}
	AWhale* Player = Cast<AWhale>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnGameOver.AddUObject(this, &AWhaleGameMode::OnGameOver);
	}

	WhaleGameInstance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FActorSpawnParameters Params;
	GetWorld()->SpawnActor<ASpawner>(Params);

	SaveGameClass = WhaleGameInstance->Load();
	if (SaveGameClass != nullptr)
	{
		BackGroundAudio->SetVolumeMultiplier(SaveGameClass->GetMusicVolume());
	}
}

void AWhaleGameMode::OnGameOver()
{
	GameOverWidget->SetVisibility(ESlateVisibility::Visible); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª ∫∏ø©¡‹
}

void AWhaleGameMode::OnBackGroundSoundValueChange(float Value)
{
	WhaleGameInstance->BackGroundSoundValue = Value;
	BackGroundAudio->SetVolumeMultiplier(Value != 0 ? Value : 0.001f);
	if (Value == 0)
		BackGroundAudio->SetAutoActivate(false);
	else
		BackGroundAudio->SetAutoActivate(true);
}
