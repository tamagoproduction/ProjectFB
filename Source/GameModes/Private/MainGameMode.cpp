// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Components/AudioComponent.h"
#include "MainWidget.h"
#include "OptionWidget.h"

//#include "Kismet/KismetSystemLibrary.h"

AMainGameMode::AMainGameMode()
{
	// * 메인위젯
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_MainWidget.BP_MainWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		MainWidgetClass = WidgetAsset.Class;
	}
	DefaultPawnClass = AMainCharacter::StaticClass();

	// * 옵션위젯
	static ConstructorHelpers::FClassFinder<UUserWidget> OptionWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_OptionWidget.BP_OptionWidget'"));
	if (WidgetAsset.Succeeded())
	{
		OptionWidgetClass = OptionWidgetAsset.Class;
	}

	// * 사운드
	BackGroundAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BackGroundAudio"));

	static ConstructorHelpers::FObjectFinder<USoundWave> AudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/BackGround/MainBackGroundSound.MainBackGroundSound'"));
	if (AudioAsset.Succeeded())
	{
		BackGroundAudio->SetSound(AudioAsset.Object);
	}
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (MainWidgetClass != nullptr)
	{
		MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
		MainWidget->AddToViewport();
	}
	if (OptionWidgetClass != nullptr)
	{
		OptionWidget = CreateWidget<UOptionWidget>(GetWorld(), OptionWidgetClass);
		OptionWidget->AddToViewport();
		MainWidget->OptionWidget = OptionWidget;
		OptionWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	// 게임 시작 시 전면광고 로드
	//UKismetSystemLibrary::LoadInterstitialAd(0);
}
