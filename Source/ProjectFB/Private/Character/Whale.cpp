// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Whale.h"
#include "Character/WhaleCameraActor.h"
#include "Actor/Obstacle.h"
#include "Game/WhaleGameInstance.h"
#include "Game/WhaleGameMode.h"
#include "Utile/Keys.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Sound/SoundCue.h"

// Sets default values
AWhale::AWhale()
{
	PrimaryActorTick.bCanEverTick = true;
	// * ������ġ
	RootComponent->SetWorldLocation(FVector(50.f, -250.f, 300.f));

	// * �޽�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> WhaleMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Whale/Mesh/Whale_High.Whale_High'"));
	if (WhaleMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(WhaleMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, -30, 0));
		GetMesh()->SetRelativeRotation(FRotator(180, 0, 180));
		GetMesh()->SetRelativeScale3D(FVector(10));
	}
	
	// * �Է½ý���
	//#include "InputMappingContext.h"�� �ؾ� FObjectFinder�� �ε尡 ����
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/InputSystem/IMC_Defaut.IMC_Defaut'"));
	if (IMCAsset.Succeeded())
	{
		DefaultMappingContext = IMCAsset.Object;
	}
	//#include "InputAction.h"�� �ؾ� FObjectFinder�� �ε尡 ����
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/InputSystem/IA_Jump.IA_Jump'"));
	{
		JumpAction = JumpActionAsset.Object;
	}
	// * �ִϸ��̼� �������Ʈ
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Whale/ABP_Whale.ABP_Whale_C'"));
	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimAsset.Class);
	}

	// * ���� ��Ÿ��
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpAsset(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Whale/MTG_Jump.MTG_Jump'"));
	if (JumpAsset.Succeeded())
	{
		JumpMontage = JumpAsset.Object;
	}

	// * ���� ����
	static ConstructorHelpers::FObjectFinder<USoundCue> JumpSoundAsset(TEXT("/Script/Engine.SoundCue'/Game/Sound/Effect/select_01_Cue.select_01_Cue'"));
	if (JumpSoundAsset.Succeeded())
	{
		JumpSound = JumpSoundAsset.Object;
	}

	// ItemComponent
	//ItemComponent = CreateDefaultSubobject<UItemComponent>(TEXT("ItemComponent"));

	// ĸ�� �ð�ȭ �ɼ�
	GetCapsuleComponent()->SetHiddenInGame(false);

	// ĸ�� ������Ʈ ũ�� ����
	GetCapsuleComponent()->SetCapsuleSize(25.f, 25.f);
	// ĸ�� collision profile ����
	GetCapsuleComponent()->SetCollisionProfileName("OverlapAllDynamic");
	// ĸ���� Overlap �̺�Ʈ Ȱ��ȭ
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// Overlap �Լ� ����
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AWhale::OnWhaleOverlap);

	// ���� ���� ī��Ʈ
	JumpMaxCount = INT_MAX;
	// ���� �ӵ� ����
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;

	Score = 0;
}

// Called when the game starts or when spawned
void AWhale::BeginPlay()
{
	Super::BeginPlay();
	// * ī�޶� ���� ����
	WhaleCamera = GetWorld()->SpawnActor<AWhaleCameraActor>();
	if (IsValid(WhaleCamera))
	{
		// ��Ʈ�ѷ� ��������
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (IsValid(PlayerController))
		{
			// �þ߸� �ش� ī�޶�� ����
			PlayerController->SetViewTargetWithBlend(WhaleCamera.Get());
			// * ���� �Է����� ���ؽ�Ʈ ����
			UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			if (SubSystem != nullptr)
			{
				SubSystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
	GameInstance = Cast<UWhaleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called every frame
void AWhale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// * ȸ�� ����
	if (GetVelocity().Z > 0)
	{
		SetActorRotation(FRotator(0, 0, FMath::Lerp(GetActorRotation().Roll, -40.f, GetVelocity().Z * 0.02f * DeltaTime)));
	}
	else
	{
		SetActorRotation(FRotator(0, 0, FMath::Lerp(GetActorRotation().Roll, 90.f, -GetVelocity().Z * 0.005f * DeltaTime)));
	}
}

// Called to bind functionality to input
void AWhale::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input != nullptr)
	{
		//Ű�� ��������
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AWhale::Jump);
		//Ű�� ������
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &Super::StopJumping);
	}
	// * ���� ��� �ܿ� �ٸ� ���۹��� �������� �ʴ´�
}

void AWhale::Jump()
{
	Super::Jump();
	PlayAnimMontage(JumpMontage);

	UGameplayStatics::PlaySound2D(GetWorld(), JumpSound, GameInstance->EffectSoundValue);
}

void AWhale::OnWhaleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�浹 ��밡 ��ȿ�ϰ� ��ֹ� �±׸� ������ �ִٸ�
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Obstacle))
	{
		AWhaleGameMode* WhaleGameMode = Cast<AWhaleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(WhaleGameMode))
		{
			if (GameInstance->GetBestScore() < Score)
			{
				GameInstance->SetBestScore(Score); //������ �����ν��Ͻ��� ����
			}

			// ���� ����
			//FlappyWhaleGameMode->OnGameOver();
			OnGameOver.Broadcast();
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			//TODO : ������� ������ ���� ����
		}
	}
	// pass �浹
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Pass))
	{
		Score++;
		if (OnUpdateScore.IsBound())
		{
			OnUpdateScore.Broadcast(Score);
		}

	}
	// ������ �浹
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

