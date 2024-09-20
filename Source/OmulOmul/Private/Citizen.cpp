// Fill out your copyright notice in the Description page of Project Settings.


#include "Citizen.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values
ACitizen::ACitizen()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACitizen::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACitizen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FTransform ttt = FTransform(GetControlRotation());
	Direction = ttt.TransformVector(Direction);
	Direction.Z = 0;
	Direction.Normalize();
	Direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void ACitizen::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
    if (input)
	{ 
	input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ACitizen::OnMyActionMove);
	}
}

void ACitizen::OnMyActionMove(const FInputActionValue& Value)
{
	
		FVector2D v = Value.Get<FVector2D>();
		Direction.X = v.X;
		Direction.Y = v.Y;
		Direction.Normalize();

}
// 
