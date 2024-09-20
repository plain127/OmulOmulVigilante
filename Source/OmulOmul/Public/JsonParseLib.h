// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonParseLib.generated.h"


/**
 *
 */
UCLASS()
class OMULOMUL_API UJsonParseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FString MakeJson(const TMap<FString, FString> source,FString id);

	static FString MakeLoginInfoJson(FString Id, FString Pwd);

	static FString TokenJsonParse(const FString& json);

	static FString ResultJsonParse(const FString& json);
};
