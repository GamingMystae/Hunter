// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Bird.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponet = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponet);

	BulletSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Bullet Sprite"));
	BulletSprite->SetupAttachment(SphereComponet);

	//set default movement direction
	MovementDirection = FVector2D(1.0f, 1.0f);
	

}


// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponet->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OverlapBegin);
	
}


// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//moving the bullet
	FVector2D MoveDistance = MovementDirection * MovementSpeed * DeltaTime;
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + FVector(MoveDistance.X, 0.0f, MoveDistance.Y);
	SetActorLocation(NewLocation);

	DestroyBullet(false);
	

}

void ABullet::Launch(FVector2D Direction, float Speed)
{
	UGameplayStatics::PlaySoundAtLocation(this, GunSound, GetActorLocation());
	MovementDirection = Direction;
	MovementSpeed = Speed;
}

void ABullet::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABird* Bird = Cast<ABird>(OtherActor);
	if (Bird)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		DestroyBullet(true);
	}
	
}

void ABullet::DestroyBullet(bool bOncollision)
{
	// Destroy immediately if it's a collision
	if (bOncollision)
	{
		Destroy();
		return;
	}
	// Get the current position of the bullet
	FVector BulletPosition = GetActorLocation();

	// Check if the bullet has exceeded the boundaries or hit a bird
	if (BulletPosition.Z > 590 || BulletPosition.X > 1020 || BulletPosition.X < -1020)
	{
		// Destroy the bullet actor
		Destroy();
	}
}

