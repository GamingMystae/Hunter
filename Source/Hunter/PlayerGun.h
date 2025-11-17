// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "GameFramework/Pawn.h"
#include "PlayerGun.generated.h"

UCLASS()
class HUNTER_API APlayerGun : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	TSubclassOf<ABullet> BulletBPClass; /// calling the ammo for spawning

	//enable or disable input using that bool from the game mode
	bool bIsInputEnabled = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* SphereComponent;

	

	//void MovePlayer(float input);
	void  Fire();
	float ShotPower;

	//gun creation
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USceneComponent* GunParent;

	UPROPERTY(VisibleAnywhere, Category = "Sprite")
	class UPaperSpriteComponent* GunSprite;

	//getting the spawn position
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USceneComponent* SpawnPotition;

	bool bCanSpawn = true;
	int MaxSpawns = 40;

	

};
