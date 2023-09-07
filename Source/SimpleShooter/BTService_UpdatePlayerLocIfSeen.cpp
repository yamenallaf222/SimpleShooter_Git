// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocIfSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"


UBTService_UpdatePlayerLocIfSeen::UBTService_UpdatePlayerLocIfSeen()
{
	NodeName = "Update Player Location If Seen";
}



void UBTService_UpdatePlayerLocIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIController* EnemeyAIController = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld() , 0);


	if (EnemeyAIController == nullptr || PlayerPawn == nullptr) return;
	
	if (EnemeyAIController->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}



}
