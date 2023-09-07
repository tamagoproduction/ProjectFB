// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameoverWidget.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETS_API UGameoverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override; //위젯 초기화시 호출되는 함수
public:
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton; // 재시작 버튼
	UPROPERTY(meta = (BindWidget))
	class UButton* MainButton; // 메인화면 돌아가기 버튼
public:
	UFUNCTION()
	void OnRestart();
	UFUNCTION()
	void OnMain();
};
