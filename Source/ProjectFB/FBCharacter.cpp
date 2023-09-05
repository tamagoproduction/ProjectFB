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

	// 시작 위치를 높게 설정
	RootComponent->SetWorldLocation(FVector(0.f, -600.f, 300.f));

	// FBMesh 컴포넌트 생성 및 Root로 임시 지정
	FBMesh = CreateDefaultSubobject<UStaticMeshComponent>("FBMesh");
	if (IsValid(FBMesh))
	{
		// Root(Camera)에 붙이기
		FBMesh->SetupAttachment(RootComponent);

		// 큐브 스태틱 메시 가져오기
		ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		if (tempCube.Succeeded() && IsValid(tempCube.Object))
		{
			FBMesh->SetStaticMesh(tempCube.Object);
			FBMesh->SetRelativeScale3D(FVector(0.5f));
		}
	}

	// 카메라
	/*FBCamera = CreateDefaultSubobject<UCameraComponent>("FBCamera");
	if (IsValid(FBCamera))
	{
		// RootComponent로 설정(점프에 영향받지 않도록)
		FBCamera->SetupAttachment(FBMesh);
		FBCamera->SetWorldLocation(FVector(-500.f, 0.f, 100.f));
	}*/

	// 점프중에 또 점프가 가능하도록 카운트를 무한으로 설정
	JumpMaxCount = INT_MAX;

	// 캡슐 크기 조정
	GetCapsuleComponent()->SetCapsuleSize(40.f, 40.f);
	// 점프 기본값 420.f, 더 높게 점프하도록 수정가능
	//GetCharacterMovement()->JumpZVelocity = 600.f;
}

// Called when the game starts or when spawned
void AFBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 카메라 생성
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

	// * 점프 기능 외에 다른 조작법이 존재하지 않는다
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &Super::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &Super::StopJumping);
}