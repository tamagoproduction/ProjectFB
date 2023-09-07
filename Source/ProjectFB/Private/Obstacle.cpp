// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "Keys.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	

	// Overlap 이벤트 활성화
	AboveObstacleMesh->SetGenerateOverlapEvents(true);
	UnderObstacleMesh->SetGenerateOverlapEvents(true);

	//크기 변경
	AboveObstacleMesh->SetRelativeScale3D(FVector(1, 1, 4));
	UnderObstacleMesh->SetRelativeScale3D(FVector(1, 1, 4));
	//위치 변경
	AboveObstacleMesh->SetRelativeLocation(FVector(0, 0, 300));
	UnderObstacleMesh->SetRelativeLocation(FVector(0, 0, -300));
	//태그 추가
	AboveObstacleMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	UnderObstacleMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);

	//가운데 콜리전 초기 설정
	PassCollision->SetRelativeLocation(FVector::Zero());
	PassCollision->InitSphereRadius(60.f);
	PassCollision->ComponentTags.Add(Keys::GameKeys::Pass);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector Movement = FVector::ForwardVector * Speed * DeltaTime;
	FVector Movement = FVector(0.f, -1.f, 0.f) * Speed * DeltaTime;

	SetActorLocation(GetActorLocation() + Movement);
}
