// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLib.h"
#include "HttpActor.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"

FString UJsonParseLib::MakeJson(const TMap<FString, FString> source,FString id)
{
	// source �� JsonObject �������� �����.
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonObject> Temp = MakeShareable(new FJsonObject());

	for (TPair<FString, FString> pair : source)
	{
		Temp->SetStringField(pair.Key, pair.Value);
	}

	TArray<TSharedPtr<FJsonValue>> JsonArray;
	JsonArray.Add(MakeShareable(new FJsonValueObject(Temp)));
	jsonObject->SetArrayField(FString::Printf(TEXT("%s"), *id), JsonArray);

	// writer �� ����� JsonObject�� ���ڵ��ؼ� ��ȯ�Ѵ�.
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
	// �����⸦ �����
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	// �Ľ� ����� ���� ���� ����
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// �ؼ��� �Ѵ�.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader, result))
	{
		if (result->HasField("token")) {
			FString token = result->GetStringField("token");
			returnValue.Append(FString::Printf(TEXT("%s"), *token));
		}
	}
	// ��ȯ�Ѵ�.
	return returnValue;
}

FString UJsonParseLib::ResultJsonParse(const FString& json)
{
	// �����⸦ �����
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);
	// �Ľ� ����� ���� ���� ����
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// �ؼ��� �Ѵ�.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader, result))
	{
		if (result->HasField("score") && result->HasField("CAUSE")) {
			int32 score = result->GetIntegerField("score");
			FString cause = result->GetStringField("CAUSE");
			returnValue.Append(FString::Printf(TEXT("Score : % d \n Cause : % s\n"), score, *cause));
		}
	}
	// ��ȯ�Ѵ�.
	return returnValue;
}



