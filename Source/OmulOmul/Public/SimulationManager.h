// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulationManager.generated.h"

UCLASS()
class OMULOMUL_API ASimulationManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimulationManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	double GetTotal() const;

	int32 GetRecordCount() const;

	void SetAlerted();

	bool GetAlerted();

private:
	UPROPERTY(EditInstanceOnly, Category = "Settings")
	class AOmulOmulCharacter* Player;

	UPROPERTY(EditInstanceOnly, Category = "Settings")
	class ABallonActor* Target;


	float RecordingTime = 1.0f;
	
	float CurrentTime = 0.0f;

	int32 RecordCount = 0;
	
	FVector distance;

	double Total = 0;

	bool Alerted;

};
