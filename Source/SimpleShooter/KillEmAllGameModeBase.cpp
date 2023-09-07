// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterCharacter.h"
#include "ShooterAIController.h"




void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	
	


	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
		
	
	if (PlayerController != nullptr)
	{

		
		
		EndGame(false);
		
	}

	else
	{
		
		for (AShooterAIController* ShooterAIController :  TActorRange<AShooterAIController>(GetWorld()))
		{
			if (ShooterAIController!= nullptr)
			{
	
				if (!ShooterAIController->IsDead())
				{
					return;
				}
			
			}
		}


		EndGame(true);

	}




	UE_LOG(LogTemp, Warning, TEXT("Pawn Has Killed"));

}


void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
			
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
		


		

	}


}