// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BirdSpawner.h"
#include "GameFramework/GameModeBase.h"
#include "HunterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHunterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    // Constructor
    AHunterGameModeBase();

    UFUNCTION(BlueprintCallable, Category = "Score")
    void ResetScore();

    //we call it from blueprint code
    UFUNCTION(BlueprintCallable)
    int GetScore();

    UFUNCTION()
    static void AddScore(int ScoreToAdd);

    //using it to chose the levle
    UPROPERTY(BlueprintReadOnly, Category = "Progress")
    int KillBirdsCount = 0;
    //using it to chose the level
    UPROPERTY(BlueprintReadOnly, Category = "Progress")
    int EscapeBirdCount = 0;

    //function for pass to next level
    void IncrementKillBirdsCount();
    void KilledBirdsCount();
    void IncrementEscapedBirdsCount();
    void StoreScore();

protected:
    virtual void BeginPlay() override;
    
    // make an even that it is implemented from blueprints
    UFUNCTION(BlueprintImplementableEvent)
    void StartGame();

private:
    // Variable to store the score
    inline static int PlayerScore;

    // a delay of 4 sec for starting the game
    float StartDelay = 4.0f;
      
    //function for starting the timer
    void HandleGameStart();

    //fuction for enable the player inputs
    UFUNCTION()
    void EnablePlayerInput();

    // set the timer hsandle
    FTimerHandle NothingToDo;

    ABirdSpawner* BirdSpawnerInstance;


};

