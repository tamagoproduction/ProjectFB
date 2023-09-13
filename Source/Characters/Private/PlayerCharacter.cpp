// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Obstacle.h"
#include "GameGameMode.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectGameInstance.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Keys.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 시작위치 변경
	RootComponent->SetWorldLocation(FVector(50.f, -600.f, 300.f));

	// FBMesh 컴포넌트 생성 및 Root로 임시 지정
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>("FBMesh");
	if (IsValid(MyMesh))
	{
		MyMesh->SetupAttachment(RootComponent);
		// 큐브 스태틱 메시 가져오기
		ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		if (tempCube.Succeeded() && IsValid(tempCube.Object))
		{
			MyMesh->SetStaticMesh(tempCube.Object);
			// 스케일 조절
			MyMesh->SetRelativeScale3D(FVector(0.5f));
			// 큐브를 폰처럼 행동하게 변경
			MyMesh->SetCollisionProfileName("Pawn");
		}
	}

	// * 입력시스템
	//#include "InputMappingContext.h"를 해야 FObjectFinder로 로드가 가능
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/InputSystem/IMC_Defaut.IMC_Defaut'"));
	if (IMCAsset.Succeeded())
	{
		DefaultMappingContext = IMCAsset.Object;
	}
	//#include "InputAction.h"를 해야 FObjectFinder로 로드가 가능
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/InputSystem/IA_Jump.IA_Jump'"));
	{
		JumpAction = JumpActionAsset.Object;
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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnMyOverlap);

	// 연속 점프 카운트
	JumpMaxCount = INT_MAX;
	// 점프 속도 조절, 기본값 420
	GetCharacterMovement()->JumpZVelocity = 500.f;

	Score = 0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	// * 카메라 액터 생성
	MainCamera = GetWorld()->SpawnActor<AMainCamera>();
	if (MainCamera.IsValid())
	{
		// 컨트롤러 가져오기
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (IsValid(PlayerController))
		{
			// 시야를 해당 카메라로 설정
			PlayerController->SetViewTargetWithBlend(MainCamera.Get());
			
			// * 향상된 입력으로 컨텍스트 변경
			UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			if (SubSystem != nullptr)
			{
				SubSystem->AddMappingContext(DefaultMappingContext, 0);
			}

		}
	}
	
	GameInstance = Cast<UProjectGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input != nullptr)
	{
		//키를 눌렀을때
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &Super::Jump);
		//키를 땟을때
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &Super::StopJumping);
	}
	// * 점프 기능 외에 다른 조작법이 존재하지 않는다

}

void APlayerCharacter::OnMyOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

		AGameGameMode* GameGameMode = Cast<AGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(GameGameMode))
		{
			if (GameInstance->GetBestScore() > Score)
			{
				GameInstance->SetBestScore(Score); //점수를 게임인스턴스에 저장
			}

			// 게임 오버
			GameGameMode->OnGameOver();
			//TODO : 죽은경우 서버로 점수 저장
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
	}
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Pass))
	{
		Score++;
		if (OnUpdateScoreDelegate.IsBound())
		{
			OnUpdateScoreDelegate.Broadcast(Score);
		}
		FString message = FString::Printf(TEXT("Score : %d"), Score);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, message);
	}
}

