// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"


UCLASS()
class SIMPLESHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo;

	void MultiplyDamageBy(int32 Factor);



private:

	
	


	
	
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root; 

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	
	





	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* GunShotImpactSound;

	UPROPERTY(EditAnywhere)
	USoundBase* GunEmptySound;


	

	


	
	
	bool GunTrace(FHitResult& BulletHitResult, FVector& ShotDirection);

	


	AController* GetOwnerController() const;


};
