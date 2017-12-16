// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteRunnerGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPool.h"
#include "EngineUtils.h"

AInfiniteRunnerGameMode::AInfiniteRunnerGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(TEXT("ActorPoolComponent"));

}


void AInfiniteRunnerGameMode::PopulateBoundsVolumePool()
{
	auto NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	while (NavMeshIterator)
	{
		AddToPool(*NavMeshIterator);
		//ANavMeshBoundsVolume* FoundNavMesh = *NavMeshIterator;
		//UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *FoundActor->GetName());
		++NavMeshIterator;
	}
}

void AInfiniteRunnerGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("NavMesh: %s"), *VolumeToAdd->GetName());
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}

void AInfiniteRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

}



