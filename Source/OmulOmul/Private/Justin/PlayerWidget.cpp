// Fill out your copyright notice in the Description page of Project Settings.


#include "Justin/PlayerWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HorizontalBox_0->SetVisibility(ESlateVisibility::Collapsed);
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UPlayerWidget::DisplayTime(float TimeLeft)
{
	int Minute = TimeLeft / 60.f;
	int Second = int(TimeLeft) % 60;

	FText MinText = FText::FromString(FString::Printf(TEXT("%.0f"), float(Minute)));
	FText SecText = FText::FromString(FString::Printf(TEXT("%.0f"), float(Second)));
	
	Text_Minute->SetText(MinText);
	Text_Second->SetText(SecText);
}

void UPlayerWidget::SetVisi()
{
	HorizontalBox_0->SetVisibility(ESlateVisibility::HitTestInvisible);
}
