// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationManager.h"
#include "Citizen.h"
#include "../OmulOmulCharacter.h"
#include "BallonActor.h"
#include "HttpActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASimulationManager::ASimulationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Alerted = false;
}

// Called when the game starts or when spawned
void ASimulationManager::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

// Called every frame
void ASimulationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Player || !Target) return;

	distance = Player->GetActorLocation() - Target->GetActorLocation();

	CurrentTime += DeltaTime;
	if (CurrentTime >= RecordingTime) {
		CurrentTime = 0;
		RecordCount++;
		Total += distance.Size();
	}
}


double ASimulationManager::GetTotal() const
{
	return Total;
}

int32 ASimulationManager::GetRecordCount() const
{
	return RecordCount;
}
void ASimulationManager::SetAlerted()
{
	Alerted = true;
}

bool ASimulationManager::GetAlerted()
{
	return Alerted;
}



