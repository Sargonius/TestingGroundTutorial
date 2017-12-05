// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusAtPoint.h"

EBTNodeResult::Type UFocusAtPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	/*// Get the patrol route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	// Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Point = BlackboardComp->GetValueAsObject(PointKey.SelectedKeyName);

	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);*/

	return EBTNodeResult::Succeeded;
}


