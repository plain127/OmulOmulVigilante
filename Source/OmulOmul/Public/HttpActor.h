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

	// Ending ���� ������ ������ ���� ������ ���� Map 

	// �� ���ۿ� ���� �Լ��� ���� ���� HttpActor�� GradingData�� �߰��ϴ� �Լ�
	void AddToMap(FString Key, FString Value);

	// �α��� ��û�� ������ �Լ�
	void LoginRequest(FString id, FString pwd);

	// ������ ������ ���� �Լ�
	void ResLoginRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	// Ending ���� Ư�� Ʈ���ſ� ���ؼ� ������ GradingData�� Json ���� ���� �۽��ϴ� �Լ�
	void SendGradingDataToServer();

	// ������ ������ ���� �Լ�
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
