// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "HunterGameModeBase.h"

// Sets default values
ABird::ABird()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComp);

	BirdSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Bird Flipbook"));
	BirdSprite->SetupAttachment(CapsuleComp);

}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABird::OverlapBegin);
	
}

void ABird::DestroyBird()
{
	FVector BirdPosition = GetActorLocation();

	// Check if the bird has moved past the X boundary
	// Adjust the x value for destroying the bird
	if (BirdPosition.X > 1320 || BirdPosition.X < -1320)
	{
		Destroy();
		AHunterGameModeBase* GameMode = Cast<AHunterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->IncrementEscapedBirdsCount();
		}
	}
	

}

void ABird::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
	// Example usage in another class
	AHunterGameModeBase* GameMode = Cast<AHunterGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->AddScore(10); // Add 10 points
		GameMode->IncrementKillBirdsCount(); // run the function for adding kills from the gamemode
	}
	
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Move the bird from -X to +X
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + FVector(MovementSpeed * DeltaTime, 0.0f, 0.0f);
	SetActorLocation(NewLocation);

	// Call the DestroyBird function to check if the bird should be destroyed
	DestroyBird();
}

