// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FBCharacter.generated.h"

UCLASS()
class PROJECTFB_API AFBCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFBCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// * Mesh
	// �ӽ÷� ����� cube������ static mesh �̿�
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FBMesh;

	// * ī�޶�
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FBCamera;

private:
	// * ĳ���� ������ ���� �Լ�
	UFUNCTION()
	void FBJump();
};
