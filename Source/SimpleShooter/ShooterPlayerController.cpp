// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus , bool bIsWinner )
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UGameplayStatics::GetPlayerPawn(this , 0)->DisableInput(this);
	
	
	HUD->RemoveFromViewport();

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{

			WinScreen->AddToViewport();

		}

	}
	else
	{ 
		UUserWidget* LoseScreen = CreateWidget(this , LoseScreenClass);
		if (LoseScreen)
		{
			
			
			LoseScreen->AddToViewport();
	
		}

	}
	


	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

	UE_LOG(LogTemp, Warning, TEXT("I ll fucking restart"));
}





void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();


	HUD = CreateWidget(this, HUDClass);
	
	if (HUD)
	{
		HUD->AddToViewport();
		
	}

	
	
	
}