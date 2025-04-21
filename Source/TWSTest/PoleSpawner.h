// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoleSpawner.generated.h"

class ATWSBasePole;
class ATWSCableActor;
class USplineComponent;

UCLASS()
class TWSTEST_API APoleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APoleSpawner();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	USplineComponent* Spline;

	// Клас стовпа
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<ATWSBasePole> PoleClass;

	// Клас кабеля
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<ATWSCableActor> CableClass;

	// Відстань між стовпами
	UPROPERTY(EditAnywhere, Category = "Setup")
	float DistanceBetweenPoles = 1000.f;

	UFUNCTION(CallInEditor, Category = "Helper Functions")
	void RebuildPolesAndLines();

	UFUNCTION(CallInEditor, Category = "Helper Functions")
	void ClearPolesAndLines();

private:
	void ClearExistingSetup();
	void SpawnPolesAndCables();

	void SpawnCables();
	void SpawnPoles();

	UPROPERTY(Transient)
	TArray<ATWSBasePole*> SpawnedPoles;

	UPROPERTY(Transient)
	TArray<ATWSCableActor*> SpawnedCables;
};
