// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Components/CapsuleComponent.h"
#include "MainCharacter.h"
#include "Keys.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Above = CreateDefaultSubobject<USceneComponent>(TEXT("Above"));
	Under = CreateDefaultSubobject<USceneComponent>(TEXT("Under"));
	AbovePillarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AboveObstacleMesh"));
	AboveCapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AbovePillarCapMesh"));
	UnderPillarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnderObstacleMesh"));
	UnderCapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnderPillarCapMesh"));
	PassCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PassCollision"));

	RootComponent = Root;
	Above->SetupAttachment(Root);
	Under->SetupAttachment(Root);
	PassCollision->SetupAttachment(Root);

	AbovePillarMesh->SetupAttachment(Above);
	AboveCapMesh->SetupAttachment(Above);

	UnderCapMesh->SetupAttachment(Under);
	UnderPillarMesh->SetupAttachment(Under);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PillarMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Pillar/Mesh/ClassicColumnC_LOD0_ClassicColumnPillarC_LOD_0.ClassicColumnC_LOD0_ClassicColumnPillarC_LOD_0'"));
	if (PillarMeshAsset.Succeeded())
	{
		AbovePillarMesh->SetStaticMesh(PillarMeshAsset.Object);
		UnderPillarMesh->SetStaticMesh(PillarMeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CapMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Pillar/Mesh/ClassicColumnC_LOD0_ClassicColumnCapC_LOD_0.ClassicColumnC_LOD0_ClassicColumnCapC_LOD_0'"));
	if (CapMeshAsset.Succeeded())
	{
		AboveCapMesh->SetStaticMesh(CapMeshAsset.Object);
		UnderCapMesh->SetStaticMesh(CapMeshAsset.Object);
	}


	// Overlap 이벤트 활성화
	AbovePillarMesh->SetGenerateOverlapEvents(true);
	AboveCapMesh->SetGenerateOverlapEvents(true);
	UnderPillarMesh->SetGenerateOverlapEvents(true);
	UnderCapMesh->SetGenerateOverlapEvents(true);

	//크기 변경
	AbovePillarMesh->SetRelativeScale3D(FVector(70));
	AboveCapMesh->SetRelativeScale3D(FVector(70));
	UnderPillarMesh->SetRelativeScale3D(FVector(70));
	UnderCapMesh->SetRelativeScale3D(FVector(70));

	//회전
	Above->SetRelativeRotation(FRotator(180, 0, 0));

	//위치 변경
	Above->SetRelativeLocation(FVector(0, 0, 900));
	Under->SetRelativeLocation(FVector(0, 0, -900));

	//태그 추가
	AbovePillarMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	AboveCapMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	UnderPillarMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	UnderCapMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);

	//가운데 콜리전 초기 설정
	PassCollision->SetRelativeLocation(FVector::Zero());
	PassCollision->InitCapsuleSize(50, 700);
	PassCollision->ComponentTags.Add(Keys::GameKeys::Pass);
	PassCollision->SetHiddenInGame(false);
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
		//5초 후 비활성화
		GetWorldTimerManager().SetTimer(Timer, this, &AObstacle::Deactivate, 10.f, false);
	}
}

void AObstacle::Deactivate()
{
	SetActive(false); //비활성화
}