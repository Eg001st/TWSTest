// Fill out your copyright notice in the Description page of Project Settings.


#include "TWSBasePole.h"

#include "Components/StaticMeshComponent.h"

ATWSBasePole::ATWSBasePole()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
}
