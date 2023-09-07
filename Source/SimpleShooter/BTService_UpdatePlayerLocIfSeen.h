// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlayerLocIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_UpdatePlayerLocIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
		UBTService_UpdatePlayerLocIfSeen();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
