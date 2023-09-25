// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Keys.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ItemMesh
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	if (IsValid(ItemMesh))
	{
		RootComponent = ItemMesh;
		//태그 추가
		ItemMesh->ComponentTags.Add(Keys::GameKeys::Item);
		ItemMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));
	}

	// * 데이터 테이블
	/*ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Item/ItemData.ItemData'"));
	if (DataAsset.Succeeded())
	{
		ItemDataTable = DataAsset.Object;
		ItemRowHandle.DataTable = DataAsset.Object;
		ItemRowHandle.RowName = TEXT("Default");
	}*/
}

void AItem::OnConstruction(const FTransform& Transform)
{
	/*ItemData = *ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");

	if (&ItemData != nullptr && IsValid(ItemMesh))
	{
		TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(ItemData.ItemName));

		if(IsValid(ItemData.ItemMesh))
			ItemMesh->SetStaticMesh(ItemData.ItemMesh);
	}*/
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	//ItemData = *ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");
}