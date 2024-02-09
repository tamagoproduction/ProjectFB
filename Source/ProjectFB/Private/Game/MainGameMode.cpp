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
		OptionWidget->OnBackGroundSoundValueChange.AddUObject(this, &AMainGameMode::OnBackGroundSoundValueChange);
	}

	WhaleGameInstance = Cast<UWhaleGameInstance>((UGameplayStatics::GetGameInstance(GetWorld())));

	SaveGameClass = WhaleGameInstance->Load();
	if (IsValid(SaveGameClass))
	{
		BackGroundAudio->SetVolumeMultiplier(SaveGameClass->GetMusicVolume());
	}
}

void AMainGameMode::OnBackGroundSoundValueChange(float Value)
{
	WhaleGameInstance->BackGroundSoundValue = Value;
	BackGroundAudio->SetVolumeMultiplier(Value != 0 ? Value : 0.001f);
	if (Value == 0)
		BackGroundAudio->SetAutoActivate(false);
	else
		BackGroundAudio->SetAutoActivate(true);
}