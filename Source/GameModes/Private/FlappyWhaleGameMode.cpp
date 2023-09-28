// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyWhaleGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "FlappyWhaleWidget.h"
#include "OptionWidget.h"

AFlappyWhaleGameMode::AFlappyWhaleGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();

	// * 게임창 위젯
	static ConstructorHelpers::FClassFinder<UUserWidget> FlappyWhaleWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_FlappyWhaleWidget.BP_FlappyWhaleWidget_C'"));
	if (FlappyWhaleWidgetAsset.Succeeded())
	{
		FlappyWhaleWidgetClass = FlappyWhaleWidgetAsset.Class;
	}
	// * 게임종료 위젯
	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (GameOverWidgetAsset.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetAsset.Class;
	}
	// * 옵션창 위젯
	static ConstructorHelpers::FClassFinder<UUserWidget> OptionWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_OptionWidget.BP_OptionWidget'"));
	if (OptionWidgetAsset.Succeeded())
	{
		OptionWidgetClass = OptionWidgetAsset.Class;
	}

	// * 사운드
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
	if (FlappyWhaleWidgetClass != nullptr)
	{
		FlappyWhaleWidget = CreateWidget<UFlappyWhaleWidget>(GetWorld(), FlappyWhaleWidgetClass);
		FlappyWhaleWidget->AddToViewport();
	}

	if (GameOverWidgetClass != nullptr)
	{
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
		GameOverWidget->SetVisibility(ESlateVisibility::Hidden); //게임오버 위젯을 숨겨줌
	}

	if (OptionWidgetClass != nullptr)
	{
		OptionWidget = CreateWidget<UOptionWidget>(GetWorld(), OptionWidgetClass);
		OptionWidget->AddToViewport();
		FlappyWhaleWidget->OptionWidget = OptionWidget;
		OptionWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnGameOverDelegate.AddUObject(this, &AFlappyWhaleGameMode::OnGameOver);
	}

}

void AFlappyWhaleGameMode::OnGameOver()
{
	//마우스를 보여줌
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameOverWidget->SetVisibility(ESlateVisibility::Visible); //게임오버 위젯을 보여줌
}
