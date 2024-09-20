// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "OmulOmulCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UPhoneWidget;
class UPlayerWidget;
class AAudioCaptureActor;
class AOmulOmulPlayerController;
class UAudioComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class AOmulOmulCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AlertAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TogglePhoneAction;

public:
	AOmulOmulCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

public:
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float AlertRadius;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float PlayTime;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UPhoneWidget> PhoneWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY(EditInstanceOnly, Category = "Settings")
	TObjectPtr<AAudioCaptureActor> AudioCapture;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Alert();

	void TogglePhone();

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TObjectPtr<UAudioComponent> AudioComp;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TObjectPtr<USoundBase> Sound_BGM;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPhoneWidget> PhoneWidget;
	TObjectPtr<AOmulOmulPlayerController> PC;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY(BlueprintReadOnly)
	float CallTime;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCalling;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void StartCall();
	void StopCall();
public:
	UPROPERTY(EditDefaultsOnly)
	class AHttpActor* httpActor;



	TObjectPtr<UPlayerWidget> PlayerWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHttpActor> httpActorFactory;

	bool bOnce = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoadingWidgetFactory;
	
	class UUserWidget* LoadingWidget;


	float ReqTime = 5.0f;
};

