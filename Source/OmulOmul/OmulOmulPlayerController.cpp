// Copyright Epic Games, Inc. All Rights Reserved.


#include "OmulOmulPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AOmulOmulPlayerController::ToPhoneInput()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if (Subsystem)
	{
		Subsystem->RemoveMappingContext(InputMappingContext);
		Subsystem->AddMappingContext(IMC_Phone, 0);
	}

}

void AOmulOmulPlayerController::ToMovementInput()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->RemoveMappingContext(IMC_Phone);
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AOmulOmulPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

