// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingUI.generated.h"

/**
 *
 */
UCLASS()
class OMULOMUL_API UEndingUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResultText;
	
	UFUNCTION()
	void SetText(FString result);
};
