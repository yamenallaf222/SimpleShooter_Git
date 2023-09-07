// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifleAmmoIncrement.h"
#include "Components/CapsuleComponent.h"
#include "ShooterCharacter.h"
#include "GunActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

// Sets default values
AAssaultRifleAmmoIncrement::AAssaultRifleAmmoIncrement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(Root);


	
}

// Called when the game starts or when spawned
void AAssaultRifleAmmoIncrement::BeginPlay()
{
	Super::BeginPlay();
	ZAxisInitialPosition = GetActorLocation().Z;
	bLevitationDirection = 0;

	CurrentPosition = GetActorLocation();

	ZAxisLevitationTarget = CurrentPosition.Z + ZAxisLevitationAdditionFactor;
	

}

// Called every frame
void AAssaultRifleAmmoIncrement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LevitateEffect();

	
		

	
	
}








void AAssaultRifleAmmoIncrement::LevitateEffect()
{
	
		if (!bLevitationDirection)
		{
			CurrentPosition.Z = FMath::FInterpTo(CurrentPosition.Z, ZAxisLevitationTarget, UGameplayStatics::GetWorldDeltaSeconds(this), GunLevitaionSpeed);
			SetActorLocation(CurrentPosition);
			if (CurrentPosition.Z >= ZAxisLevitationTarget - 10.f && CurrentPosition.Z <= ZAxisLevitationTarget + 10.f)
			{
				bLevitationDirection = 1;
			}
		}

		else
		{

			CurrentPosition.Z = FMath::FInterpTo(CurrentPosition.Z, ZAxisInitialPosition, UGameplayStatics::GetWorldDeltaSeconds(this), GunLevitaionSpeed);
			SetActorLocation(CurrentPosition);

			if (CurrentPosition.Z >= ZAxisInitialPosition - 10.f && CurrentPosition.Z <= ZAxisInitialPosition + 10.f)
			{
				bLevitationDirection = 0;
			}

		}


}




void AAssaultRifleAmmoIncrement::GetVisibleLoop()
{
	GetWorldTimerManager().SetTimer(GetVisibleTimer, this, &AAssaultRifleAmmoIncrement::GetVisible, 10.f);
}


void AAssaultRifleAmmoIncrement::GetVisible()
{
	
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	

}