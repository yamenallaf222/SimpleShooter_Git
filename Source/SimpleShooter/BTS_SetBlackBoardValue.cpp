// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SetBlackBoardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_SetBlackBoardValue::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!bHaveValueSet)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}



}


UBTS_SetBlackBoardValue::UBTS_SetBlackBoardValue()
{
	NodeName = " Set BlackBoard Bool Value True";
}