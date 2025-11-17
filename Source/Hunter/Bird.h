// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bird.generated.h"

UCLASS()
class HUNTER_API ABird : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABird();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "Component")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, Category = "PaperSprite ")
	class UPaperFlipbookComponent* BirdSprite;

	void DestroyBird();
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 800;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bNextLevel = false;
		
};
