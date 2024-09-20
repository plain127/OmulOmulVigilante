// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartUI.generated.h"

/**
 *
 */
UCLASS()
class OMULOMUL_API UStartUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* UserIdPrompt;
	
	UPROPERTY(meta = (BindWidget))
	class UEditableText* UserPwdPrompt;

	
	UPROPERTY(meta = (BindWidget))
	class UButton* LoginRequest;

	UPROPERTY(EditDefaultsOnly)
	class AHttpActor* HttpActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHttpActor> HttpActorFactory;

	UFUNCTION()
	void OnMyIDCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnMyPwdCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnMyLoginButtonClicked();
};
