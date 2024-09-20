// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioCaptureActor.generated.h"

class UAudioCaptureComponent;

UCLASS()
class OMULOMUL_API AAudioCaptureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAudioCaptureActor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartCapture();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopCapture();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	TObjectPtr<UAudioCaptureComponent> AudioCaptureComp;
};
