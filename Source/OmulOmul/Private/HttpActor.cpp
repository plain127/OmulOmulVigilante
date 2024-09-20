// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpActor.h"
#include "HttpModule.h"
#include "JsonParseLib.h"
#include "StartUI.h"
#include "SimulationManager.h"
#include "Kismet/GameplayStatics.h"
#include "../OmulOmulCharacter.h"
#include "EndingUI.h"
#include "Justin/PlayerWidget.h"

// Sets default values
AHttpActor::AHttpActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHttpActor::BeginPlay()
{
	Super::BeginPlay();


	if (InputUIFactory) {
		UE_LOG(LogTemp, Warning, TEXT("InputUIFactory"));
		InputUI = CreateWidget<UStartUI>(GetWorld(), InputUIFactory);
		if (InputUI) {
			UE_LOG(LogTemp, Warning, TEXT("InputUI"));
			InputUI->AddToViewport();
			auto* pc = GetWorld()->GetFirstPlayerController();
			if (pc) {
				UE_LOG(LogTemp, Warning, TEXT("PC"));
				pc->bShowMouseCursor = true;

				FInputModeUIOnly InputMode;
				pc->SetInputMode(InputMode);
			}
		}

	}

}

// Called every frame
void AHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHttpActor::AddToMap(FString Key, FString Value)
{
	GradingData.Add(Key, Value);
}

void AHttpActor::LoginRequest(FString id, FString pwd)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *serverURL);

	CurrentID = id;

	req->SetURL(serverURL);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("content-type"), TEXT("application/json"));
	req->SetContentAsString(UJsonParseLib::MakeLoginInfoJson(id, pwd));

	FString info = FString::Printf(TEXT("info/"));
	sendResultURL = FString::Printf(TEXT("%s%s"), *baseURL, *id);
	sendResultURL_1 = FString::Printf(TEXT("%s%s%s"), *baseURL, *info, *id);
	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &AHttpActor::ResLoginRequest);

	// 서버에 요청
	req->ProcessRequest();
}

void AHttpActor::ResLoginRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		UE_LOG(LogTemp, Warning, TEXT("Successed"));
		token = UJsonParseLib::TokenJsonParse(Response->GetContentAsString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *token);
		InputUI->RemoveFromParent();
		bSuccessLogin = true;

		auto* pc = GetWorld()->GetFirstPlayerController();
		if (pc) {
			pc->bShowMouseCursor = false;

			FInputModeGameOnly InputMode;
			pc->SetInputMode(InputMode);
		}

		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	else {
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("OnResPostTest Failed..."));
	}
}

void AHttpActor::SendGradingDataToServer()
{
	UE_LOG(LogTemp, Warning, TEXT("SendGradingDataToServer"));
	TArray<uint8> FileData;
	FString FilePath = FPaths::ProjectContentDir() + TEXT("/Sound/Report.wav");

	if (FFileHelper::LoadFileToArray(FileData, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("File loaded successfully: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
		return;
	}
	FString En_SoundFile = FBase64::Encode(FileData);

	AddToMap("EncodingSoundFile", En_SoundFile);

	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	auto what = UGameplayStatics::GetActorOfClass(GetWorld(), smFactory);
	if (what)
	{
		sm = Cast<ASimulationManager>(what);

		if (sm) {
			UE_LOG(LogTemp, Warning, TEXT("sm"));
			AddToMap("AverDistance", FString::SanitizeFloat(sm->GetTotal() / sm->GetRecordCount()));
			AddToMap("Alerted", sm->GetAlerted() == true ? "true" : "false");
		}
	}


	req->SetURL(sendResultURL);
	req->SetVerb("POST");
	req->SetHeader(TEXT("User-Agent"), "UnrealEngine/5.0");
	req->SetHeader(TEXT("token"), FString::Printf(TEXT("%s"), *token));
	req->SetHeader(TEXT("content-type"), TEXT("application/json"));
	req->SetContentAsString(UJsonParseLib::MakeJson(GradingData, CurrentID));

	req->OnProcessRequestComplete().BindUObject(this, &AHttpActor::SendGradingDataFromServer);

	req->ProcessRequest();
}

void AHttpActor::SendGradingDataFromServer(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully) {
		UE_LOG(LogTemp, Warning, TEXT("Successed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}

void AHttpActor::ReqGradingResult()
{
	UE_LOG(LogTemp, Warning, TEXT("ReqGradingResult"));
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// 요청할 정보를 설정

	UE_LOG(LogTemp, Warning, TEXT("%s"), *sendResultURL_1);
	req->SetURL(sendResultURL_1);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("token"), FString::Printf(TEXT("%s"), *token));
	req->SetHeader(TEXT("content-type"), TEXT("application/json"));
	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &AHttpActor::ResGradingResult);
	// 서버에 요청
	req->ProcessRequest();
}

void AHttpActor::ResGradingResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully) {
		UE_LOG(LogTemp, Warning, TEXT("ResGradingResult: Successed"));
		Result = UJsonParseLib::ResultJsonParse(Response->GetContentAsString());
		UGameplayStatics::SetGamePaused(GetWorld(),true);
		auto* Player = Cast<AOmulOmulCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (Player) {	
			if(Player->LoadingWidget)
				Player->LoadingWidget->RemoveFromParent();
				Player->PlayerWidget->RemoveFromParent();
			EndingWidget = CreateWidget<UEndingUI>(GetWorld(),EndingWidgetFactory);
			if (EndingWidget) {
				EndingWidget->AddToViewport();
				EndingWidget->SetText(Result);
			}
		}	
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}
