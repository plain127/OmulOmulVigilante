// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpActor.generated.h"

static FString username;
static FString userPWD;

UCLASS()
class OMULOMUL_API AHttpActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Ending 이후 서버로 전송할 리턴 값들을 담은 Map 

	// 각 동작에 대한 함수의 리턴 값을 HttpActor의 GradingData에 추가하는 함수
	void AddToMap(FString Key, FString Value);

	// 로그인 요청을 보내는 함수
	void LoginRequest(FString id, FString pwd);

	// 서버의 응답을 받을 함수
	void ResLoginRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	// Ending 이후 특정 트리거에 의해서 서버에 GradingData를 Json 으로 만들어서 송신하는 함수
	void SendGradingDataToServer();

	// 서버의 응답을 받을 함수
	void SendGradingDataFromServer(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void ReqGradingResult();

	void ResGradingResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

private:
	TMap<FString, FString> GradingData;

	FString serverURL = "http://192.168.1.55:8080/user/login/token";
	FString baseURL = "http://192.168.1.55:8080/result/";
	FString sendResultURL;
	FString sendResultURL_1;
	FString token;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UStartUI> InputUIFactory;
	
	class UStartUI* InputUI;

	
public:
	bool bSuccessLogin = false;

	UPROPERTY(EditDefaultsOnly)
	class ASimulationManager* sm;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASimulationManager> smFactory;

	FString CurrentID;

	FString Result;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UEndingUI> EndingWidgetFactory;
	
	class UEndingUI* EndingWidget;
};
