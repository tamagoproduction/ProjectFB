// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "Keys.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	AboveObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AboveObstacleMesh"));
	UnderObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnderObstacleMesh"));
	PassCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PassCollision"));

	RootComponent = Root;
	AboveObstacleMesh->SetupAttachment(Root);
	UnderObstacleMesh->SetupAttachment(Root);
	PassCollision->SetupAttachment(Root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (MeshAsset.Succeeded())
	{
		AboveObstacleMesh->SetStaticMesh(MeshAsset.Object);
		UnderObstacleMesh->SetStaticMesh(MeshAsset.Object);
	}


	// Overlap �̺�Ʈ Ȱ��ȭ
	AboveObstacleMesh->SetGenerateOverlapEvents(true);
	UnderObstacleMesh->SetGenerateOverlapEvents(true);

	//ũ�� ����
	AboveObstacleMesh->SetRelativeScale3D(FVector(1, 1, 4));
	UnderObstacleMesh->SetRelativeScale3D(FVector(1, 1, 4));
	//��ġ ����
	AboveObstacleMesh->SetRelativeLocation(FVector(0, 0, 300));
	UnderObstacleMesh->SetRelativeLocation(FVector(0, 0, -300));
	//�±� �߰�
	AboveObstacleMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	UnderObstacleMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);

	//��� �ݸ��� �ʱ� ����
	PassCollision->SetRelativeLocation(FVector::Zero());
	PassCollision->InitSphereRadius(60.f);
	PassCollision->ComponentTags.Add(Keys::GameKeys::Pass);

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AObstacle::Deactivate, 10.f, false);
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Movement = FVector::LeftVector * Speed * DeltaTime;

	SetActorLocation(GetActorLocation() + Movement);
}

void AObstacle::SetActive(bool isActive)
{
	SetActorTickEnabled(isActive);
	SetActorEnableCollision(isActive);
	SetActorHiddenInGame(!isActive);
	bActive = isActive;
	if (isActive)
	{
		FTimerHandle Timer;
		//5�� �� ��Ȱ��ȭ
		GetWorldTimerManager().SetTimer(Timer, this, &AObstacle::Deactivate, 10.f, false);
	}
}

void AObstacle::Deactivate()
{
	SetActive(false); //��Ȱ��ȭ
}

