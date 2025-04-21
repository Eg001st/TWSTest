// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TWSCableActor.generated.h"

class UCableComponent;

UCLASS()
class TWSTEST_API ATWSCableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATWSCableActor();

	TObjectPtr<UCableComponent> GetCableComponent() const {return Cable;}


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cable")
	TObjectPtr<UCableComponent> Cable;
};

