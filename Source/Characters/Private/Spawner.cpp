// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Obstacle.h"
#include "Kismet/KismetMathLibrary.h"

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
	
	GetWorldTimerManager().SetTimer(Timer, this, &ASpawner::SpawnObstacle, 1.f, true);
}

void ASpawner::SpawnObstacle()
{
	// ��� ������ �����ϰ� �����ϱ� ���� ���� ����
	int32 RandValue = UKismetMathLibrary::RandomIntegerInRange(-3, 3);
	// Z��ġ�� ����
	float RandZPos = 50.f * RandValue;
	SpawnPos.Z = RandZPos;

	if (Obstacles.Num() != 0)
	{
		for (AObstacle* item : Obstacles)
		{
			if (!item->GetIsActive())
			{
				item->SetActive(true);
				item->SetActorLocation(SpawnPos);

				return;
			}
		}
	}
	
	FTransform Transform;
	Transform.SetLocation(SpawnPos);
	AObstacle* Obj = GetWorld()->SpawnActor<AObstacle>(AObstacle::StaticClass(), Transform);
	Obstacles.Add(Obj);
	
}

void ASpawner::SpawnItem()
{
}


