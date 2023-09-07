// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssaultRifleAmmoIncrement.generated.h"

UCLASS()
class SIMPLESHOOTER_API AAssaultRifleAmmoIncrement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAssaultRifleAmmoIncrement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int32 AmmoIncrement = 10;
	void GetVisibleLoop();

private:

	void GetVisible();
	
	

	

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;



	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;



	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Mesh;


	


	//levitating variables 
	FVector CurrentPosition;

	float ZAxisInitialPosition;

	UPROPERTY(EditAnywhere , Category = "Levitation")
		float ZAxisLevitationAdditionFactor  ;

	float ZAxisLevitationTarget;

	float LevitationTargetMoment;


	UPROPERTY(EditAnywhere, Category = "Levitation")
		float GunLevitaionSpeed ;


	bool bLevitationDirection;

	FTimerHandle GetVisibleTimer;

	void AddAmmo(AActor* OtherActor);
	
	void LevitateEffect();
	
	
};
