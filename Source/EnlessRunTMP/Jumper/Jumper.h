// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Jumper.generated.h"

UCLASS()
class ENLESSRUNTMP_API AJumper : public ACharacter
{
	GENERATED_BODY()

public:
	AJumper();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
//-------------------------------------------------------------------------------------------
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"));
	int CurentLane;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"));
	int MaxLane;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"));
	int CountJumpInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"));
	int Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"));
	bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"));
	bool bIsDeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"));
	float JumpDistance;


	UFUNCTION(BlueprintCallable, Category = "Player State")
	void Death();
	void DisableMovement();

protected:

	void JumpLeft();
	void JumpRight();
	void DoubleJump();
	void DeJump();


	void SetPlayerMoveDirection();


private:
	UCharacterMovementComponent* CharacterMovement;

	USkeletalMeshComponent* Mesh;


};
