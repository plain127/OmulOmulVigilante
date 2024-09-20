// Fill out your copyright notice in the Description page of Project Settings.


#include "Justin/AudioCaptureActor.h"
#include "AudioCaptureComponent.h"

AAudioCaptureActor::AAudioCaptureActor()
{
	PrimaryActorTick.bCanEverTick = true;

	AudioCaptureComp = CreateDefaultSubobject<UAudioCaptureComponent>("AudioCaptureComp");

}