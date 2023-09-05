// Fill out your copyright notice in the Description page of Project Settings.

//#include "Camera/CameraComponent.h"
#include "MainCamera.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

#include "FBCharacter.h"

// Sets default values
AFBCharacter::AFBCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���� ��ġ�� ���� ����
	RootComponent->SetWorldLocation(FVector(0.f, -600.f, 300.f));

	// FBMesh ������Ʈ ���� �� Root�� �ӽ� ����
	FBMesh = CreateDefaultSubobject<UStaticMeshComponent>("FBMesh");
	if (IsValid(FBMesh))
	{
		// Root(Camera)�� ���̱�
		FBMesh->SetupAttachment(RootComponent);

		// ť�� ����ƽ �޽� ��������
		ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		if (tempCube.Succeeded() && IsValid(tempCube.Object))
		{
			FBMesh->SetStaticMesh(tempCube.Object);
			FBMesh->SetRelativeScale3D(FVector(0.5f));
		}
	}

	// ī�޶�
	/*FBCamera = CreateDefaultSubobject<UCameraComponent>("FBCamera");
	if (IsValid(FBCamera))
	{
		// RootComponent�� ����(������ ������� �ʵ���)
		FBCamera->SetupAttachment(FBMesh);
		FBCamera->SetWorldLocation(FVector(-500.f, 0.f, 100.f));
	}*/

	// �����߿� �� ������ �����ϵ��� ī��Ʈ�� �������� ����
	JumpMaxCount = INT_MAX;

	// ĸ�� ũ�� ����
	GetCapsuleComponent()->SetCapsuleSize(40.f, 40.f);
	// ���� �⺻�� 420.f, �� ���� �����ϵ��� ��������
	//GetCharacterMovement()->JumpZVelocity = 600.f;
}

// Called when the game starts or when spawned
void AFBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ī�޶� ����
	MainCamera = GetWorld()->SpawnActor<AMainCamera>();
	if (MainCamera.IsValid())
	{
		Cast<APlayerController>(GetController())->SetViewTargetWithBlend(MainCamera.Get());
	}
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &Super::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &Super::StopJumping);
}