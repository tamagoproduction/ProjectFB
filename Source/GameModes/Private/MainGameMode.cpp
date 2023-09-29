// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Components/AudioComponent.h"
#include "MainWidget.h"
#include "OptionWidget.h"
#include "ProjectGameInstance.h"

//#include "Kismet/KismetSystemLibrary.h"

AMainGameMode::AMainGameMode()
{
	// * ��������
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_MainWidget.BP_MainWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		MainWidgetClass = WidgetAsset.Class;
	}
	DefaultPawnClass = AMainCharacter::StaticClass();

	// * �ɼ�����
	static ConstructorHelpers::FClassFinder<UUserWidget> OptionWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_OptionWidget.BP_OptionWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		OptionWidgetClass = OptionWidgetAsset.Class;
	}

	// * ����
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
		OptionWidget->OnBackGroundSoundValueChange.AddUObject(this, &AMainGameMode::OnBackGroundSoundValueChange);
	}

	ProjectGameInstance = Cast<UProjectGameInstance>((UGameplayStatics::GetGameInstance(GetWorld())));

	// ���� ���� �� ���鱤�� �ε�
	//UKismetSystemLibrary::LoadInterstitialAd(0);
}

void AMainGameMode::OnBackGroundSoundValueChange(float Value)
{
	ProjectGameInstance->BackGroundSoundValue = Value;
	BackGroundAudio->SetVolumeMultiplier(Value != 0 ? Value : 0.001f);
	if (Value == 0)
		BackGroundAudio->SetAutoActivate(false);
	else
		BackGroundAudio->SetAutoActivate(true);
	FString Message = FString::Printf(TEXT("SoundValue : %f"), Value);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, Message);
}
