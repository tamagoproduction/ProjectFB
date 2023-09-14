// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETS_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeOnInitialized() override; //위젯 초기화시 호출되는 함수
public:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UTextBlock> ScoreText;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UButton> OptionButton;
public:
	UFUNCTION()
		void OnUpdateScore(int32 Score);
};
