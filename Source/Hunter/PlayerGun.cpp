// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGun.h"
#include "PaperSpriteComponent.h"
#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"


// Sets default values
APlayerGun::APlayerGun()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponent);

    GunParent = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Parent"));
    GunParent->SetupAttachment(SphereComponent);

	GunSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GunSprite"));
	GunSprite->SetupAttachment(GunParent);
    
    SpawnPotition = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Location"));
    SpawnPotition->SetupAttachment(GunSprite);

}

// Called when the game starts or when spawned
void APlayerGun::BeginPlay()
{
	Super::BeginPlay();

    // Get the player controller with casting
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController)
    {
        // Set the mouse cursor to be always visible
        PlayerController->bShowMouseCursor = true;
    }
	
}



void APlayerGun::Fire()
{
    //check the bool value
    if (!bIsInputEnabled)
    {
        return;
    }
    //spawn the bullet
    ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBPClass, SpawnPotition->GetComponentLocation(), FRotator(0.0f, 0.0f, 0.0f));

    // Get the player controller with casting
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController)
    {
        //getting the mouse position
        FVector MouseWorldLocation, MouseWordDirection;
        PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWordDirection);

        //bullet direction
        FVector CurrentLocation = GetActorLocation();
        FVector2D BulletDirection = FVector2D(MouseWorldLocation.X - CurrentLocation.X, MouseWorldLocation.Z - CurrentLocation.Z);
        BulletDirection.Normalize();

        //calling the launch function
        float BulletSpeed = 1000.0f;
        
        if (bCanSpawn)
        {
            Bullet->Launch(BulletDirection, BulletSpeed);
            MaxSpawns--;
                if (MaxSpawns == 0)
                {
                    bCanSpawn = false;
                }
        }
        
    
    }
}



// Called every frame
void APlayerGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bIsInputEnabled)
    {
        return;
    }
    //roate the gun and following the cursor
    // Get the player controller with casting
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController)
    {
          //getting the mouse position
        FVector MouseWorldLocation, MouseWordDirection;
        PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWordDirection);
       
        FVector CurrentLocation = GetActorLocation();
        FVector Start = FVector(CurrentLocation.X, 0.0f, CurrentLocation.Z);
        FVector Target = FVector(MouseWorldLocation.X, 0.0f, MouseWorldLocation.Z);
        FRotator GunRotator = UKismetMathLibrary::FindLookAtRotation(Start, Target);
        
        GunParent->SetRelativeRotation(GunRotator);


    }

}

// Called to bind functionality to input
void APlayerGun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    	
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerGun::Fire);
}

