// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"

#include "FBCharacter.h"

// Sets default values
AFBCharacter::AFBCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// FBMesh ������Ʈ ���� �� Root�� �ӽ� ����
	FBMesh = CreateDefaultSubobject<UStaticMeshComponent>("FBMesh");
	FBMesh->SetupAttachment(RootComponent);

	// ť�� ����ƽ �޽� ��������
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempCube.Succeeded() && IsValid(tempCube.Object))
	{
		FBMesh->SetStaticMesh(tempCube.Object);
	}

	// FBCamera ������Ʈ ���� �� FBMesh�� ���̱�
	FBCamera = CreateDefaultSubobject<UCameraComponent>("FBCamera");
	FBCamera->SetupAttachment(FBMesh);

	// ī�޶� ��ġ�� �ָ� ����߸���
	FBCamera->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AFBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// * ���� ��� �ܿ� �ٸ� ���۹��� �������� �ʴ´�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFBCharacter::FBJump);
}

void AFBCharacter::FBJump()
{
	//Super::Jump();
	// ACharacter Ŭ������ Jump�Լ��� �����Ͽ� �ش� �÷��׸� �����Ͽ� ���
	bPressedJump = true;
}