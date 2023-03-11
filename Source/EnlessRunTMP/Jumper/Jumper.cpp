// Fill out your copyright notice in the Description page of Project Settings.


#include "Jumper.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AJumper::AJumper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	CharacterMovement = GetCharacterMovement();
	CharacterMovement->BrakingDecelerationFalling = 1000;
	CharacterMovement->AirControl = 100;
	CharacterMovement->FallingLateralFriction = 1000;	
	CharacterMovement->JumpZVelocity=500;
    CharacterMovement->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	 Mesh = GetMesh();


	//-----------------------------------------------------
	JumpDistance = 200;
	MaxLane = 3;
	CountJumpInAir = 0;
	bIsDeath = false;
	Score = 0;

}

// Called when the game starts or when spawned
void AJumper::BeginPlay()
{
	Super::BeginPlay();
}

void AJumper::Death()
{
	bIsDeath = true;
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AJumper::DisableMovement, 0.35f, false);
	

}

void AJumper::DisableMovement()
{
	

	CharacterMovement->DisableMovement();
	Mesh->SetCollisionProfileName(FName("Ragdoll"),true);
	Mesh->SetSimulatePhysics(true);


}




void AJumper::JumpLeft()
{
	if (bIsDeath) return;
	if (!(CurentLane<MaxLane/2))return;
	if (!(CountJumpInAir < 2)) return;
	AddMovementInput(FVector(1, 1, 0), 1, false);
	Jump();
	CurentLane += 1;
	CountJumpInAir += 1;
}

void AJumper::JumpRight()
{
	if (bIsDeath) return;
	if (!(CurentLane > (MaxLane / 2)*-1))return;
	if (!(CountJumpInAir < 2)) return;
	AddMovementInput(FVector(1, -1, 0), 1, false);
	Jump();
	CurentLane -= 1;
	CountJumpInAir += 1;
}

void AJumper::DoubleJump()
{
	if (!(CountJumpInAir<2))return;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Bool: %s"), bIsInAir? TEXT("true") : TEXT("false")));

	if (bIsInAir)
	{
		CharacterMovement->Velocity = FVector(CharacterMovement->Velocity.X, CharacterMovement->Velocity.Y,400.f );
		CountJumpInAir += 1;
	}
	else 
	{
		Jump();
		CountJumpInAir += 1;
	}


	 
}

void AJumper::DeJump()
{
	if (!bIsInAir)return;
	CharacterMovement->AddForce(FVector(0.f,0.f,-6000000.f));

}

void AJumper::SetPlayerMoveDirection()
{

	if (CharacterMovement)
	{
		FVector MovementVelocity = CharacterMovement->Velocity;

		if (MovementVelocity.Y==0)
		{
			AddMovementInput(FVector(1,0,0),1,false);
			
		}
		else {
		
			if (MovementVelocity.Y > 0)
			{
				AddMovementInput(FVector(1, 1, 0), 1, false);
			}
			else
			{
				AddMovementInput(FVector(1, -1, 0), 1, false);
			}
		}
	}
}



// Called every frame
void AJumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bIsInAir = CharacterMovement->IsFalling();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Bool: %s"), bIsInAir? TEXT("true") : TEXT("false")));
	
	AddMovementInput(FVector(1, 0, 0), 1, false);

	if (bIsInAir)
	{
		SetPlayerMoveDirection();
	}
	else
	{
		CountJumpInAir = 0;
	}
}

// Called to bind functionality to input
void AJumper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("JumpLeft", IE_Pressed, this, &AJumper::JumpLeft);
	PlayerInputComponent->BindAction("JumpRight", IE_Pressed, this, &AJumper::JumpRight);
	PlayerInputComponent->BindAction("DoubleJump", IE_Pressed, this, &AJumper::DoubleJump);
	PlayerInputComponent->BindAction("DeJump", IE_Pressed, this, &AJumper::DeJump);


}

