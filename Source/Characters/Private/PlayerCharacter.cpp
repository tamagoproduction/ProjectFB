// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "FlappyWhaleCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Obstacle.h"
#include "FlappyWhaleGameMode.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectGameInstance.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Keys.h"
#include "Item.h"
#include "ItemComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 시작위치 변경
	RootComponent->SetWorldLocation(FVector(50.f, -600.f, 300.f));

	// 고래 메시 가져오기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> WhaleMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Whale/Mesh/Whale_High.Whale_High'"));
	if (WhaleMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(WhaleMesh.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0, -30, 0));
	GetMesh()->SetRelativeRotation(FRotator(180, 0, 180));
	GetMesh()->SetRelativeScale3D(FVector(10));
	

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
	// * 애니메이션 블루프린트
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Whale/ABP_Player.ABP_Player_C'"));
	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimAsset.Class);
	}

	// * 점프 몽타주
	ConstructorHelpers::FObjectFinder<UAnimMontage> JumpAsset(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Whale/Whale_Jump_Mtg.Whale_Jump_Mtg'"));
	if (JumpAsset.Succeeded())
	{
		JumpMontage = JumpAsset.Object;
	}

	// ItemComponent
	//ItemComponent = CreateDefaultSubobject<UItemComponent>(TEXT("ItemComponent"));

	// 캡슐 시각화 옵션
	GetCapsuleComponent()->SetHiddenInGame(false);

	// 캡슐 컴포넌트 크기 변경
	GetCapsuleComponent()->SetCapsuleSize(25.f, 25.f);
	// 캡슐 collision profile 변경
	GetCapsuleComponent()->SetCollisionProfileName("OverlapAllDynamic");
	// 캡슐에 Overlap 이벤트 활성화
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// Overlap 함수 연결
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnMyOverlap);

	// 연속 점프 카운트
	JumpMaxCount = INT_MAX;
	// 점프 속도 조절
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;

	Score = 0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	// * 카메라 액터 생성
	FlappyWhaleCamera = GetWorld()->SpawnActor<AFlappyWhaleCamera>();
	if (FlappyWhaleCamera.IsValid())
	{
		// 컨트롤러 가져오기
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (IsValid(PlayerController))
		{
			// 시야를 해당 카메라로 설정
			PlayerController->SetViewTargetWithBlend(FlappyWhaleCamera.Get());
			
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
	// * 회전 구현
	if (GetVelocity().Z > 0)
	{
		SetActorRotation(FRotator(0, 0, FMath::Lerp(GetActorRotation().Roll, -40.f, GetVelocity().Z * 0.02f * DeltaTime)));
	}
	else
	{
		SetActorRotation(FRotator(0, 0, FMath::Lerp(GetActorRotation().Roll, 90.f, -GetVelocity().Z * 0.005f * DeltaTime)));
	}
	FString message2 = FString::Printf(TEXT("%f, %f, %f"), GetVelocity().X, GetVelocity().Y, GetVelocity().Z);
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, message2);
	FString message = FString::Printf(TEXT("%f, %f, %f"), GetActorRotation().Roll, GetActorRotation().Pitch, GetActorRotation().Yaw);
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Purple, message);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input != nullptr)
	{
		//키를 눌렀을때
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		//키를 땟을때
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &Super::StopJumping);
	}
	// * 점프 기능 외에 다른 조작법이 존재하지 않는다

}

void APlayerCharacter::Jump()
{
	Super::Jump();
	PlayAnimMontage(JumpMontage);
}

void APlayerCharacter::OnMyOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		FString message = FString::Printf(TEXT("Comp Name : %s"), *OtherComp->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, message);
	}

	//충돌 상대가 유효하고 장애물 태그를 가지고 있다면
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Obstacle))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Obstacle Collision Overlap"));

		AFlappyWhaleGameMode* FlappyWhaleGameMode = Cast<AFlappyWhaleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(FlappyWhaleGameMode))
		{
			if (GameInstance->GetBestScore() < Score)
			{
				GameInstance->SetBestScore(Score); //점수를 게임인스턴스에 저장
			}
			FString message2 = FString::Printf(TEXT("Score : %d"), GameInstance->GetBestScore());
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, message2);

			// 게임 오버
			//FlappyWhaleGameMode->OnGameOver();
			OnGameOverDelegate.Broadcast();
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			//TODO : 죽은경우 서버로 점수 저장
		}
	}
	// pass 충돌
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Pass))
	{
		Score++;
		if (OnUpdateScoreDelegate.IsBound())
		{
			OnUpdateScoreDelegate.Broadcast(Score);
		}
		FString message = FString::Printf(TEXT("Score : %d"), Score);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, message);

		FString message2 = FString::Printf(TEXT("Score : %d"), GameInstance->GetBestScore());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, message2);
		
	}
	// 아이템 충돌
	/*if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Item))
	{
		if (IsValid(ItemComponent))
		{
			AItem* Item = Cast<AItem>(OtherActor);
			if(IsValid(Item))
				ItemComponent->CheckItem(Item);
		}
	}*/
}

