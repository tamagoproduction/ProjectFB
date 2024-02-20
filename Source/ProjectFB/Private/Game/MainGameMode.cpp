// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MainGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Widget/MainWidget.h"
#include "Widget/OptionWidget.h"
#include "Game/WhaleGameInstance.h"
#include "Game/WhaleSaveGame.h"
AMainGameMode::AMainGameMode()
{
	// * 皋牢困连
	static ConstructorHelpers::FClassFinder<UUserWidget> MainWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/WB_Main.WB_Main_C'"));
	if (MainWidgetAsset.Succeeded())
	{
		MainWidgetClass = MainWidgetAsset.Class;
	}

	// * 可记困连
	static ConstructorHelpers::FClassFinder<UUserWidget> OptionWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/WB_Option.WB_Option_C'"));
	if (OptionWidgetAsset.Succeeded())
	{
		OptionWidgetClass = OptionWidgetAsset.Class;
	}

	// * 荤款靛
	BackGroundAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BackGroundAudio"));

	static ConstructorHelpers::FObjectFinder<USoundWave> AudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/BackGround/MainBackGroundSound.MainBackGroundSound'"));
	if (AudioAsset.Succeeded())
	{
		BackGroundAudio->SetSound(AudioAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = ACharacter::StaticClass();

}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (IsValid(Player))
	{
		Player->bUseControllerRotationPitch = false;
		Player->bUseControllerRotationYaw = false;
		Player->bUseControllerRotationRoll = false;
		APlayerController* Controller = Cast<APlayerController>(Player->GetController());
		if (IsValid(Controller))
		{
			Controller->SetShowMouseCursor(true);
		}
	}
	// * 皋牢困连
	if (MainWidgetClass != nullptr)
	{
		MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
		MainWidget->AddToViewport();
	}

	// * 可记困连
	if (OptionWidgetClass != nullptr)
	{
		OptionWidget = CreateWidget<UOptionWidget>(GetWorld(), OptionWidgetClass);
		OptionWidget->AddToViewport();
		MainWidget->OptionWidget = OptionWidget;
		OptionWidget->SetVisibility(ESlateVisibility::Hidden);
		OptionWidget->OnMusicValueChange.AddUObject(this, &AMainGameMode::OnMusicValueChange);
		OptionWidget->OnSoundValueChange.AddUObject(this, &AMainGameMode::OnSoundValueChange);
	}
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AMainGameMode::Load, 0.2f, false);
}

void AMainGameMode::OnMusicValueChange(float Value)
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

void AMainGameMode::OnSoundValueChange(float Value)
{
	auto Instance = Cast< UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Instance->SoundVolume = Value;
	Save();
}

void AMainGameMode::Save()
{
	UWhaleSaveGame* SaveGame = Cast<UWhaleSaveGame>(UGameplayStatics::CreateSaveGameObject(UWhaleSaveGame::StaticClass()));
	if (SaveGame == nullptr) return;
	auto Instance = Cast< UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Instance == nullptr) return;
	SaveGame->Score = Instance->Score;
	SaveGame->MusicVolume = Instance->MusicVolume;
	SaveGame->SoundVolume = Instance->SoundVolume;
	UGameplayStatics::AsyncSaveGameToSlot(SaveGame, SaveGame->SaveSlotName, SaveGame->Index);
}

void AMainGameMode::Load()
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
