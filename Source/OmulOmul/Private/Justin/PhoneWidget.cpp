// Fill out your copyright notice in the Description page of Project Settings.


#include "Justin/PhoneWidget.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "OmulOmul/OmulOmulCharacter.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Justin/AudioCaptureActor.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UPhoneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto what = Cast<AOmulOmulCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AOmulOmulCharacter::StaticClass()));
	if (what)
	{
		OmulTest = what;
	}

	bIsCapturing = false;
	Button_StartCall->OnPressed.AddDynamic(this, &UPhoneWidget::OnStartCall);
	Text_CallTime->SetVisibility(ESlateVisibility::Collapsed);
}

void UPhoneWidget::UpdateCallTimeText(float CallTime)
{
	Update(CallTime);
}

void UPhoneWidget::Init(AAudioCaptureActor* _AudioCapture, AOmulOmulCharacter * _Character)
{
	AudioCapture = _AudioCapture;
	OmulTest = _Character;
}

void UPhoneWidget::RetrievePhone()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UPhoneWidget::PulloutPhone()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPhoneWidget::OnStartCall()
{
	if (AudioCapture)
	{
		if (bIsCapturing)
		{
			if (StopCallSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), StopCallSound);
			}
			Text_CallTime->SetVisibility(ESlateVisibility::Collapsed);
			bIsCapturing = false;
			OmulTest->StopCall();
			AudioCapture->StopCapture();
		}
		else
		{
			if (StartCallSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), StartCallSound);
			}
			Text_CallTime->SetVisibility(ESlateVisibility::HitTestInvisible);
			bIsCapturing = true;
			OmulTest->StartCall();
			AudioCapture->StartCapture();
		}
	}
}
