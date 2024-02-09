// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Whale.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateScoreSignature, int32);
DECLARE_MULTICAST_DELEGATE(FOnGameOverSignature);

UCLASS()
class PROJECTFB_API AWhale : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWhale();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
private:
	// * Mesh
	UPROPERTY(VisibleAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> JumpMontage;

	// * 카메라
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class AWhaleCameraActor> WhaleCamera;
	// * 게임인스턴스
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class UWhaleGameInstance> GameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, Category = "Score")
	TObjectPtr<class USoundCue> JumpSound;

	// 점프 속도 변수, 기본값 420
	float JumpSpeed = 600.f;

private: //향상된 입력 시스템
	UPROPERTY(VisibleAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	UPROPERTY(VisibleAnywhere, Category = Input)
	TObjectPtr<class UInputAction> JumpAction;

private:
	UFUNCTION()
	void OnWhaleOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
public:
	FOnUpdateScoreSignature OnUpdateScore;
	FOnGameOverSignature OnGameOver;
public:
	FORCEINLINE int32 GetScore()
	{
		return Score;
	}
};
