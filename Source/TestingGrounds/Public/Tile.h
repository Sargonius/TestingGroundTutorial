// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT(BlueprintType)
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FVector Location;
	UPROPERTY(BlueprintReadWrite)
	float Rotation;
	UPROPERTY(BlueprintReadWrite)
	float Scale;
};

USTRUCT(BlueprintType)
struct FSpawnParameters
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	int32 MinSpawn = 1;
	UPROPERTY(BlueprintReadWrite)
	int32 MaxSpawn = 1;
	UPROPERTY(BlueprintReadWrite)
	float Radius = 500;
	UPROPERTY(BlueprintReadWrite)
	float MinScale = 1;
	UPROPERTY(BlueprintReadWrite)
	float MaxScale = 1;
};

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnParameters SpawnParameters);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnParameters SpawnParameters);

	UFUNCTION(BlueprintCallable)
	void SetPool(UActorPool* Pool);

	void PositionNavMeshBoundsVolume();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FVector NavigationVolumeOffset;

private:

	TArray<FSpawnPosition> RandomSpawnPositions(FSpawnParameters SpawnParameters);

	bool CanSpawnAtLocation(FVector Location, float Radius);
	
	bool FindEmptyLocation(FVector &OutLocation, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FSpawnParameters SpawnPosition);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);
	
	UActorPool* Pool;
	AActor* NavMeshBoundsVolume;
};
