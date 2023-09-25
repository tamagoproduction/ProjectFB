// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemComponent.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemComponent::CheckItem(AItem* item)
{
	EItem ItemType = item->GetItemData().ItemType;

	switch (ItemType)
	{
	case EItem::Slower:
		ChangeGameSpeed(-0.1);
		break;
	case EItem::Faster:
		ChangeGameSpeed(0.1);
		break;
	case EItem::Invincible:
		break;
	}
}

void UItemComponent::ChangeGameSpeed(float deltaSpeed)
{
	if (GetWorld())
	{
		float GameSpeed = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
		GameSpeed += deltaSpeed;
		// 하한선
		if (GameSpeed < 0.5f)
			GameSpeed = 0.5f;
		// 상한선
		if (GameSpeed > 2.f)
			GameSpeed = 2.f;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), GameSpeed);
	}
}

void UItemComponent::Invinsible()
{
}

