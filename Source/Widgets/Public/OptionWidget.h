// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidget.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBackSoundGroundValueChangeDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectSoundValueChangeDelegate, float);
UCLASS()
class WIDGETS_API UOptionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override; //���� �ʱ�ȭ�� ȣ��Ǵ� �Լ�
public:
	//TODO : ���� �����̵��, ȿ���� �����̵��, �ݱ�(���)
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class UButton> CloseButton;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class USlider> BackgroundSoundSlider;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<class USlider> EffectSoundSlider;
public:
	FOnBackSoundGroundValueChangeDelegate OnBackGroundSoundValueChange;
	FOnEffectSoundValueChangeDelegate OnEffectSoundValueChange;
private:
	UFUNCTION()
		void OnCloseWidget();
	UFUNCTION()
		void OnBackGroundSoundSlider(float Value);
	UFUNCTION()
		void OnEffectSoundSlider(float Value);
};
