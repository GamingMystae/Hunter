// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TimerHandle.h"
#include "Bird.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BirdSpawner.generated.h"


UCLASS()
class HUNTER_API ABirdSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABirdSpawner();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "SpawnBird")
	TSubclassOf<ABird> BirdSpawner;

	//enable or disable Spawn using that bool from the game mode
	bool bIsSpawnEnabled = false;

	int BirdMaxSpawns = 40;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Time")
	float SpawnTime = 1.0f;
		
	void SpawnBird();

	FTimerHandle SpawnTimer;

	bool bBirdCanSpawn = true;
	

};
