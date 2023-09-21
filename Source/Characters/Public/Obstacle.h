// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class CHARACTERS_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
		TObjectPtr<class USceneComponent> Root; //��Ʈ ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
		TObjectPtr<class UStaticMeshComponent> AboveObstacleMesh; //���� ��ֹ�
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
		TObjectPtr<class UStaticMeshComponent> UnderObstacleMesh; //�Ʒ� ��ֹ�
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
		TObjectPtr<class USphereComponent> PassCollision; //��� �浹üũ
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float Speed = 700.f;

	// ���� ���� �ٷ� ����ϹǷ� �⺻���� true�� ����
	bool bActive = true;
public:
	void SetActive(bool isActive); //Ȱ��ȭ ��Ȱ��ȭ
	void Deactivate(); //��Ȱ��ȭ
public:
	FORCEINLINE bool GetIsActive()
	{
		return bActive;
	}
};
