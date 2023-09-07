// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_ServiceUpdatePlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackBoardComponent.h"

UBT_ServiceUpdatePlayerLocation::UBT_ServiceUpdatePlayerLocation()
{

	NodeName = "Update Player Location";

}


void UBT_ServiceUpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn == nullptr) return;

	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());



}
