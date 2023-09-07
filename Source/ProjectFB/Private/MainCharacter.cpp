// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"

#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Obstacle.h"
#include "../ProjectFBGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Keys.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 시작위치 변경
	RootComponent->SetWorldLocation(FVector(50.f, -600.f, 300.f));

	// FBMesh 컴포넌트 생성 및 Root로 임시 지정
	FBMesh = CreateDefaultSubobject<UStaticMeshComponent>("FBMesh");
	if (IsValid(FBMesh))
	{
		FBMesh->SetupAttachment(RootComponent);
		// 큐브 스태틱 메시 가져오기
		ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		if (tempCube.Succeeded() && IsValid(tempCube.Object))
		{
			FBMesh->SetStaticMesh(tempCube.Object);
			// 스케일 조절
			FBMesh->SetRelativeScale3D(FVector(0.5f));
			// 큐브를 폰처럼 행동하게 변경
			FBMesh->SetCollisionProfileName("Pawn");
		}
	}

	// 캡슐 시각화 옵션
	GetCapsuleComponent()->SetHiddenInGame(false);

	// 캡슐 컴포넌트 크기 변경
	GetCapsuleComponent()->SetCapsuleSize(40.f, 40.f);
	// 캡슐 collision profile 변경
	GetCapsuleComponent()->SetCollisionProfileName("OverlapAllDynamic");
	// 캡슐에 Overlap 이벤트 활성화
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// Overlap 함수 연결
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::MyOverlap);

	// 연속 점프 카운트
	JumpMaxCount = INT_MAX;
	// 점프 속도 조절, 기본값 420
	GetCharacterMovement()->JumpZVelocity = 500.f;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 카메라 액터 생성
	MainCamera = GetWorld()->SpawnActor<AMainCamera>();
	if (MainCamera.IsValid())
	{
		// 컨트롤러 가져오기
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (IsValid(PlayerController))
		{
			// 시야를 해당 카메라로 설정
			PlayerController->SetViewTargetWithBlend(MainCamera.Get());
		}
	}

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// * 점프 기능 외에 다른 조작법이 존재하지 않는다
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &Super::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &Super::StopJumping);
}

void AMainCharacter::MyOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		FString message = FString::Printf(TEXT("Comp Name : %s"), *OtherComp->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, message);
	}

	//충돌상 상대가 유효하고 장애물 태그를 가지고 있다면
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Obstacle))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Obstacle Collision Overlap"));

		AProjectFBGameModeBase* GameMode = Cast<AProjectFBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(GameMode))
		{
			// 게임 오버
			GameMode->GameOver();
			//TODO : 죽은경우 서버로 점수 저장
		}
	}
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Pass))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Pass Collision Overlap"));
		//TODO : 점수 증가 로직 추가
	}
}

