// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantumCircuitMapActorComponent.h"
TMap<FIntVector, FVector2D> UQuantumCircuitMapActorComponent::GetAllFromOperators(
	TArray<FIntVector>& InputArray) {
	TMap<FIntVector, FVector2D> OutputMap;
	for (auto& iter : InputArray) {
		if (MapOperationsComplexNumbers.Contains(iter)) {
			OutputMap.Add(iter, MapOperationsComplexNumbers[iter]);
		}
	}
	return OutputMap;
}
TMap<FIntVector, FVector2D> UQuantumCircuitMapActorComponent::GetAllFromTransitions(
	TArray<FIntVector>& InputArray) {
	TMap<FIntVector, FVector2D> OutputMap;
	for (auto& iter : InputArray) {
		if (MapTransitionsComplexNumbers.Contains(iter)) {
			OutputMap.Add(iter, MapTransitionsComplexNumbers[iter]);
		}
	}
	return OutputMap;
}
TMap<FIntPoint, FVector2D> UQuantumCircuitMapActorComponent::GetAllFromInitialKets(
	TArray<FIntPoint>& InputArray) {
	TMap<FIntPoint, FVector2D> OutputMap;
	for (auto& iter : InputArray) {
		if (MapInitialKetComplexNumbers.Contains(iter)) {
			OutputMap.Add(iter, MapInitialKetComplexNumbers[iter]);
		}
	}
	return OutputMap;
}
void UQuantumCircuitMapActorComponent::InitializationOfQuantumCircuitMapsProcessed(
	int32 InputOperatorCount,
	int32 InputQubitCount,
	TMap<FIntVector, FVector2D> InputOperatorMatricesComplexNumbers,
	TMap<FIntVector, FVector2D> InputTransitionMatricesComplexNumbers,
	TMap<FIntPoint, FVector2D> InputInitialKetsComplexNumbers,
	float InputToleranceLevel) {
	TArray<FIntVector> LocalOperatorMatricesAddressArray;
	TArray<FIntVector> LocalTransitionMatricesAddressArray;
	TArray<FIntPoint> LocalInitialKetsAddressArray;
	for (auto& iter : InputOperatorMatricesComplexNumbers) {
		LocalOperatorMatricesAddressArray.Add(iter.Key);
		MapOperationsComplexNumbers.Add(iter.Key, iter.Value);
	}
	for (auto& iter : InputTransitionMatricesComplexNumbers) {
		LocalTransitionMatricesAddressArray.Add(iter.Key);
		MapTransitionsComplexNumbers.Add(iter.Key, iter.Value);
	}
	for (auto& iter : InputInitialKetsComplexNumbers) {
		LocalInitialKetsAddressArray.Add(iter.Key);
		MapInitialKetComplexNumbers.Add(iter.Key, iter.Value);
	}
	//InputOperatorMatricesComplexNumbers.GetKeys(LocalOperatorMatricesAddressArray);
	//InputTransitionMatricesComplexNumbers.GetKeys(LocalTransitionMatricesAddressArray);
	//InputInitialKetsComplexNumbers.GetKeys(LocalInitialKetsAddressArray);
	InitializationOfMapToMaps(
		InputOperatorCount,
		InputQubitCount,
		LocalOperatorMatricesAddressArray,
		LocalTransitionMatricesAddressArray,
		LocalInitialKetsAddressArray);
	for (int32 LocalOperatorIndex = 0; LocalOperatorIndex < OperatorCount; LocalOperatorIndex++) {
		TArray<FIntVector> CurrentOperationsKeyArray;
		IndexToOperations.MultiFind(LocalOperatorIndex, CurrentOperationsKeyArray);
		TMap<FIntVector, FVector2D> OperationMapCurrent = 
			GetAllFromOperators(CurrentOperationsKeyArray);
		TArray<FVector2D> OperationMapValuesCurrent;
		OperationMapCurrent.GenerateValueArray(OperationMapValuesCurrent);
		bool OutputBool;
		int32 OutputInt;
		UQuantumLandBlueprintFxnLibrary::FxnGetValidDivisor(
			OperationMapValuesCurrent, QubitCount, InputToleranceLevel, OutputBool, OutputInt);
		if (OutputBool) {
			MapOperationsDenominatorPowerOfTwo.Add(LocalOperatorIndex, OutputInt);
			UQuantumLandBlueprintFxnLibrary::FxnGetIntVectorDyadicMapFromIntVectorComplex(
				OperationMapCurrent, InputToleranceLevel, OutputInt, MapOperationsDyadic, OutputBool);
		}
	}
	for (int32 LocalOperatorIndex = 0; LocalOperatorIndex < OperatorCount; LocalOperatorIndex++) {
		TArray<FIntVector> CurrentTransitionsKeyArray;
		IndexToTransitions.MultiFind(LocalOperatorIndex, CurrentTransitionsKeyArray);
		TMap<FIntVector, FVector2D> TransitionMapCurrent =
			GetAllFromTransitions(CurrentTransitionsKeyArray);
		TArray<FVector2D> TransitionMapValuesCurrent;
		TransitionMapCurrent.GenerateValueArray(TransitionMapValuesCurrent);
		bool OutputBool;
		int32 OutputInt;
		UQuantumLandBlueprintFxnLibrary::FxnGetValidDivisor(
			TransitionMapValuesCurrent, QubitCount, InputToleranceLevel, OutputBool, OutputInt);
		if (OutputBool) {
			MapTransitionsDenominatorPowerOfTwo.Add(LocalOperatorIndex, OutputInt);
			UQuantumLandBlueprintFxnLibrary::FxnGetIntVectorDyadicMapFromIntVectorComplex(
				TransitionMapCurrent, InputToleranceLevel, OutputInt, MapTransitionsDyadic, OutputBool);
		}
	}
	for (int32 LocalOperatorIndex = 0; LocalOperatorIndex < OperatorCount; LocalOperatorIndex++) {
		TArray<FIntPoint> CurrentInitialKetsKeyArray;
		IndexToInitialKets.MultiFind(LocalOperatorIndex, CurrentInitialKetsKeyArray);
		TMap<FIntPoint, FVector2D> InitialKetMapCurrent =
			GetAllFromInitialKets(CurrentInitialKetsKeyArray);
		TArray<FVector2D> InitialKetMapValuesCurrent;
		InitialKetMapCurrent.GenerateValueArray(InitialKetMapValuesCurrent);
		bool OutputBool;
		int32 OutputInt;
		UQuantumLandBlueprintFxnLibrary::FxnGetValidDivisor(
			InitialKetMapValuesCurrent, QubitCount, InputToleranceLevel, OutputBool, OutputInt);
		if (OutputBool) {
			MapInitialKetsDenominatorPowerOfTwo.Add(LocalOperatorIndex, OutputInt);
			UQuantumLandBlueprintFxnLibrary::FxnGetIntPointDyadicMapFromIntPointComplex(
				InitialKetMapCurrent, InputToleranceLevel, OutputInt, MapInitialKetsDyadic, OutputBool);
		}
	}



}
FString UQuantumCircuitMapActorComponent::GetStringDyadicDisplay(FQuantumDyadicComplexRadical& DyadicInput) {
	return FString("(" + FString::FromInt(DyadicInput.NumeratorReal) + ","
		+ FString::FromInt(DyadicInput.RationalReal) + ","
		+ FString::FromInt(DyadicInput.NumeratorImaginary) + ","
		+ FString::FromInt(DyadicInput.RationalImaginary) + ","
		+ FString::FromInt(DyadicInput.PowerOfTwoDenominator) + ")");
}
void UQuantumCircuitMapActorComponent::FxnGetIntVectorMapDyadicDisplay(
	FString NameDyadicMap,
	TMap < FIntVector, FQuantumDyadicComplexRadical>& DyadicMapInput,
	TArray<FString>& OutputStringList) {
	OutputStringList.Add(NameDyadicMap);
	for (auto& iter: DyadicMapInput) {
		OutputStringList.Add(FString(iter.Key.ToString() + GetStringDyadicDisplay(iter.Value)));
	}
}
void UQuantumCircuitMapActorComponent::FxnGetIntPointMapDyadicDisplay(
	FString NameDyadicMap,
	TMap < FIntPoint, FQuantumDyadicComplexRadical>& DyadicMapInput,
	TArray<FString>& OutputStringList) {
	OutputStringList.Add(NameDyadicMap);
	for (auto& iter : DyadicMapInput) {
		OutputStringList.Add(FString(iter.Key.ToString() + "->" + GetStringDyadicDisplay(iter.Value)));
	}
}
void UQuantumCircuitMapActorComponent::FxnGetIntVectorMapComplexDisplay(
	FString NameDyadicMap,
	TMap < FIntVector, FVector2D>& ComplexMapInput,
	TArray<FString>& OutputStringList) {
	OutputStringList.Add(NameDyadicMap);
	for (auto& iter : ComplexMapInput) {
		OutputStringList.Add(FString(iter.Key.ToString() + "->" + iter.Value.ToString()));
	}
}
void UQuantumCircuitMapActorComponent::FxnGetIntPointMapComplexDisplay(
	FString NameDyadicMap,
	TMap < FIntPoint, FVector2D>& ComplexMapInput,
	TArray<FString>& OutputStringList) {
	OutputStringList.Add(NameDyadicMap);
	for (auto& iter : ComplexMapInput) {
		OutputStringList.Add(FString(iter.Key.ToString() + "->" + iter.Value.ToString()));
	}
}
void UQuantumCircuitMapActorComponent::FxnGetAllMapsDisplay(
	TArray<FString>& OutputStringList) {
	FxnGetIntVectorMapComplexDisplay(
		"MapOperationsComplexNumbers",
		MapOperationsComplexNumbers,
		OutputStringList);
	FxnGetIntVectorMapComplexDisplay(
		"MapTransitionsComplexNumbers",
		MapTransitionsComplexNumbers,
		OutputStringList);
	FxnGetIntPointMapComplexDisplay(
		"MapInitialKetComplexNumbers",
		MapInitialKetComplexNumbers,
		OutputStringList);
	FxnGetIntVectorMapDyadicDisplay(
		"MapOperationsDyadic",
		MapOperationsDyadic,
		OutputStringList);
	FxnGetIntVectorMapDyadicDisplay(
		"MapTransitionsDyadic",
		MapTransitionsDyadic,
		OutputStringList);
	FxnGetIntPointMapDyadicDisplay(
		"MapInitialKetsDyadic",
		MapInitialKetsDyadic,
		OutputStringList);
}