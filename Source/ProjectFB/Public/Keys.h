// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace Keys
{
	namespace LevelKeys
	{
		const FName MainMap = TEXT("Main");
		const FName FlappyWhaleMap = TEXT("FlappyWhale");
	}
	namespace GameKeys
	{
		const FName Obstacle = TEXT("Obstacle");
		const FName Pass = TEXT("Pass");
	}
}