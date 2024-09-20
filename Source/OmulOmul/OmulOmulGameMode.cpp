// Copyright Epic Games, Inc. All Rights Reserved.

#include "OmulOmulGameMode.h"
#include "OmulOmulCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOmulOmulGameMode::AOmulOmulGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
