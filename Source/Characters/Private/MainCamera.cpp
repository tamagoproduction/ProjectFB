// Fill out your copyright notice in the Description page of Project Settings.


#include "FlappyWhaleCamera.h"

AFlappyWhaleCamera::AFlappyWhaleCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent->SetWorldLocation(FVector(-1000.f, 0.f, 0.f));
}