// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override; //위젯 초기화시 호출되는 함수
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> RestartButton; // 재시작 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MainButton; // 메인화면 돌아가기 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ScoreText; //점수 텍스트
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> BestScoreText; //점수 텍스트
private:

public:
	UFUNCTION()
	void OnRestart();
	UFUNCTION()
	void OnMain();
public:
	UFUNCTION()
	void OnUpdateScore(int32 Score);
	UFUNCTION()
	void OnUpdateBestScore();
};
