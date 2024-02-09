// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WhaleCameraActor.h"
#include "Camera/CameraComponent.h"

AWhaleCameraActor::AWhaleCameraActor()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent->SetWorldLocation(FVector(-1000.f, 0.f, 0.f));

	UCameraComponent* Camera = GetCameraComponent();
	if (!IsValid(Camera)) return;
	Camera->SetConstraintAspectRatio(false);
	Camera->SetFieldOfView(100);
}
