// Fill out your copyright notice in the Description page of Project Settings.


#include "Justin/NPCPawn.h"

// Sets default values
ANPCPawn::ANPCPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANPCPawn::StartStop()
{
	bStop = true;
}

