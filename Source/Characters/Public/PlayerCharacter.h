// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CHARACTERS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	// * Mesh
// �ӽ÷� ����� cube������ static mesh �̿�
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		TObjectPtr<UStaticMeshComponent> MyMesh;

	// * ī�޶�
	TWeakObjectPtr<class AMainCamera> MainCamera;
private: //���� �Է� �ý���
	UPROPERTY(VisibleAnywhere, Category = Input)
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	UPROPERTY(VisibleAnywhere, Category = Input)
		TObjectPtr<class UInputAction> JumpAction;

private:
	UFUNCTION()
		void OnMyOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
};
