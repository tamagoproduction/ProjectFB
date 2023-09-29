// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETS_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override; //위젯 초기화시 호출되는 함수
public:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UButton> StartButton; //게임시작 버튼
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UButton> OptionButton; //환경설정 버튼
	UPROPERTY(VisibleAnywhere, Category = "Widget")
		TObjectPtr<class UUserWidget> OptionWidget; //옵션위젯
public:
	UFUNCTION()
		void OnStartGame();
	UFUNCTION()
		void OnOptionWidget();
};
