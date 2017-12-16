// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfiniteRunnerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);

public:

	AInfiniteRunnerGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PopulateBoundsVolumePool();	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UActorPool* NavMeshBoundsVolumePool;
	
	
	
};
