// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStruct.generated.h"

// 아이템 효과 열거형
UENUM(BlueprintType)
enum class EItem : uint8
{
	None UMETA(Display = "None"),
	Slower UMETA(Display = "Slower"),
	Faster UMETA(Display = "Faster"),
	Invincible UMETA(Display = "Invincible")
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FItemData() {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ItemName = "Default";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UStaticMesh* ItemMesh = nullptr;

	// 아이템을 먹었을 때 나타낼 효과
	// 해당 변수를 통해 ItemComponent가 추가 효과를 적용
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EItem ItemType = EItem::None;

};
/**
 * 
 */
class CHARACTERS_API ItemStruct
{
public:
	ItemStruct();
	~ItemStruct();
};
