// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingUI.h"
#include "Components/TextBlock.h"

void UEndingUI::SetText(FString result)
{
	ResultText->SetText(FText::FromString(result));
}
