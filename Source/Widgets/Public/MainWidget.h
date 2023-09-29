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
	virtual void NativeOnInitialized() override; //���� �ʱ�ȭ�� ȣ��Ǵ� �Լ�
public:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UButton> StartButton; //���ӽ��� ��ư
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UButton> OptionButton; //ȯ�漳�� ��ư
	UPROPERTY(VisibleAnywhere, Category = "Widget")
		TObjectPtr<class UUserWidget> OptionWidget; //�ɼ�����
public:
	UFUNCTION()
		void OnStartGame();
	UFUNCTION()
		void OnOptionWidget();
};
