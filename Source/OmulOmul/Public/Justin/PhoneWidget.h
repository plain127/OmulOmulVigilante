// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"
#include "PhoneWidget.generated.h"

/**
 *
 */

class UEditableText;
class AOmulOmulCharacter;
class UButton;
class AAudioCaptureActor;
class UImage;
class UTextBlock;

UCLASS()
class OMULOMUL_API UPhoneWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:

	UFUNCTION(BlueprintCallable)
	void UpdateCallTimeText(float CallTime);

	UFUNCTION(BlueprintImplementableEvent)
	void Update(float CallTime);

	void Init(AAudioCaptureActor* _AudioCapture, AOmulOmulCharacter* _Character);
	void RetrievePhone();
	void PulloutPhone();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_CallTime;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCapturing;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_StartCall;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TObjectPtr<USoundBase> StartCallSound;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TObjectPtr<USoundBase> StopCallSound;
private:
	UFUNCTION()
	void OnStartCall();

	TObjectPtr<AOmulOmulCharacter> OmulTest;
	bool bIsRetrieving;



	TObjectPtr<AAudioCaptureActor> AudioCapture;
};
