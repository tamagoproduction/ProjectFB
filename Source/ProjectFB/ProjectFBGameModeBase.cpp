// Copyright Epic Games, Inc. All Rights Reserved.

#include "FBCharacter.h"

#include "ProjectFBGameModeBase.h"

AProjectFBGameModeBase::AProjectFBGameModeBase()
{
	DefaultPawnClass = AFBCharacter::StaticClass();
}