// Fill out your copyright notice in the Description page of Project Settings.


//#include "QuantumDisplayActorComponent.h"
//
//// Sets default values for this component's properties
//UQuantumDisplayActorComponent::UQuantumDisplayActorComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UQuantumDisplayActorComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}
//
////
////// Called every frame
////void UQuantumDisplayActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
////{
////	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
////
////	// ...
////}
////
//////void UQuantumDisplayActorComponent::InitializeDisplayMapsForKetCurrent(
//////	TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualToISMC){
//////	SetMaterialInterfacesToISMC(MapActualToISMC, );
//////	for()
//////}
////void UQuantumDisplayActorComponent::InitializeDisplayStructuresForKetCircuit(
////	UMultiMapIntegerActorComponent* InputMMIAC,
////	FQuantumDisplayParam& InputDisplayParam,
////	TMap<int32, FVector2D>& InputStartingKetMap,
////	TArray<FQuantumGateSpecifier>& InputGateArray,
////	TMap<FIntVector, FVector2D>& InputOperatorMapToUpdate,
////	TMap<FIntVector, FVector2D>& InputTransitionMapToUpdate,
////	TMap<FIntPoint, FVector2D>& InputKetMapToUpdate,
////	bool& SuccessFlag) {
////	int32 LocalQubitCount = -1;
////	if (InputGateArray.Num() > 0) {
////		bool LocalSuccessFlag = true;
////		LocalQubitCount = InputGateArray[0].QubitCount;
////		for (auto& iter : InputGateArray) {
////			if (iter.QubitCount != LocalQubitCount) LocalSuccessFlag = false;
////		}
////		QuantumDisplayParam = InputDisplayParam;
////		if (LocalSuccessFlag) {
////			GetAllTransitionOperationKetFlagged(
////				InputGateArray,
////				InputStartingKetMap,
////				LocalQubitCount,
////				InputOperatorMapToUpdate,
////				InputTransitionMapToUpdate,
////				InputKetMapToUpdate,
////				LocalSuccessFlag);
////			GetQuantumDisplayDerived(
////				InputMMIAC,
////				InputOperatorMapToUpdate,
////				InputTransitionMapToUpdate,
////				InputKetMapToUpdate,
////				QuantumDisplayParam,
////				QuantumDisplayDerived);
////			InitializeQubitSplitDisplay(
////				InputMMIAC,
////				QuantumDisplayParam, //InputDisplayParam,
////				QuantumDisplayDerived, //InputQuantumDisplayDerived,
////				QubitSplitDisplay);
////			MapIntPointKetDisplay.Empty();
////			for (auto& iter : QuantumDisplayDerived.MapPositionKetInitialMainState) {
////				FQuantumKetDisplay LocalQuantumKetDisplay;
////				InitializeQuantumKetMainStateDisplay(
////					InputMMIAC,
////					QuantumDisplayParam, //InputDisplayParam,
////					QuantumDisplayDerived, //InputQuantumDisplayDerived,
////					iter.Key.X,
////					iter.Key.Y,
////					LocalSuccessFlag,
////					LocalQuantumKetDisplay);
////				MapIntPointKetDisplay.Add(iter.Key, LocalQuantumKetDisplay);
////			}
////			MapIntVectorTransitionDisplay.Empty();
////			for (auto& iter : InputTransitionMapToUpdate) {
////				FQuantumTransitionDisplay LocalQuantumTransitionDisplay;
////				InitializeQuantumTransitionSubstateDisplay(
////					InputMMIAC,
////					QuantumDisplayParam, //InputDisplayParam,
////					QuantumDisplayDerived, //InputQuantumDisplayDerived,
////					iter.Key.X,
////					iter.Key.Y,
////					iter.Key.Z,
////					LocalSuccessFlag,
////					LocalQuantumTransitionDisplay);
////				MapIntVectorTransitionDisplay.Add(iter.Key, LocalQuantumTransitionDisplay);
////			}
////			
////		}
////	}
////}