// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"





void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);
		

		
		GetBlackboardComponent()->SetValueAsVector(TEXT("SelfPawnStartLocation"), GetPawn()->GetActorLocation());

	}
	
	
	

}



void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;


}