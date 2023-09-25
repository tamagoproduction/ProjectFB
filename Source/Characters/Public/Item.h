// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemStruct.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class CHARACTERS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// * 아이템 데이터
	UPROPERTY()
		class UDataTable* ItemDataTable;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
		struct FDataTableRowHandle ItemRowHandle;
	FItemData ItemData;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* ItemMesh;

public:
	FItemData GetItemData() const { return ItemData; }


};
