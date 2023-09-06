// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"

#include "FBCharacter.h"

// Sets default values
AFBCharacter::AFBCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// FBMesh 컴포넌트 생성 및 Root로 임시 지정
	FBMesh = CreateDefaultSubobject<UStaticMeshComponent>("FBMesh");
	FBMesh->SetupAttachment(RootComponent);

	// 큐브 스태틱 메시 가져오기
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempCube.Succeeded() && IsValid(tempCube.Object))
	{
		FBMesh->SetStaticMesh(tempCube.Object);
	}

	// FBCamera 컴포넌트 생성 및 FBMesh에 붙이기
	FBCamera = CreateDefaultSubobject<UCameraComponent>("FBCamera");
	FBCamera->SetupAttachment(FBMesh);

	// 카메라 위치를 멀리 떨어뜨리기
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

	// * 점프 기능 외에 다른 조작법이 존재하지 않는다
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFBCharacter::FBJump);
}

void AFBCharacter::FBJump()
{
	//Super::Jump();
	// ACharacter 클래스의 Jump함수를 참고하여 해당 플래그를 공유하여 사용
	bPressedJump = true;
}