// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthAdditionActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API AHealthAdditionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthAdditionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = " Addition Attributes" , meta = (ClampMin = "0.0" , ClampMax = "1.0" , UIMin = "0.0" , UIMax = "1.0"))
	float HealthAdditionPercentage;
	 
private:
	//levitating variables 
	FVector CurrentPosition;

	float ZAxisInitialPosition;

	UPROPERTY(EditAnywhere,   Category = "Levitation")
	float ZAxisLevitationAdditionFactor = 25.0f;

	float ZAxisLevitationTarget;

	float LevitationTargetMoment;


	UPROPERTY(EditAnywhere, Category = "Levitation")
	float ActorLevitaionSpeed = 1.0f;


	bool bLevitationDirection;

	void LevitateEffect();
	
	//Comps Varibles
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
	

	



};
