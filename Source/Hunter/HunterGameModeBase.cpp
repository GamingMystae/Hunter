// Copyright Epic Games, Inc. All Rights Reserved.


#include "HunterGameModeBase.h"
#include "Bird.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "PlayerGun.h"
#include "BirdSpawner.h"


AHunterGameModeBase::AHunterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerScore = 0;
}

void AHunterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
			
	// bird instance
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABirdSpawner::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		BirdSpawnerInstance = Cast<ABirdSpawner>(FoundActors[0]);
	}
	
	HandleGameStart();
	StartGame();
	
}

int AHunterGameModeBase::GetScore()
{

	return PlayerScore;
}
void AHunterGameModeBase::AddScore(int ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
}
void AHunterGameModeBase::ResetScore()
{
	PlayerScore = 0;
}

void AHunterGameModeBase::StoreScore()
{
	
}
void AHunterGameModeBase::HandleGameStart()
{
	//disable the  player controller for 4 sec
	 // Get reference to the player
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		APlayerGun* PlayerGun = Cast<APlayerGun>(PlayerController->GetPawn());
		if (PlayerGun)
		{
			// Disable input for 4 seconds
			PlayerController->DisableInput(PlayerController);
			GetWorld()->GetTimerManager().SetTimer(NothingToDo, this, &AHunterGameModeBase::EnablePlayerInput, 4.0f, false);

		}
		
	}
	
}

void AHunterGameModeBase::EnablePlayerInput()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->EnableInput(PlayerController);
		APlayerGun* PlayerGun = Cast<APlayerGun>(PlayerController->GetPawn());
		if (PlayerGun)
		{
			PlayerGun->bIsInputEnabled = true;
			
		}
		// Enable spawning on BirdSpawner after the delay
		if (BirdSpawnerInstance)
		{
			BirdSpawnerInstance->bIsSpawnEnabled = true;
		}
		
	}
	
}

void AHunterGameModeBase::IncrementKillBirdsCount()
{
	KillBirdsCount++;
	

	KilledBirdsCount();
}

void AHunterGameModeBase::KilledBirdsCount()
{
	
	TArray<AActor*> BirdActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABird::StaticClass(), BirdActors);

	if (KillBirdsCount > 35 && BirdSpawnerInstance && BirdSpawnerInstance->BirdMaxSpawns == 0 && BirdActors.Num() == 0)
	{
		UGameplayStatics::OpenLevel(this, FName("L_Continue"));
	}
	else if (BirdSpawnerInstance && BirdSpawnerInstance->BirdMaxSpawns == 0 && BirdActors.Num() == 0)
	{
		UGameplayStatics::OpenLevel(this, FName("L_GameOver"));
	}
}

void AHunterGameModeBase::IncrementEscapedBirdsCount()
{	
	EscapeBirdCount++;
	KilledBirdsCount();
	
}
