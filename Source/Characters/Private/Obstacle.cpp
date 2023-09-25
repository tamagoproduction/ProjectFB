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


	// Overlap �̺�Ʈ Ȱ��ȭ
	AbovePillarMesh->SetGenerateOverlapEvents(true);
	AboveCapMesh->SetGenerateOverlapEvents(true);
	UnderPillarMesh->SetGenerateOverlapEvents(true);
	UnderCapMesh->SetGenerateOverlapEvents(true);

	//ũ�� ����
	AbovePillarMesh->SetRelativeScale3D(FVector(70));
	AboveCapMesh->SetRelativeScale3D(FVector(70));
	UnderPillarMesh->SetRelativeScale3D(FVector(70));
	UnderCapMesh->SetRelativeScale3D(FVector(70));

	//ȸ��
	Above->SetRelativeRotation(FRotator(180, 0, 0));

	//��ġ ����
	Above->SetRelativeLocation(FVector(0, 0, 900));
	Under->SetRelativeLocation(FVector(0, 0, -900));

	//�±� �߰�
	AbovePillarMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	AboveCapMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	UnderPillarMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);
	UnderCapMesh->ComponentTags.Add(Keys::GameKeys::Obstacle);

	//��� �ݸ��� �ʱ� ����
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
		//5�� �� ��Ȱ��ȭ
		GetWorldTimerManager().SetTimer(Timer, this, &AObstacle::Deactivate, 10.f, false);
	}
}

void AObstacle::Deactivate()
{
	SetActive(false); //��Ȱ��ȭ
}