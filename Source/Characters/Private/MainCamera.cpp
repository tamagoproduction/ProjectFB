// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent->SetWorldLocation(FVector(-1000.f, 0.f, 300.f));
}