// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameOptions.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USaveGameOptions : public USaveGame
{
	GENERATED_BODY()



public:
	float MouseSens;
	
};
