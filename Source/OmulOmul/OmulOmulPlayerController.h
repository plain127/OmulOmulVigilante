// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmulOmulPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class OMULOMUL_API AOmulOmulPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void ToPhoneInput();
	void ToMovementInput();

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* IMC_Phone;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
