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
	virtual void NativeOnInitialized() override; //���� �ʱ�ȭ�� ȣ��Ǵ� �Լ�
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> RestartButton; // ����� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MainButton; // ����ȭ�� ���ư��� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ScoreText; //���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> BestScoreText; //���� �ؽ�Ʈ
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
