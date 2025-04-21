// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TWSBasePole.generated.h"

class UStaticMeshComponent;

UCLASS(Blueprintable)
class TWSTEST_API ATWSBasePole : public AActor
{
	GENERATED_BODY()

public:

	ATWSBasePole();

public:

	TObjectPtr<UStaticMeshComponent> GetMeshComponent() const {return MeshComponent;}

	int32 GetNumCablePairs() const {return NumCablePairs;}
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pole Config")
	int32 NumCablePairs = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
