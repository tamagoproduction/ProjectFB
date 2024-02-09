// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CollisionObstacle.h"
#include "Components/BoxComponent.h"
#include "Utile/Keys.h"

ACollisionObstacle::ACollisionObstacle()
{
	PrimaryActorTick.bCanEverTick = false;
	ObstacleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleCollision"));
	RootComponent = ObstacleCollision;
	ObstacleCollision->ComponentTags.Add(Keys::GameKeys::Obstacle);
	ObstacleCollision->SetBoxExtent(FVector(50, 2000, 50));
}

// Called when the game starts or when spawned
void ACollisionObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}


