// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAdditionActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"



// Sets default values
AHealthAdditionActor::AHealthAdditionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void AHealthAdditionActor::BeginPlay()
{
	Super::BeginPlay();

	ZAxisInitialPosition = GetActorLocation().Z;
	bLevitationDirection = 0;

	CurrentPosition = GetActorLocation();

	ZAxisLevitationTarget = CurrentPosition.Z + ZAxisLevitationAdditionFactor;



}

// Called every frame
void AHealthAdditionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LevitateEffect();
}

void AHealthAdditionActor::LevitateEffect()
{

	if (!bLevitationDirection)
	{
		CurrentPosition.Z = FMath::FInterpTo(CurrentPosition.Z, ZAxisLevitationTarget, UGameplayStatics::GetWorldDeltaSeconds(this), ActorLevitaionSpeed);
		SetActorLocation(CurrentPosition);
		if (CurrentPosition.Z >= ZAxisLevitationTarget - 10.f && CurrentPosition.Z <= ZAxisLevitationTarget + 10.f)
		{
			bLevitationDirection = 1;
		}
	}

	else
	{

		CurrentPosition.Z = FMath::FInterpTo(CurrentPosition.Z, ZAxisInitialPosition, UGameplayStatics::GetWorldDeltaSeconds(this), ActorLevitaionSpeed);
		SetActorLocation(CurrentPosition);

		if (CurrentPosition.Z >= ZAxisInitialPosition - 10.f && CurrentPosition.Z <= ZAxisInitialPosition + 10.f)
		{
			bLevitationDirection = 0;
		}

	}


}