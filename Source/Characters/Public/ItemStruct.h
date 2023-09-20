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
	
	// �������� �Ծ��� �� ��Ÿ�� ȿ��
	// player�� enum���� state�� ����� �� ���ΰ�?
	// �Ǵ� �Լ� ������ �� ���ΰ�?
	// ��� �ʿ�
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
