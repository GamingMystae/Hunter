#include "BirdSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Bird.h"
#include "Engine/Engine.h"  // For GEngine

// Sets default values
ABirdSpawner::ABirdSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABirdSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Set up a timer to spawn a bird every `SpawnTime` seconds
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ABirdSpawner::SpawnBird, SpawnTime, true);
}

// Called every frame
void ABirdSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABirdSpawner::SpawnBird()
{
	if (!bIsSpawnEnabled)
	{
		return;
	}
	// Generate random coordinates for the bird spawn location
	float RandomX = FMath::FRandRange(-1230.0f, -1030.0f);
	float RandomZ = FMath::FRandRange(-240.0f, 500.0f);

	// Set the spawn location and rotation
	FVector SpawnLocation(RandomX, 0.0f, RandomZ);  // Assuming Y is 0 since you only mentioned X and Z
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// Check if BirdClass is valid before spawning
	if (BirdSpawner && BirdMaxSpawns > 0)
	{
		// Spawn the bird
		GetWorld()->SpawnActor<ABird>(BirdSpawner, SpawnLocation, SpawnRotation);
		BirdMaxSpawns--;	
		
	}
	else
	{
		bBirdCanSpawn = false;
	}

}


