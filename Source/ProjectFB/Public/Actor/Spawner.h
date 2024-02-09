// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class PROJECTFB_API ASpawner : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Objstacle")
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, Category = "Objstacle")
	TArray<class AObstacle*> Obstacles;
	UPROPERTY(VisibleAnywhere, Category = "Objstacle")
	FVector SpawnPos;

	FTimerHandle Timer;
private:
	UFUNCTION()
	void SpawnObstacle();
	//UFUNCTION()
	//void SpawnItem();
};
