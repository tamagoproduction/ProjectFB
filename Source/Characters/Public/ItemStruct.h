// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FItemData() {}

	UPROPERTY(BlueprintReadWrite)
		FString ItemName;
	UPROPERTY(BlueprintReadWrite)
		class UStaticMesh* ItemMesh;
	
	// 아이템을 먹었을 때 나타낼 효과
	// player에 enum으로 state를 만들어 줄 것인가?
	// 또는 함수 실행을 할 것인가?
	// 고민 필요
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
