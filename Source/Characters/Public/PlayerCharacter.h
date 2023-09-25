// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateScoreDelegate, int32);
DECLARE_MULTICAST_DELEGATE(FOnGameOverDelegate);

UCLASS()
class CHARACTERS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
private:
	// * Mesh
	UPROPERTY(VisibleAnywhere, Category = "Montage")
		TObjectPtr<class UAnimMontage> JumpMontage;

	// * 카메라
	TWeakObjectPtr<class AFlappyWhaleCamera> FlappyWhaleCamera;
	// * 게임인스턴스
	TWeakObjectPtr<class UProjectGameInstance> GameInstance;
	// * 아이템 컴포넌트
	/*UPROPERTY(VisibleAnywhere)
		class UItemComponent* ItemComponent;*/

	UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 Score;

	// 점프 속도 변수, 기본값 420
	float JumpSpeed = 600.f;

private: //향상된 입력 시스템
	UPROPERTY(VisibleAnywhere, Category = Input)
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	UPROPERTY(VisibleAnywhere, Category = Input)
		TObjectPtr<class UInputAction> JumpAction;

private:
	UFUNCTION()
		void OnMyOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
public:
	FOnUpdateScoreDelegate OnUpdateScoreDelegate;
	FOnGameOverDelegate OnGameOverDelegate;
public:
	FORCEINLINE int32 GetScore()
	{
		return Score;
	}
};
