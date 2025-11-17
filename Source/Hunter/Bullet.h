// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class HUNTER_API ABullet : public AActor
{
	GENERATED_BODY()
	
	
public:
	ABullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	//launch function
	void Launch(FVector2D Direction, float Speed);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector2D MovementDirection;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 1000;

	UPROPERTY(EditAnywhere, Category = "Component")
	class USphereComponent* SphereComponet;

	UPROPERTY(EditAnywhere, Category = "Sprite Component")
	class UPaperSpriteComponent* BulletSprite;

	// for using the collision
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//destroy function bullet
	void DestroyBullet(bool bOncollision);

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* GunSound;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* DeathSound;
};

