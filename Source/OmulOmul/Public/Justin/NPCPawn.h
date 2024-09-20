// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NPCPawn.generated.h"

UCLASS()
class OMULOMUL_API ANPCPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANPCPawn();

	UFUNCTION(BlueprintCallable)
	void StartStop();

	UPROPERTY(BlueprintReadOnly)
	bool bStop;
};
