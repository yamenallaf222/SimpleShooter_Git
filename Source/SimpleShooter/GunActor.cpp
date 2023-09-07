// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "ShooterCharacter.h"



#define OUT


// Sets default values
AGunActor::AGunActor()
{

	
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));

	Mesh->SetupAttachment(Root);

	

}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	


	CurrentAmmo = MaxAmmo;


	

	
}


void AGunActor::MultiplyDamageBy(int32 Factor)
{

	this->Damage *= Factor;

}


// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	


	
		
	
		
	
		

	
}


void AGunActor::PullTrigger()
{

	if (CurrentAmmo > 0)
	{

		CurrentAmmo--;

		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));



		FHitResult BulletHitResult;
		FVector ShotDirection;

		bool bSuccess = GunTrace(BulletHitResult, ShotDirection);



		if (bSuccess)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, BulletHitResult.Location, ShotDirection.Rotation());
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), GunShotImpactSound, BulletHitResult.Location, ShotDirection.Rotation());




			AActor* HitActor = BulletHitResult.GetActor();
			if (HitActor != nullptr)
			{
				FPointDamageEvent PointDamageEvent(Damage, BulletHitResult, ShotDirection, nullptr);
				AController* OwnerController = GetOwnerController();
				HitActor->TakeDamage(Damage, PointDamageEvent, OwnerController, this);
			}

		}



	}

	else
	{
		UGameplayStatics::SpawnSoundAttached(GunEmptySound, Mesh, TEXT("RifleMag"));

	}




}


bool AGunActor::GunTrace(FHitResult& BulletHitResult, FVector& ShotDirection)
{
	
		AController* OwnerController = GetOwnerController();

		if (OwnerController == nullptr)
		{
			return false;
		}

		FVector CameraLocation = FVector::ZeroVector;
		FRotator CameraRotation = FRotator::ZeroRotator;


		OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
		ShotDirection = -CameraRotation.Vector();
		FVector End = CameraLocation + CameraRotation.Vector() * MaxRange;



		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		Params.AddIgnoredActor(GetOwner());


		return GetWorld()->LineTraceSingleByChannel(BulletHitResult, CameraLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
	
}



AController* AGunActor::GetOwnerController() const
{
	
		APawn* OwnerPawn = Cast<APawn>(GetOwner());

		if (OwnerPawn == nullptr) return nullptr;

		AController* OwnerController = Cast<AController>(OwnerPawn->GetController());


		return OwnerController;
	

	
}


