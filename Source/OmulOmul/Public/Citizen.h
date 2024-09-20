// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "Citizen.generated.h"

UCLASS()
class OMULOMUL_API ACitizen : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACitizen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* IMC_Citizen;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Move;

	void OnMyActionMove(const FInputActionValue& Value);

	FVector Direction;



};
