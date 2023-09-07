// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GunActor.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "AssaultRifleAmmoIncrement.h"
#include "HealthAdditionActor.h"
#include "EngineUtils.h"
#include "GameFramework/SpringArmComponent.h"

#define DefaultAmmoChosen 30
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RotationRateGamepad = 50.f;

	RotationRateGamepad = 10.f;


}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	Health = MaxHealth;
	
	//filling AllControllers Array 
	for (AController* SController : TActorRange<AController>(GetWorld()))
	{
		AllControllers.Add(SController);
	}


	//initializing guns inventory
	Guns[AssaultRifleIndex] = GetWorld()->SpawnActor<AGunActor>(AssaultRifleClass);
	Guns[LauncherIndex] = GetWorld()->SpawnActor<AGunActor>(LauncherClass);

	//Setting The Equipped of available guns
	EquippedGunIndex = AssaultRifleIndex;

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Guns[EquippedGunIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Guns[EquippedGunIndex]->SetOwner(this);


	Guns[LauncherIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Guns[LauncherIndex]->SetOwner(this);
	Guns[LauncherIndex]->SetActorHiddenInGame(true);


	


	UCapsuleComponent* CharacterCollision = GetCapsuleComponent();

	if(CharacterCollision)
		CharacterCollision->OnComponentBeginOverlap.AddDynamic(this, &AShooterCharacter::OnBeginOverlap);




}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{


	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRateMouse"), this, &AShooterCharacter::LookUpRateMouse);
	PlayerInputComponent->BindAxis(TEXT("LookRightRateMouse"), this, &AShooterCharacter::LookRightRateMouse);
	PlayerInputComponent->BindAxis(TEXT("LookUpRateGamepad"), this, &AShooterCharacter::LookUpRateGamepad);
	PlayerInputComponent->BindAxis(TEXT("LookRightRateGamepad"), this, &AShooterCharacter::LookRightRateGamepad);
	PlayerInputComponent->BindAction(TEXT("Jump") , EInputEvent::IE_Pressed , this , &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("LauncherToggle"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SwitchToLauncher);
	PlayerInputComponent->BindAction(TEXT("RifleToggle"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SwitchToRifle);
	PlayerInputComponent->BindAction(TEXT("ShiftShoulders"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ShiftShoulders);

	



}
	

void AShooterCharacter::MoveForward(float AxisValue)
{

	AddMovementInput(GetActorForwardVector() * AxisValue);
	
}

void AShooterCharacter::MoveRight(float AxisValue)
{

	AddMovementInput(GetActorRightVector() * AxisValue);

}

void AShooterCharacter::LookUpRateGamepad(float AxisValue)
{

	AddControllerPitchInput(AxisValue * RotationRateGamepad * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::LookUpRateMouse(float AxisValue)
{

	AddControllerPitchInput(AxisValue * RotationRateMouse * GetWorld()->GetDeltaSeconds());

}



void AShooterCharacter::LookRightRateGamepad(float AxisValue)
{

	AddControllerYawInput(AxisValue * RotationRateGamepad * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::LookRightRateMouse(float AxisValue)
{

	AddControllerYawInput(AxisValue * RotationRateMouse * GetWorld()->GetDeltaSeconds());

}
	

void AShooterCharacter::Shoot()
{
	Guns[EquippedGunIndex]->PullTrigger();
}


float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	DamageToApply = FMath::Min(Health, DamageToApply);

	Health -= DamageToApply;

	if (IsDead())
	{
		
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fuck you UNREAL v SC"));
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	}
	

	

	

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
	
}


float AShooterCharacter::GetHealthPercent() const
{


	return Health / MaxHealth;
}


AGunActor* AShooterCharacter::GetTheGun() const
{
	return Guns[EquippedGunIndex];
}


void AShooterCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//All Checking is Done within the funciton
	AddHealthFromOf(OtherActor);

	//All Checking is Done within the funciton
	AddAmmoToAholdGunOf(OtherActor);


}

//Other Actor is the actor that has the ammo 
void AShooterCharacter::AddAmmoToAholdGunOf(AActor* OtherActor)
{
	AAssaultRifleAmmoIncrement* ActorHasAmmoToAdd = Cast<AAssaultRifleAmmoIncrement>(OtherActor);
	if (ActorHasAmmoToAdd && EquippedGunIndex == AssaultRifleIndex)
	{
		if (Guns[EquippedGunIndex])
		{

			if (Guns[EquippedGunIndex]->CurrentAmmo != Guns[EquippedGunIndex]->MaxAmmo)
			{
				//checking if incrementing ammo get outta mag bounds
				Guns[EquippedGunIndex]->CurrentAmmo = Guns[EquippedGunIndex]->CurrentAmmo + ActorHasAmmoToAdd->AmmoIncrement > Guns[EquippedGunIndex]->MaxAmmo ? Guns[EquippedGunIndex]->MaxAmmo : Guns[EquippedGunIndex]->CurrentAmmo + ActorHasAmmoToAdd->AmmoIncrement;


				//Disbale Adding Ammo functionality and visibilty of it is actor
				ActorHasAmmoToAdd->SetActorHiddenInGame(true);
				ActorHasAmmoToAdd->SetActorEnableCollision(false);
				ActorHasAmmoToAdd->GetVisibleLoop();

			}

		}
	}

}

void AShooterCharacter::AddHealthFromOf(AActor* OtherActor)
{
	AHealthAdditionActor* HealthAdditionActor = Cast<AHealthAdditionActor>(OtherActor);
	if (HealthAdditionActor)
	{
		float IntendedHealthToBeSetTo = Health + MaxHealth * HealthAdditionActor->HealthAdditionPercentage;
		if (Health < MaxHealth)
		{
			Health = IntendedHealthToBeSetTo > MaxHealth ?  MaxHealth : IntendedHealthToBeSetTo ;

			HealthAdditionActor->SetActorHiddenInGame(true);
			HealthAdditionActor->SetActorEnableCollision(false);
		}
	}

}

void AShooterCharacter::SwitchToRifle()
{

	if (EquippedGunIndex == AssaultRifleIndex)
	{
		return;
	}


	Guns[EquippedGunIndex]->SetActorHiddenInGame(true);

	EquippedGunIndex = AssaultRifleIndex;

	Guns[EquippedGunIndex]->SetActorHiddenInGame(false);



}


void AShooterCharacter::SwitchToLauncher()
{
	if (EquippedGunIndex == LauncherIndex)
	{
		return;
	}

	Guns[EquippedGunIndex]->SetActorHiddenInGame(true);

	EquippedGunIndex = LauncherIndex;

	Guns[EquippedGunIndex]->SetActorHiddenInGame(false);
	
}

void AShooterCharacter::ShiftShoulders()
{
	 USpringArmComponent* CameraArm = FindComponentByClass<USpringArmComponent>();

	 if (!ensure(CameraArm != nullptr)) return;

	 if (CameraArm->SocketOffset.Y == 60)
		 CameraArm->SocketOffset.Y = -120;
	 else
		 CameraArm->SocketOffset.Y = 60;

}






