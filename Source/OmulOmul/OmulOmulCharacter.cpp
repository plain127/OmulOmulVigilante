// Copyright Epic Games, Inc. All Rights Reserved.

#include "OmulOmulCharacter.h"
#include "OmulOmulProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Justin/NPCPawn.h"
#include "Kismet/GameplayStatics.h"
#include "SimulationManager.h"
#include "Blueprint/UserWidget.h"
#include "Justin/PhoneWidget.h"
#include "Justin/PlayerWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "OmulOmulPlayerController.h"
#include "HttpActor.h"
#include "Components/AudioComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AOmulOmulCharacter

AOmulOmulCharacter::AOmulOmulCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	AlertRadius = 100.f;
	PlayTime = 10.0f;

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
}

void AOmulOmulCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	auto PlayerUI = Cast<UPlayerWidget>(CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass));
	if (PlayerUI)
	{
		PlayerWidget = PlayerUI;
		PlayerWidget->AddToViewport();
	}

	PC = GetController<AOmulOmulPlayerController>();

	httpActor = Cast<AHttpActor>(UGameplayStatics::GetActorOfClass(GetWorld(), httpActorFactory));	

	auto Phone = Cast<UPhoneWidget>(CreateWidget<UPhoneWidget>(GetWorld(), PhoneWidgetClass));
	if (Phone)
	{
		PhoneWidget = Phone;

		PhoneWidget->Init(AudioCapture, this);
		PhoneWidget->AddToViewport(5);
		PhoneWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AOmulOmulCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayTime -= DeltaTime;
	
	if (nullptr != httpActor && httpActor->bSuccessLogin) {

		if (AudioComp && !AudioComp->IsPlaying())
		{
			AudioComp->SetSound(Sound_BGM);
			AudioComp->Play();
			AudioComp->FadeIn(1.5f);
			PlayerWidget->SetVisi();
		}

		if (PlayerWidget)
		{
			if (PlayTime < 0.f) {
				PlayTime = 0.f;
				if (!bOnce) {
					AudioComp->FadeOut(1.5f, 0.f);
					httpActor->SendGradingDataToServer();
					bOnce = true;
					LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetFactory);
					if (LoadingWidget) {
						LoadingWidget->AddToViewport();
					}
				}
			}
			if (bOnce) {
				ReqTime -= DeltaTime;
				UE_LOG(LogTemp, Warning, TEXT("%lf"), ReqTime);
				if (ReqTime < 0.0f) {
					ReqTime = 5.0f;
					httpActor->ReqGradingResult();
				}
			}
			PlayerWidget->DisplayTime(PlayTime);
		}
	}
	if (bIsCalling)
	{
		CallTime += DeltaTime;
		PhoneWidget->UpdateCallTimeText(CallTime);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AOmulOmulCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOmulOmulCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOmulOmulCharacter::Look);

		//Alerting
		EnhancedInputComponent->BindAction(AlertAction, ETriggerEvent::Completed, this, &AOmulOmulCharacter::Alert);

		EnhancedInputComponent->BindAction(TogglePhoneAction, ETriggerEvent::Completed, this, &AOmulOmulCharacter::TogglePhone);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AOmulOmulCharacter::StartCall()
{
	bIsCalling = true;
	CallTime = 0.f;
}

void AOmulOmulCharacter::StopCall()
{
	bIsCalling = false;
	CallTime = 0.f;
}

void AOmulOmulCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AOmulOmulCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AOmulOmulCharacter::Alert()
{
	FHitResult Hit;

	FVector Start = GetActorLocation();

	FCollisionShape Shape;
	Shape.SetSphere(AlertRadius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	DrawDebugSphere(GetWorld(), Start, AlertRadius, 23, FColor::Blue, false, 5.f);

	if (GetWorld()->SweepSingleByObjectType(Hit, Start, Start, FQuat::Identity, ECollisionChannel::ECC_Pawn, Shape, QueryParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning"));

		auto Pawn = Cast<ANPCPawn>(Hit.GetActor());
		auto Manager = Cast<ASimulationManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASimulationManager::StaticClass()));
		if (Pawn && Manager)
		{
			Pawn->StartStop();
			Manager->SetAlerted();
		}
	}
}

void AOmulOmulCharacter::TogglePhone()
{
	if (PhoneWidget && !PhoneWidget->IsVisible())
	{
		PhoneWidget->SetVisibility(ESlateVisibility::Visible);
		PhoneWidget->PulloutPhone();

		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetController<APlayerController>(), PhoneWidget);
		if (PC)
		{
			PC->SetShowMouseCursor(true);
			PC->ToPhoneInput();
		}
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetController<APlayerController>());
		PhoneWidget->RetrievePhone();

		if (PC)
		{
			PC->SetShowMouseCursor(false);
			PC->ToMovementInput();
		}
	}
}
