// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Obstacle.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SpawnPos = FVector(0, 2000, 0);

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(Timer, this, &ASpawner::SpawnObstacle, 5.f, true);
}

void ASpawner::SpawnObstacle()
{
	if (Obstacles.Num() != 0)
	{
		for (AObstacle* item : Obstacles)
		{
			if (!item->GetIsActive())
			{
				item->SetActive(true);
				item->SetActorRelativeLocation(SpawnPos);
				return;
			}
		}
	}
	
	FTransform Transform;
	Transform.SetLocation(SpawnPos);
	AObstacle* Obj = GetWorld()->SpawnActor<AObstacle>(AObstacle::StaticClass(), Transform);
	Obstacles.Add(Obj);

}


