// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationVolumeOffset = FVector(2000, 0, 0);

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No actor to return!"));
		return;
	}

	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FSpawnPosition> ATile::RandomSpawnPositions(FSpawnParameters SpawnParameters)
{
	TArray<FSpawnPosition> SpawnPositions;
	int32 NumberToSpawn = FMath::RandRange(SpawnParameters.MinSpawn, SpawnParameters.MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(SpawnParameters.MinScale, SpawnParameters.MaxScale);
		bool CanSpawn = FindEmptyLocation(SpawnPosition.Location, SpawnParameters.Radius * SpawnPosition.Scale);
		if (CanSpawn)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			//
			SpawnPositions.Add(SpawnPosition);
		}
	}

	return SpawnPositions;
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnParameters SpawnParameters)
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(SpawnParameters);

	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

void ATile::SetPool(UActorPool* InPool)
{
	Pool = InPool;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();

	if (NavMeshBoundsVolume == nullptr) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No actors in pool!"));
		return; 
	}
	FVector NavMeshLocation = GetActorLocation();
	NavMeshLocation += NavigationVolumeOffset;
	NavMeshBoundsVolume->SetActorLocation(NavMeshLocation);
	GetWorld()->GetNavigationSystem()->Build();
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit =  GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));

	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), GlobalLocation, Radius, 10, ResultColor, true, 100);

	return !HasHit;
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	FVector Min = FVector(0, -2000, 0);
	FVector Max = FVector(4000, 2000, 0);
	FBox Bound(Min, Max);
	for (int i = 0; i < 10; i++)
	{
		auto TestPoint = FMath::RandPointInBox(Bound);
		if (CanSpawnAtLocation(TestPoint, Radius))
		{
			OutLocation = TestPoint;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

