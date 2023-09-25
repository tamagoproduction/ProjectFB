// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStruct.generated.h"

// ������ ȿ�� ������
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

	// �������� �Ծ��� �� ��Ÿ�� ȿ��
	// �ش� ������ ���� ItemComponent�� �߰� ȿ���� ����
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
