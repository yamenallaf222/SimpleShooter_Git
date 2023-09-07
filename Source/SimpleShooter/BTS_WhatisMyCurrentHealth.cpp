// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_WhatisMyCurrentHealth.h"
#include "AIController.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"

UBTS_WhatisMyCurrentHealth::UBTS_WhatisMyCurrentHealth()
{
	NodeName = "What is My Current Health Percentage";
}

void UBTS_WhatisMyCurrentHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode( OwnerComp,   NodeMemory,  DeltaSeconds);
	
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController)
	{
		AShooterCharacter* AICharacter = Cast<AShooterCharacter>( AIController->GetPawn());
		if (AICharacter)
		{

			
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), AICharacter->GetHealthPercent());
			

		}
	
	}


}