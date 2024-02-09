// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class PROJECTFB_API AObstacle : public AActor
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
	TObjectPtr<class USceneComponent> Root; //루트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class USceneComponent> Above; //루트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class USceneComponent> Under; //루트 컴포넌트

	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class UStaticMeshComponent> AbovePillarMesh; //위 기둥
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class UStaticMeshComponent> AboveCapMesh; //위 기둥 캡
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class UStaticMeshComponent> UnderPillarMesh; //아래 기둥
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class UStaticMeshComponent> UnderCapMesh; //아래 기둥 캡
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class UCapsuleComponent> PassCollision; //가운데 충돌체크
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	float Speed = 700.f;

	// 생성 직후 바로 사용하므로 기본값을 true로 설정
	bool bActive = true;

	FTimerHandle Timer;
public:
	void SetActive(bool isActive); //활성화 비활성화
	void Deactivate(); //비활성화
public:
	FORCEINLINE bool GetIsActive()
	{
		return bActive;
	}
};
