// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionObstacle.generated.h"

UCLASS()
class PROJECTFB_API ACollisionObstacle : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ACollisionObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
	TObjectPtr<class UBoxComponent> ObstacleCollision; //장애물 콜리전

};
