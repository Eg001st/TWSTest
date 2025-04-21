// Fill out your copyright notice in the Description page of Project Settings.


#include "TWSCableActor.h"

#include "CableComponent.h"
#include "Components/SceneComponent.h"



ATWSCableActor::ATWSCableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	Cable->SetupAttachment(RootComponent);
	Cable->EndLocation = FVector::ZeroVector;
	Cable->CableLength = 300.0f;
	Cable->NumSegments = 20;
	Cable->SolverIterations = 8;
	Cable->bEnableStiffness = true;
	Cable->bEnableCollision = false;
}


