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

	// ������ġ ����
	RootComponent->SetWorldLocation(FVector(50.f, -600.f, 300.f));

	// FBMesh ������Ʈ ���� �� Root�� �ӽ� ����
	FBMesh = CreateDefaultSubobject<UStaticMeshComponent>("FBMesh");
	if (IsValid(FBMesh))
	{
		FBMesh->SetupAttachment(RootComponent);
		// ť�� ����ƽ �޽� ��������
		ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		if (tempCube.Succeeded() && IsValid(tempCube.Object))
		{
			FBMesh->SetStaticMesh(tempCube.Object);
			// ������ ����
			FBMesh->SetRelativeScale3D(FVector(0.5f));
			// ť�긦 ��ó�� �ൿ�ϰ� ����
			FBMesh->SetCollisionProfileName("Pawn");
		}
	}

	// ĸ�� �ð�ȭ �ɼ�
	GetCapsuleComponent()->SetHiddenInGame(false);

	// ĸ�� ������Ʈ ũ�� ����
	GetCapsuleComponent()->SetCapsuleSize(40.f, 40.f);
	// ĸ�� collision profile ����
	GetCapsuleComponent()->SetCollisionProfileName("OverlapAllDynamic");
	// ĸ���� Overlap �̺�Ʈ Ȱ��ȭ
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// Overlap �Լ� ����
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::MyOverlap);

	// ���� ���� ī��Ʈ
	JumpMaxCount = INT_MAX;
	// ���� �ӵ� ����, �⺻�� 420
	GetCharacterMovement()->JumpZVelocity = 500.f;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ī�޶� ���� ����
	MainCamera = GetWorld()->SpawnActor<AMainCamera>();
	if (MainCamera.IsValid())
	{
		// ��Ʈ�ѷ� ��������
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (IsValid(PlayerController))
		{
			// �þ߸� �ش� ī�޶�� ����
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

	// * ���� ��� �ܿ� �ٸ� ���۹��� �������� �ʴ´�
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

	//�浹�� ��밡 ��ȿ�ϰ� ��ֹ� �±׸� ������ �ִٸ�
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Obstacle))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Obstacle Collision Overlap"));

		AProjectFBGameModeBase* GameMode = Cast<AProjectFBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(GameMode))
		{
			// ���� ����
			GameMode->GameOver();
			//TODO : ������� ������ ���� ����
		}
	}
	if (IsValid(OtherActor) && OtherComp->ComponentHasTag(Keys::GameKeys::Pass))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Pass Collision Overlap"));
		//TODO : ���� ���� ���� �߰�
	}
}

