// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera.generated.h"

UCLASS()
class ENLESSRUNTMP_API ACamera : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACamera();
	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;

private:	


	

};
