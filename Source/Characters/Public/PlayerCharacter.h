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
private:
	// * Mesh
// 임시로 사용할 cube형태의 static mesh 이용
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		TObjectPtr<class UStaticMeshComponent> MyMesh;

	// * 카메라
	TWeakObjectPtr<class AFlappyWhaleCamera> FlappyWhaleCamera;
	// * 게임인스턴스
	TWeakObjectPtr<class UProjectGameInstance> GameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 Score;
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
