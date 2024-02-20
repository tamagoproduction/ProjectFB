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
		OptionWidget->OnMusicValueChange.AddUObject(this, &AWhaleGameMode::OnMusicValueChange);
		OptionWidget->OnSoundValueChange.AddUObject(this, &AWhaleGameMode::OnSoundValueChange);
	}
	AWhale* Player = Cast<AWhale>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnGameOver.AddUObject(this, &AWhaleGameMode::OnGameOver);
	}

	FActorSpawnParameters Params;
	GetWorld()->SpawnActor<ASpawner>(Params);

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AWhaleGameMode::Load, 0.2f, false);
}

void AWhaleGameMode::OnGameOver()
{
	GameOverWidget->SetVisibility(ESlateVisibility::Visible); //∞‘¿”ø¿πˆ ¿ß¡¨¿ª ∫∏ø©¡‹
	Save();
}

void AWhaleGameMode::OnMusicValueChange(float Value)
{
	auto Instance = Cast< UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Instance->MusicVolume = Value;
	BackGroundAudio->SetVolumeMultiplier(Value != 0 ? Value : 0.001f);
	if (Value == 0)
		BackGroundAudio->SetAutoActivate(false);
	else
		BackGroundAudio->SetAutoActivate(true);
	Save();
}

void AWhaleGameMode::OnSoundValueChange(float Value)
{
	auto Instance = Cast< UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Instance->SoundVolume = Value;
	Save();
}

void AWhaleGameMode::Save()
{
	UWhaleSaveGame* MySaveGame = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
	if (MySaveGame == nullptr) return;
	auto Instance = Cast< UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MySaveGame == nullptr) return;
	MySaveGame->Score = Instance->Score;
	MySaveGame->MusicVolume = Instance->MusicVolume;
	MySaveGame->SoundVolume = Instance->SoundVolume;
	UGameplayStatics::AsyncSaveGameToSlot(MySaveGame, MySaveGame->SaveSlotName, MySaveGame->Index);
}

void AWhaleGameMode::Load()
{
	UWhaleSaveGame* MySaveGame = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
	if (MySaveGame == nullptr) return;
	if (UGameplayStatics::DoesSaveGameExist(MySaveGame->SaveSlotName, MySaveGame->Index))
	{
		auto Instance = Cast< UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (Instance == nullptr) return;
		MySaveGame = Cast<UWhaleSaveGame>(UGameplayStatics::LoadGameFromSlot(MySaveGame->SaveSlotName, MySaveGame->Index));
		Instance->Score = MySaveGame->Score;
		Instance->MusicVolume = MySaveGame->MusicVolume;
		Instance->SoundVolume = MySaveGame->SoundVolume;
	}
}
