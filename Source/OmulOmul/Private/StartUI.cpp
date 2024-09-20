// Fill out your copyright notice in the Description page of Project Settings.


#include "StartUI.h"
#include "Components/EditableText.h"
#include "JsonParseLib.h"
#include "Components/Button.h"
#include "HttpActor.h"
#include "Kismet/GameplayStatics.h"

void UStartUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	HttpActor = Cast<AHttpActor>(UGameplayStatics::GetActorOfClass(GetWorld(), HttpActorFactory));

	UserIdPrompt->OnTextCommitted.AddDynamic(this, &UStartUI::OnMyIDCommitted);

	UserPwdPrompt->OnTextCommitted.AddDynamic(this, &UStartUI::OnMyPwdCommitted);

	LoginRequest->OnClicked.AddDynamic(this, &UStartUI::OnMyLoginButtonClicked);
}

void UStartUI::OnMyIDCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus)
	{
		username = Text.ToString();
		UE_LOG(LogTemp, Log, TEXT("User ID: %s"), *username);
	}
}

void UStartUI::OnMyPwdCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter || CommitMethod == ETextCommit::OnUserMovedFocus)
	{
		userPWD = Text.ToString();
		UE_LOG(LogTemp, Log, TEXT("User Password: %s"), *userPWD);
	}
}

void UStartUI::OnMyLoginButtonClicked()
{	
	HttpActor->LoginRequest(username,userPWD);
}
