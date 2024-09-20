// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UHorizontalBox;

UCLASS()
class OMULOMUL_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void DisplayTime(float TimeLeft);
	void SetVisi();
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override; 

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_Minute;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Second;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox_0;

};
