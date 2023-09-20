// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

//#include "Kismet/KismetSystemLibrary.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_MainWidget.BP_MainWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		MainWidgetClass = WidgetAsset.Class;
	}
	DefaultPawnClass = AMainCharacter::StaticClass();
}

void AMainGameMode::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (MainWidgetClass != nullptr)
	{
		MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
		MainWidget->AddToViewport();
	}

	// 게임 시작 시 전면광고 로드
	//UKismetSystemLibrary::LoadInterstitialAd(0);
}
