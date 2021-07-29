// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ActorComponent.h"
#include "MultiMapIntegerActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUBITLAND_API UMultiMapIntegerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultiMapIntegerActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntPoint> MapFullKetSpace;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FVector2D> MapOperationsComplexNumbers;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FVector2D> MapTransitionsComplexNumbers;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntPoint, FVector2D> MapInitialKetComplexNumbers;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector,bool>

	//TMultiMap<int32, int32> MapQubitIndexTrueToKets;
	//TMultiMap<int32, int32> MapQubitIndexFalseToKets;
	//TMultiMap<FIntPoint, FIntVector> OperationQubitZeroFalse;
	//TMultiMap<FIntPoint, FIntVector> IndexToOperations;

	TMultiMap<int32, FIntVector> IndexToOperations;
	TMultiMap<int32, FIntVector> IndexToTransitions;
	TMultiMap<int32, FIntPoint> IndexToInitialKets;
	TMultiMap<int32, FIntPoint> IndexToFinalKets;

	TMultiMap<FIntPoint, int32> InitialKetToIndex;
	TMultiMap<FIntPoint, FIntPoint> InitialKetToFinalKets;
	TMultiMap<FIntPoint, FIntVector> InitialKetToOperators;
	TMultiMap<FIntPoint, FIntVector> InitialKetToTransitions;

	TMultiMap<FIntPoint, FIntPoint> FinalKetToInitialKets;
	TMultiMap<FIntPoint, FIntVector> FinalKetToOperators;
	TMultiMap<FIntPoint, FIntVector> FinalKetToTransitions;
	TMultiMap<FIntPoint, int32> FinalKetToIndex;

	TMultiMap<FIntVector, int32> OperationToIndex;
	TMultiMap<FIntVector, FIntVector> OperationToTransitions;
	TMultiMap<FIntVector, FIntPoint> OperationToInitialKets;
	TMultiMap<FIntVector, FIntPoint> OperationToFinalKets;

	TMultiMap<FIntVector, int32> TransitionToIndex;
	TMultiMap<FIntVector, FIntVector> TransitionToOperations;
	TMultiMap<FIntVector, FIntPoint> TransitionToInitialKets;
	TMultiMap<FIntVector, FIntPoint> TransitionToFinalKets;

	TMultiMap<FIntPoint, FIntVector> DestinationInitialKetToOperators;
	TMultiMap<FIntPoint, FIntVector> DestinationInitialKetToTransitions;


	TMultiMap<int32, FIntPoint> KetToQubitSplits;
	TMultiMap<FIntPoint, FIntPoint> QubitSplitToQubitSplitsChildren;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntPoint, FIntPoint> QubitSplitToQubitSplitBase;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntPoint, FIntPoint> QubitSplitToQubitSplitBaseZeroFalse;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntPoint, FIntPoint> QubitSplitToQubitSplitBaseOneTrue;
	TMultiMap<int32, FIntPoint> QubitToQubitSplits;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntPoint, FIntVector> QubitSplitAddressToLocationIntVector;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int32 OperatorCount;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int32 QubitCount;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int32 KetStateCount;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<int32,int32> IndexToSubstateCount;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, int32> OperatorSourceSubstate;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, int32> OperatorTargetSubstate;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, int32> TransitionSourceSubstate;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, int32> TransitionTargetSubstate;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FIntVector> OperatorFromToStateSubstateMap;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntVector> OperatorMatrices;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntVector> TransitionMatrices;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntPoint> InitialKets;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntPoint> FinalKets;
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnIndexToOperations(
			UPARAM() int32 Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnIndexToTransitions(
			UPARAM() int32 Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnIndexToInitialKets(
			UPARAM() int32 Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnIndexToFinalKets(
			UPARAM() int32 Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnInitialKetToIndex(
			UPARAM() FIntPoint Input,
			TArray<int32>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnInitialKetToFinalKets(
			UPARAM() FIntPoint Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnInitialKetToOperators(
			UPARAM() FIntPoint Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnInitialKetToTransitions(
			UPARAM() FIntPoint Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnFinalKetToInitialKets(
			UPARAM() FIntPoint Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnFinalKetToOperators(
			UPARAM() FIntPoint Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnFinalKetToTransitions(
			UPARAM() FIntPoint Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnFinalKetToIndex(
			UPARAM() FIntPoint Input,
			TArray<int32>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnOperationToIndex(
			UPARAM() FIntVector Input,
			TArray<int32>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnOperationToTransitions(
			UPARAM() FIntVector Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnOperationToInitialKets(
			UPARAM() FIntVector Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnOperationToFinalKets(
			UPARAM() FIntVector Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnTransitionToIndex(
			UPARAM() FIntVector Input,
			TArray<int32>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnTransitionToOperations(
			UPARAM() FIntVector Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnTransitionToInitialKets(
			UPARAM() FIntVector Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnTransitionToFinalKets(
			UPARAM() FIntVector Input,
			TArray<FIntPoint>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnDestinationInitialKetToOperators(
			UPARAM() FIntPoint Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnDestinationInitialKetToTransitions(
			UPARAM() FIntPoint Input,
			TArray<FIntVector>& Output);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void InitializationOfMapToMaps(
			UPARAM() int32 InputOperatorCount,
			UPARAM() int32 InputQubitCount,
			UPARAM(ref) TArray<FIntVector>& InputOperatorMatrices,
			UPARAM(ref) TArray<FIntVector>& InputTransitionMatrices,
			UPARAM(ref) TArray<FIntPoint>& InputInitialKets);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void InitializationOfMapToMapsPlusComplexNumbers(
			UPARAM() int32 InputOperatorCount,
			UPARAM() int32 InputQubitCount,
			UPARAM(ref) TArray<FIntVector>& InputOperatorMatrices,
			UPARAM(ref) TArray<FIntVector>& InputTransitionMatrices,
			UPARAM(ref) TArray<FIntPoint>& InputInitialKets,
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputOperatorMatricesComplexNumbers,
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputTransitionMatricesComplexNumbers,
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputInitialKetsComplexNumbers);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void GetRangeOperationStateFromInitial(
			UPARAM(ref) TArray<FIntPoint>& InputIntPointArray,
			//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
			//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
			FIntPoint& OperationIndexRange,
			FIntPoint& KetStateRange);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void GetRangeOperationStateFromFinal(
			UPARAM(ref) TArray<FIntPoint>& InputIntPointArray,
			//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
			//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
			FIntPoint& OperationIndexRange,
			FIntPoint& KetStateRange);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void GetRangeOperationStateFromTransition(
			UPARAM(ref) TArray<FIntVector>& InputIntVectorArray,
			//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
			//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
			FIntPoint& OperationIndexRange,
			FIntPoint& KetStateRange);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
//		void GetQubitTunnelsForGivenQubit(
//			UPARAM() int32 InputQubit,
//			//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
//			//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
//			TArray<FIntPoint>& TunnelArray);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
//		void GetQubitTunnelsForGivenQubitBool(
//			UPARAM() int32 InputQubit,
//			UPARAM() bool InputQubitState,
//			//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
//			//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
//			TArray<FIntPoint>& TunnelArray);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
//		void GetQubitSplitsForGivenQubit(
//			UPARAM() int32 InputQubit,
//			//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
//			//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
//			TArray<FIntPoint>& OperationIndexRange,
//			TArray<FIntPoint>& OperationIndexRange,
//			TArray<FIntPoint>& OperationIndexRange,
//			TArray<FIntPoint>& KetStateRange);
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// BEGIN SPECIALIZED FUNCTIONS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetAllForOpKetFromKetTo(
			UPARAM(ref) TArray <int32>& InputOpArray,
			UPARAM(ref) TArray <int32>& InputKetFromArray,
			UPARAM(ref) TArray <int32>& InputKetToArray,
			TArray<FIntVector>& OutputArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetAllForOpKet(
			UPARAM(ref) TArray <int32>& InputOpArray,
			UPARAM(ref) TArray <int32>& InputKetArray,
			TArray<FIntPoint>& OutputArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetAllForOpKetQubit(
			UPARAM(ref) TArray <int32>& InputOpArray,
			UPARAM(ref) TArray <int32>& InputKetArray,
			UPARAM(ref) TArray <int32>& InputQubitArray,
			TArray<FIntVector>& OutputArray);
	
	//UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
	//	void FxnGetQubitSplitPath(
	//		UPARAM() int32 InputQubit,
	//		UPARAM() bool InputPathDirection,
	//		TArray<FIntPoint>& Output);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
	//	void FxnGetQubitSplitPathOverlap(
	//		UPARAM(ref) TMap<int32, bool>& Input,
	//		TArray<FIntPoint>& Output);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
	//	void FxnGetOpKetQubit(
	//		UPARAM() int32 InputOp,
	//		UPARAM() int32 InputQubit,
	//		UPARAM() bool InputPathDirection,
	//		TArray<FIntVector>& Output);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
	//	void FxnGetOpKetQubitOverlap(
	//		UPARAM() int32 InputOp,
	//		UPARAM(ref) TMap<int32, bool>& Input,
	//		TArray<FIntVector>& Output);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
	//	void FxnGetOpKetQubit(
	//		UPARAM() int32 InputOp,
	//		UPARAM() int32 InputQubit,
	//		UPARAM() bool InputPathDirection,
	//		TArray<FIntVector>& Output);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
	//	void FxnGetOpKetQubitOverlap(
	//		UPARAM() int32 InputOp,
	//		UPARAM(ref) TMap<int32, bool>& InputQubit,
	//		TArray<FIntVector>& Output);
	//TMap<int32, bool> GetPathOfKetState(int32 InputKetStateIndex) {
	//	TMap<int32, bool> LocalMap;
	//	uint32 LocalValue = InputKetStateIndex;
	//	for (int32 QubitIndex = 0; QubitIndex < QubitCount; QubitIndex++) {
	//		if ((LocalValue >> QubitIndex) % 2 == 0) {
	//			LocalMap.Add(QubitIndex, false);
	//		}
	//		else {
	//			LocalMap.Add(QubitIndex, true);
	//		}
	//	}
	//	return LocalMap;
	//};
	//TMap<int32, bool> GetPathOfKetStateSelected(int32 InputKetStateIndex, TArray<int32>& SelectedQubits) {
	//	TMap<int32, bool> LocalMap;
	//	uint32 LocalValue = InputKetStateIndex;
	//	for (int32 QubitIndex = 0; QubitIndex < QubitCount; QubitIndex++) {
	//		if (SelectedQubits.Contains(QubitIndex)) {
	//			if ((LocalValue >> QubitIndex) % 2 == 0) {
	//				LocalMap.Add(QubitIndex, false);
	//			}
	//			else {
	//				LocalMap.Add(QubitIndex, true);
	//			}
	//		}
	//	}
	//	return LocalMap;
	//};
	//int32 GetKetFromPath(TMap<int32, bool>& InputMap) {
	//	TArray<int32, bool> LocalMap;
	//	uint32 LocalValue = 1;
	//	uint32 FinalValue = 0;
	//	for (auto& iter : InputMap) {
	//		if (iter.Value) {
	//			FinalValue += (LocalValue << iter.Key);
	//		}
	//	}
	//	return FinalValue;
	//};
};
