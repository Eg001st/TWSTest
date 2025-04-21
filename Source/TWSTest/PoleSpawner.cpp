// Fill out your copyright notice in the Description page of Project Settings.

#include "PoleSpawner.h"

#include "CableComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

#include "TWSBasePole.h"
#include "TWSCableActor.h"

APoleSpawner::APoleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;
}

void APoleSpawner::BeginPlay()
{
	Super::BeginPlay();
	ClearExistingSetup();
	SpawnPolesAndCables();
}

void APoleSpawner::RebuildPolesAndLines()
{
	ClearExistingSetup();
	SpawnPolesAndCables();
}

void APoleSpawner::ClearPolesAndLines()
{
	ClearExistingSetup();
}

void APoleSpawner::ClearExistingSetup()
{
	for (auto* Pole : SpawnedPoles)
	{
		if (Pole)
		{
			Pole->Destroy();
		}
	}
	SpawnedPoles.Empty();

	for (auto* Cable : SpawnedCables)
	{
		if (Cable)
		{
			Cable->Destroy();
		}
	}
	SpawnedCables.Empty();
}

void APoleSpawner::SpawnPolesAndCables()
{
	if (!PoleClass || !CableClass) return;

	SpawnPoles();
	SpawnCables();
}

void APoleSpawner::SpawnCables()
{
	for (int32 i = 0; i < SpawnedPoles.Num() - 1; ++i)
	{
		const ATWSBasePole* StartPole = SpawnedPoles[i];
		const ATWSBasePole* EndPole = SpawnedPoles[i + 1];

		if (StartPole->GetNumCablePairs() != EndPole->GetNumCablePairs()) continue;

		const int32 NumCablesPerPole = StartPole->GetNumCablePairs();

		const auto StartMesh = StartPole->GetMeshComponent();
		const auto EndMesh = EndPole->GetMeshComponent();

		for (int32 CableIndex = 1; CableIndex <= NumCablesPerPole; ++CableIndex)
		{
			const FString StartSocketName = FString::Printf(TEXT("CableSocket%d"), CableIndex);
			const FString EndSocketName = FString::Printf(TEXT("EndCableSocket%d"), CableIndex);

			if (!StartMesh->DoesSocketExist(FName(*StartSocketName)) || !EndMesh->DoesSocketExist(FName(*EndSocketName)))
				continue;

			ATWSCableActor* CableActor = GetWorld()->SpawnActor<ATWSCableActor>(CableClass);
			if (!CableActor) return;
			auto CableComponent = CableActor->GetCableComponent();

			CableComponent->SetAttachEndToComponent(EndMesh, FName(*EndSocketName));
			CableComponent->AttachToComponent(StartMesh, FAttachmentTransformRules::KeepWorldTransform, FName(*StartSocketName));
			CableComponent->SetWorldLocation(StartMesh->GetSocketLocation(FName(*StartSocketName)));

			CableComponent->CableLength = FVector::Distance(
				StartMesh->GetSocketLocation(FName(*StartSocketName)),
				EndMesh->GetSocketLocation(FName(*EndSocketName)));

			UE_LOG(LogTemp, Display, TEXT("Spawning Cable: %s -> %s"),
				*StartPole->GetName(),
				*EndPole->GetName());

			SpawnedCables.Add(CableActor);
		}
	}
}

void APoleSpawner::SpawnPoles()
{
	const float SplineLength = Spline->GetSplineLength();
	const int32 NumPoints = FMath::FloorToInt(SplineLength / DistanceBetweenPoles);

	for (int32 i = 0; i <= NumPoints; ++i)
	{
		const float Distance = i * DistanceBetweenPoles;
		const FVector Location = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		const FRotator Rotation = Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

		ATWSBasePole* Pole = GetWorld()->SpawnActor<ATWSBasePole>(PoleClass, Location, Rotation);
		if (Pole)
		{
			SpawnedPoles.Add(Pole);
		}
	}
}


