// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"


class AGunActor;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintPure)
	bool IsDead()const;



	UFUNCTION(BlueprintPure)
	float GetHealthPercent()const;

	UFUNCTION(BlueprintPure)
	AGunActor* GetTheGun() const;

	void Shoot();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Gamepad Sensitivity
	UPROPERTY(EditDefaultsOnly, Category = "Gamepad Sensitivity", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", UIMin = "1.0", UIMax = "100.0"
		, ClampMin = "1.0", ClampMax = "100.0"))
		float RotationRateGamepad = 50.f;

	//Mouse Sensitivity
	UPROPERTY(EditDefaultsOnly, Category = "MouseSensitivity", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", UIMin = "1.0", UIMax = "100.0"
		, ClampMin = "1.0", ClampMax = "100.0"))
		float RotationRateMouse = 10.f;
	


private:
	
	static const int32 AssaultRifleIndex = 0;

	static const int32 LauncherIndex = 1;

	

	void ShiftShoulders();


	
	
	void AddHealthFromOf(AActor* OtherActor);

	void AddAmmoToAholdGunOf(AActor* OtherActor);
	

	static const int32 GunsNum = 2;
	
	AGunActor* Guns[GunsNum];
	

	int32 EquippedGunIndex = 0;



	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRateGamepad(float AxisValue);
	void LookUpRateMouse(float AxisValue);
	void LookRightRateGamepad(float AxisValue);
	void LookRightRateMouse(float AxisValue);
	void SwitchToRifle();
	void SwitchToLauncher();


	
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunActor> AssaultRifleClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunActor> LauncherClass;

	
	

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<AController*> AllControllers;



};
