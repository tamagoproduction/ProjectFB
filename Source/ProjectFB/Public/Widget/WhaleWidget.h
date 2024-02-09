// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WhaleWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFB_API UWhaleWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeOnInitialized() override; //���� �ʱ�ȭ�� ȣ��Ǵ� �Լ�
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ScoreText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> OptionButton;
	UPROPERTY()
	TObjectPtr<class UUserWidget> OptionWidget; //�ɼ�����
public:
	UFUNCTION()
	void OnUpdateScore(int32 Score);
	UFUNCTION()
	void OnOptionWidget();
};
