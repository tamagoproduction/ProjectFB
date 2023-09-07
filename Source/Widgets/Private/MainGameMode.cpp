// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/BP_MainWidget.BP_MainWidget_C'"));
	if (WidgetAsset.Succeeded())
	{
		MainWidgetClass = WidgetAsset.Class;
	}
	//DefaultPawnClass = AMainCharacter::StaticClass();
}

void AMainGameMode::BeginPlay()
{
	//마우스를 보여줌
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (MainWidgetClass != nullptr)
	{
		MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
		MainWidget->AddToViewport();
	}
}
