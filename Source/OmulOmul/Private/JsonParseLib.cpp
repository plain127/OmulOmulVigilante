// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLib.h"
#include "HttpActor.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"

FString UJsonParseLib::MakeJson(const TMap<FString, FString> source,FString id)
{
	// source 를 JsonObject 형식으로 만든다.
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonObject> Temp = MakeShareable(new FJsonObject());

	for (TPair<FString, FString> pair : source)
	{
		Temp->SetStringField(pair.Key, pair.Value);
	}

	TArray<TSharedPtr<FJsonValue>> JsonArray;
	JsonArray.Add(MakeShareable(new FJsonValueObject(Temp)));
	jsonObject->SetArrayField(FString::Printf(TEXT("%s"), *id), JsonArray);

	// writer 를 만들고 JsonObject를 인코딩해서 반환한다.
	FString json;
	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);

	return json;
}

FString UJsonParseLib::MakeLoginInfoJson(FString Id, FString Pwd)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	jsonObject->SetStringField("username", *Id);
	jsonObject->SetStringField("password", *Pwd);

	FString json;
	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);

	return json;
}

FString UJsonParseLib::TokenJsonParse(const FString& json)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	// 파싱 결과를 담을 변수 선언
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// 해석을 한다.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader, result))
	{
		if (result->HasField("token")) {
			FString token = result->GetStringField("token");
			returnValue.Append(FString::Printf(TEXT("%s"), *token));
		}
	}
	// 반환한다.
	return returnValue;
}

FString UJsonParseLib::ResultJsonParse(const FString& json)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	// 파싱 결과를 담을 변수 선언
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// 해석을 한다.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader, result))
	{
		if (result->HasField("score") && result->HasField("CAUSE")) {
			int32 score = result->GetIntegerField("score");
			FString cause = result->GetStringField("CAUSE");
			returnValue.Append(FString::Printf(TEXT("Score : % d \n Cause : % s\n"), score, *cause));
		}
	}
	// 반환한다.
	return returnValue;
}



