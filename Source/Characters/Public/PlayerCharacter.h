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
// �ӽ÷� ����� cube������ static mesh �̿�
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		TObjectPtr<class UStaticMeshComponent> MyMesh;

	// * ī�޶�
	TWeakObjectPtr<class AFlappyWhaleCamera> FlappyWhaleCamera;
	// * �����ν��Ͻ�
	TWeakObjectPtr<class UProjectGameInstance> GameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 Score;
private: //���� �Է� �ý���
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
