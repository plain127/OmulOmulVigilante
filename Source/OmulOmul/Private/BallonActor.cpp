// Fill out your copyright notice in the Description page of Project Settings.


#include "BallonActor.h"

// Sets default values
ABallonActor::ABallonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

