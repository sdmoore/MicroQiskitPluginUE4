// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantumLandBlueprintFxnLibrary.h"

/*static */void UQuantumLandBlueprintFxnLibrary::InitializeQuantumOperatorWithSpecifier(FQuantumGateSpecifier& InputRefQuantumGateSpecifier, TMap<FIntPoint, FVector2D>& InputRefTMapMatrixKetSpace) {
	return InitializeQuantumOperator(InputRefQuantumGateSpecifier.EnumGateType,
		InputRefQuantumGateSpecifier.QubitCount,
		InputRefQuantumGateSpecifier.ControlQubitArray,
		InputRefQuantumGateSpecifier.TargetQubitArray,
		InputRefTMapMatrixKetSpace);
}
/*static */void UQuantumLandBlueprintFxnLibrary::InitializeQuantumOperator(
	EQuantumGateType InputQuantumGateType,
	uint8 InputQubitCount,
	TArray<uint8>& InputControlQubitArray,
	TArray<uint8>& InputTargetQubitArray,
	//TMap<FIntPoint, FVector2D>& InputRefTMapMatrixKetSpace){
	TMap<FIntPoint, FVector2D>& OutputTMapMatrixKetSpace) {
	OutputTMapMatrixKetSpace.Empty();
	uint32 LocalHilbertSpaceDim = static_cast<int32>(static_cast<uint32>(1) << static_cast<uint32>(InputQubitCount));
	float LocalSqrtTwo = FMath::Sqrt(2.0);
	float LocalOneOverSqrtTwo = 1.0 / LocalSqrtTwo;
	//bool bTargetQubutFlag = false;
	uint32 LocalTargetQubit;
	if (InputTargetQubitArray.Num() > 0) {
		//bTargetQubutFlag = true;
		LocalTargetQubit = static_cast<uint32>(
			InputTargetQubitArray[0]);
		//bool bControlQubutFlag = false;
		uint32 LocalControlQubit;
		if (InputControlQubitArray.Num() > 0) {
			//bControlQubutFlag = true;
			LocalControlQubit = static_cast<uint32>(
				InputControlQubitArray[0]);
		}
		for (uint32 Index = 0; Index < LocalHilbertSpaceDim; Index++) {

			const uint32 OneUnsignedLong = 1;

			// Toggle Bit functionality
			uint32 BitTargeted = (OneUnsignedLong << (LocalTargetQubit));
			uint32 IndexTargetBitFipped = Index;
			//IndexTargetBitFipped &= ~BitTargeted;
			IndexTargetBitFipped ^= (OneUnsignedLong << LocalTargetQubit);
			//uint32 IndexTargetBitFipped = ToggleBit(Index, LocalTargetQubit);

			// Check Bit functionality
			bool bTargetQubit;
			if (InputTargetQubitArray.Num() > 0) {
				//bTargetQubit = ((Index >> (InputTargetQubitArray[0])) & LocalTargetQubit);
				bTargetQubit = ((Index >> (LocalTargetQubit)) & OneUnsignedLong);
			}
			//bool bTargetQubit = bCheckBit(Index, LocalTargetQubit);

			bool bControlQubit;
			if (InputControlQubitArray.Num() > 0) {
				//bControlQubit = ((Index >> (InputControlQubitArray[0])) & LocalTargetQubit);
				bControlQubit = ((Index >> (LocalControlQubit)) & OneUnsignedLong);
			}
			//bool bControlQubit = bCheckBit(Index, LocalControlQubit);

			FIntPoint CurrentHashUnchanged = FIntPoint(Index, Index);
			FIntPoint CurrentHashTargetBitFlipped = FIntPoint(Index, IndexTargetBitFipped);

			if (InputQuantumGateType == EQuantumGateType::CX/*
				&& InputControlQubitArray.Num() == 1
				&& InputTargetQubitArray.Num() == 1*/) {
				if (bControlQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(1.0, 0.0));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
				}
			}
			else if (InputQuantumGateType == EQuantumGateType::Hadamard) {
				if (bTargetQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(-LocalOneOverSqrtTwo, 0.0));
					OutputTMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(LocalOneOverSqrtTwo, 0.0));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(LocalOneOverSqrtTwo, 0.0));
					OutputTMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(LocalOneOverSqrtTwo, 0.0));
				}
			}
			else if (InputQuantumGateType == EQuantumGateType::X) {
				OutputTMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(1.0, 0.0));
			}
			else if (InputQuantumGateType == EQuantumGateType::Y) {
				if (bTargetQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(0.0, 1.0));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(0.0, -1.0));
				}
			}
			else if (InputQuantumGateType == EQuantumGateType::Z) {
				if (bTargetQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(-1.0, 0.0));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
				}
			}
			else if (InputQuantumGateType == EQuantumGateType::S) {
				if (bTargetQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(0.0, 1.0));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
				}
			}
			else if (InputQuantumGateType == EQuantumGateType::SDagger) {
				if (bTargetQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(0.0, -1.0));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
				}
			}
			else if (InputQuantumGateType == EQuantumGateType::T) {
				if (bTargetQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(LocalOneOverSqrtTwo, LocalOneOverSqrtTwo));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
				}
			}
			else if (InputQuantumGateType == EQuantumGateType::TDagger) {
				if (bTargetQubit) {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(LocalOneOverSqrtTwo, -LocalOneOverSqrtTwo));
				}
				else {
					OutputTMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
				}
			}
		}
	}
	
	
	return;
}

/*static */void UQuantumLandBlueprintFxnLibrary::MultiplyOperatorWithOperatorToOperator(
	TMap<FIntPoint, FVector2D>& MatrixLHS, 
	TMap<FIntPoint, FVector2D>& MatrixRHS,
	TMap<FIntPoint, FVector2D>& MatrixOutput) {
	TMap<FIntPoint, FVector2D> LocalMatrixOutput;
	LocalMatrixOutput.Empty();
	for (auto& iterLHS : MatrixLHS) {
		int32 FromStateLHS = iterLHS.Key.X;// FxnGetInverseHashFromState(iterLHS.Key);
		int32 ToStateLHS = iterLHS.Key.Y;// FxnGetInverseHashToState(iterLHS.Key);
		for (auto& iterRHS : MatrixRHS) {
			int32 FromStateRHS = iterRHS.Key.X;// FxnGetInverseHashFromState(iterRHS.Key);
			int32 ToStateRHS = iterRHS.Key.Y;// FxnGetInverseHashToState(iterRHS.Key);
			if (ToStateRHS == FromStateLHS) {
				FVector2D Input0 = MatrixRHS[iterRHS.Key];
				FVector2D Input1 = MatrixLHS[iterLHS.Key];
				FVector2D AddedValue = FVector2D(
					Input0.X * Input1.X - Input0.Y * Input1.Y,
					Input0.X * Input1.Y + Input0.Y * Input1.X
				);
				FIntPoint AddedKey = FIntPoint(FromStateRHS, ToStateLHS);// FxnGetHash(FromStateRHS, ToStateLHS);
				if (LocalMatrixOutput.Contains(AddedKey)) {
					FVector2D NewValue = LocalMatrixOutput[AddedKey] + AddedValue;
					LocalMatrixOutput.Add(AddedKey, NewValue);
				}
				else LocalMatrixOutput.Add(AddedKey, AddedValue);
			}
		}
	}
	return;
}
/*static */void UQuantumLandBlueprintFxnLibrary::MultiplyOperatorWithKetToKet(
	TMap<FIntPoint, FVector2D>& MatrixLHS, 
	TMap<int32, FVector2D>& KetRHS, 
	TMap<int32, FVector2D>& KetResult) {
	TMap<int32, FVector2D> LocalKetResult;
	LocalKetResult.Empty();
	for (auto& iterLHS : MatrixLHS) {
		int32 FromStateLHS = iterLHS.Key.X;// FxnGetInverseHashFromState(iterLHS.Key);
		int32 ToStateLHS = iterLHS.Key.Y;// FxnGetInverseHashToState(iterLHS.Key);
		for (auto& iterRHS : KetRHS) {
			int32 ToStateRHS = iterRHS.Key;
			if (FromStateLHS == ToStateRHS) {
				FVector2D Input0 = KetRHS[iterRHS.Key];
				FVector2D Input1 = MatrixLHS[iterLHS.Key];
				FVector2D AddedValue = FVector2D(
					Input0.X * Input1.X - Input0.Y * Input1.Y,
					Input0.X * Input1.Y + Input0.Y * Input1.X
				);
				int32 AddedKey = ToStateLHS;
				if (LocalKetResult.Contains(AddedKey)) {
					FVector2D NewValue = LocalKetResult[AddedKey] + AddedValue;
					LocalKetResult.Add(AddedKey, NewValue);
				}
				else LocalKetResult.Add(AddedKey, AddedValue);
			}
		}
	}
	return;
}
/*static */void UQuantumLandBlueprintFxnLibrary::MultiplyOperatorWithKetToOperatorKet(
	TMap<FIntPoint, FVector2D>& MatrixLHS,
	TMap<int32, FVector2D>& KetRHS,
	TMap<FIntPoint, FVector2D>& MatrixResult,
	TMap<int32, FVector2D>& KetResult) {
	float InputErrorMargin = 0.001;
	MatrixResult.Empty();
	KetResult.Empty();
	if (true) // TSharedPtr<FQuantumKet> PinnedWeakPtrQuantumKetInitial = WeakPtrQuantumKetInitial.Pin())
	//if (WeakPtrQuantumKetInitial.IsValid()) 
	{
		for (auto& iterLHS : MatrixLHS) {
			int32 FromStateLHS = iterLHS.Key.X;// FxnGetInverseHashFromState(iterLHS.Key);
			int32 ToStateLHS = iterLHS.Key.Y;// FxnGetInverseHashToState(iterLHS.Key);
			for (auto& iterRHS : KetRHS) {
				int32 ToStateRHS = iterRHS.Key;
				if (FromStateLHS == ToStateRHS) {
					FVector2D Input0 = KetRHS[iterRHS.Key];
					FVector2D Input1 = MatrixLHS[iterLHS.Key];
					FVector2D AddedValue = FVector2D(
						Input0.X * Input1.X - Input0.Y * Input1.Y,
						Input0.X * Input1.Y + Input0.Y * Input1.X
					);
					int32 AddedKeyKet = ToStateLHS;
					FIntPoint AddedKeyMatrix = iterLHS.Key;
					if (MatrixResult.Contains(AddedKeyMatrix)) {
						FVector2D NewValue = MatrixResult[AddedKeyMatrix] + AddedValue;
						MatrixResult.Add(AddedKeyMatrix, NewValue);
					}
					else {
						MatrixResult.Add(AddedKeyMatrix, AddedValue);
					}
					if (KetResult.Contains(AddedKeyKet)) {
						FVector2D NewValue = KetResult[AddedKeyKet] + AddedValue;
						KetResult.Add(AddedKeyKet, NewValue);
					}
					else {
						KetResult.Add(AddedKeyKet, AddedValue);
					}
				}
			}
			float LocalMatrixErrorMargin = InputErrorMargin / static_cast<float>(MatrixResult.Num());
			for (auto& iter : MatrixResult) {
				if (iter.Value.Size() < LocalMatrixErrorMargin) {
					MatrixResult.Remove(iter.Key);
				}
			}
			float LocalKetErrorMargin = InputErrorMargin / static_cast<float>(KetResult.Num());
			TArray<int32> KeysToRemove;
			for (auto& iter : KetResult) {
				if (iter.Value.Size() < LocalKetErrorMargin) {
					KeysToRemove.Add(iter.Key);
				}
			}
			for (auto& iter : KeysToRemove) {
				KetResult.Remove(iter);
			}
		}
	}
	return;
}
/*static */void UQuantumLandBlueprintFxnLibrary::GetTransitionsFromToSubStates(
	TArray<FIntVector>& InputTransitions,
	TMap<int32, int32>& DimensionalityOfOperation,
	TMap<FIntVector, FIntPoint>& FromToSubStateMap,
	TMap<int32, bool>& OperationErrorFlag,
	TMap<FIntVector, bool>& TransitionErrorFlag) {
	if (true)
	{
		for (int32 IndexCurrent = 0; IndexCurrent < InputTransitions.Num(); IndexCurrent++) {
			FIntVector CurrentTransition = InputTransitions[IndexCurrent];
			FIntVector StaticTransition = FIntVector(CurrentTransition.X, CurrentTransition.Y, CurrentTransition.Y);
			if (CurrentTransition.Y == CurrentTransition.Z ||
				(CurrentTransition.Y != CurrentTransition.Z && !(InputTransitions.Contains(StaticTransition)))) {
				if (DimensionalityOfOperation.Contains(CurrentTransition.X)) {
					if (DimensionalityOfOperation[CurrentTransition.X] != 1) {
						OperationErrorFlag.Add(CurrentTransition.X, true);
					}
				}
				else {
					int32 TestInt = CurrentTransition.X;
					DimensionalityOfOperation.Add(TestInt, 1);
				}
				if (FromToSubStateMap.Contains(CurrentTransition)) {
					TransitionErrorFlag.Add(CurrentTransition, true);
				}
				FromToSubStateMap.Add(CurrentTransition, FIntPoint(0, 0));
			}
			else if (CurrentTransition.Y != CurrentTransition.Z && InputTransitions.Contains(StaticTransition)) {
				if (DimensionalityOfOperation.Contains(CurrentTransition.X)) {
					if (DimensionalityOfOperation[CurrentTransition.X] != 2) {
						OperationErrorFlag.Add(CurrentTransition.X, true);
					}
				}
				else {
					DimensionalityOfOperation.Add(CurrentTransition.X, 2);
				}
				if (FromToSubStateMap.Contains(CurrentTransition) || FromToSubStateMap.Contains(StaticTransition)) {
					TransitionErrorFlag.Add(CurrentTransition, true);
				}
				if (CurrentTransition.Y < CurrentTransition.Z) {
					FromToSubStateMap.Add(CurrentTransition, FIntPoint(1, 0));
					FromToSubStateMap.Add(StaticTransition, FIntPoint(0, 0));
				}
				else {
					FromToSubStateMap.Add(CurrentTransition, FIntPoint(0, 1));
					FromToSubStateMap.Add(StaticTransition, FIntPoint(1, 1));
				}
			}
			else {
				TransitionErrorFlag.Add(CurrentTransition, true);
			}

		}
	}
	return;
}

/*static */void UQuantumLandBlueprintFxnLibrary::GetSingleTransitionFromToSubStates(
	FIntVector InputTransition,
	TArray<FIntVector>& InputTransitions,
	TMap<int32, int32>& DimensionalityOfOperation,
	TMap<FIntVector, FIntPoint>& FromToSubStateMap,
	//TMap<FIntVector, bool>& FromToSubStateMap,
	TMap<int32, bool>& OperationErrorFlag,
	TMap<FIntVector, bool>& TransitionErrorFlag) {
	FIntVector CurrentTransition = InputTransition;
	FIntVector StaticTransition = FIntVector(CurrentTransition.X, CurrentTransition.Y, CurrentTransition.Y);
	if (CurrentTransition.Y == CurrentTransition.Z ||
		(CurrentTransition.Y != CurrentTransition.Z && !(InputTransitions.Contains(StaticTransition)))) {
		if (DimensionalityOfOperation.Contains(CurrentTransition.X)) {
			if (DimensionalityOfOperation[CurrentTransition.X] != 1) {
				OperationErrorFlag.Add(CurrentTransition.X, true);
			}
		}
		else {
			int32 TestInt = CurrentTransition.X;
			DimensionalityOfOperation.Add(TestInt, 1);
		}
		if (FromToSubStateMap.Contains(CurrentTransition)) {
			TransitionErrorFlag.Add(CurrentTransition, true);
		}
		FromToSubStateMap.Add(CurrentTransition, FIntPoint(0, 0));
	}
	else if (CurrentTransition.Y != CurrentTransition.Z && InputTransitions.Contains(StaticTransition)) {
		if (DimensionalityOfOperation.Contains(CurrentTransition.X)) {
			if (DimensionalityOfOperation[CurrentTransition.X] != 2) {
				OperationErrorFlag.Add(CurrentTransition.X, true);
			}
		}
		else {
			DimensionalityOfOperation.Add(CurrentTransition.X, 2);
		}
		if (FromToSubStateMap.Contains(CurrentTransition) || FromToSubStateMap.Contains(StaticTransition)) {
			TransitionErrorFlag.Add(CurrentTransition, true);
		}
		if (CurrentTransition.Y < CurrentTransition.Z) {
			FromToSubStateMap.Add(CurrentTransition, FIntPoint(1, 0));
			FromToSubStateMap.Add(StaticTransition, FIntPoint(0, 0));
		}
		else {
			FromToSubStateMap.Add(CurrentTransition, FIntPoint(0, 1));
			FromToSubStateMap.Add(StaticTransition, FIntPoint(1, 1));
		}
	}
	else {
		TransitionErrorFlag.Add(CurrentTransition, true);
	}

	return;
}

/*static */void UQuantumLandBlueprintFxnLibrary::GetTranstionPatterns(
	TArray<FIntVector>& InputTransitions,
	TMap<int32, int32>& FromToConstantDimensionalityOfOperation,
	TMap<int32, int32>& FromToMaxDimensionalityOfOperation,
	TMap<FIntPoint, int32>& FromToStateMapCount,
	TMap<FIntPoint, int32>& FromToStateMapSingle,
	TMap<FIntPoint, FIntPoint>& FromToStateMapDouble,
	TMap<int32, int32>& ToFromConstantDimensionalityOfOperation,
	TMap<int32, int32>& ToFromMaxDimensionalityOfOperation,
	TMap<FIntPoint, int32>& ToFromStateMapCount,
	TMap<FIntPoint, int32>& ToFromStateMapSingle,
	TMap<FIntPoint, FIntPoint>& ToFromStateMapDouble,
	//TMap<FIntVector, bool>& FromToSubStateMap,
	TMap<int32, bool>& OperationErrorFlag,
	TMap<FIntVector, bool>& TransitionErrorFlag) {
	FromToConstantDimensionalityOfOperation.Empty();
	FromToMaxDimensionalityOfOperation.Empty();
	FromToStateMapCount.Empty();
	FromToStateMapSingle.Empty();
	FromToStateMapDouble.Empty();
	ToFromConstantDimensionalityOfOperation.Empty();
	ToFromMaxDimensionalityOfOperation.Empty();
	ToFromStateMapCount.Empty();
	ToFromStateMapSingle.Empty();
	ToFromStateMapDouble.Empty();
	OperationErrorFlag.Empty();
	TransitionErrorFlag.Empty();
	if (true) 
	{
		for (int32 IndexCurrent = 0; IndexCurrent < InputTransitions.Num(); IndexCurrent++) {
			FIntPoint CurrentFromTo = FIntPoint(InputTransitions[IndexCurrent].X, InputTransitions[IndexCurrent].Y);
			if (!FromToStateMapCount.Contains(CurrentFromTo)) {


			}
			if (FromToStateMapCount[CurrentFromTo] == 0) {
				FromToStateMapCount.Add(CurrentFromTo, 1);
				FromToStateMapSingle.Add(CurrentFromTo, InputTransitions[IndexCurrent].Z);
			}
			else if (FromToStateMapCount[CurrentFromTo] == 1) {
				FromToStateMapCount.Add(CurrentFromTo, 2);
				FromToStateMapDouble.Add(CurrentFromTo, FIntPoint(FromToStateMapSingle[CurrentFromTo], InputTransitions[IndexCurrent].Z));
				FromToStateMapSingle.Remove(CurrentFromTo);

			}
			else if (FromToStateMapCount[CurrentFromTo] == 2) {
				FromToStateMapCount.Add(CurrentFromTo, 3);
				FromToStateMapDouble.Remove(CurrentFromTo);

			}
			else if (FromToStateMapCount[CurrentFromTo] > 2) {
				FromToStateMapCount.Add(CurrentFromTo, FromToStateMapCount[CurrentFromTo] + 1);
			}
			else {
				TransitionErrorFlag[InputTransitions[IndexCurrent]] = true;
			}
			FIntPoint CurrentToFrom = FIntPoint(InputTransitions[IndexCurrent].X, InputTransitions[IndexCurrent].Z);
			if (!ToFromStateMapCount.Contains(CurrentToFrom)) {


			}
			if (ToFromStateMapCount[CurrentToFrom] == 0) {
				ToFromStateMapCount.Add(CurrentToFrom, 1);
				ToFromStateMapSingle.Add(CurrentToFrom, InputTransitions[IndexCurrent].Y);
			}
			else if (ToFromStateMapCount[CurrentToFrom] == 1) {
				ToFromStateMapCount.Add(CurrentToFrom, 2);
				ToFromStateMapDouble.Add(CurrentToFrom, FIntPoint(ToFromStateMapSingle[CurrentToFrom], InputTransitions[IndexCurrent].Y));
				ToFromStateMapSingle.Remove(CurrentToFrom);

			}
			else if (ToFromStateMapCount[CurrentToFrom] == 2) {
				ToFromStateMapCount.Add(CurrentToFrom, 3);
				ToFromStateMapDouble.Remove(CurrentToFrom);

			}
			else if (ToFromStateMapCount[CurrentToFrom] > 2) {
				ToFromStateMapCount.Add(CurrentToFrom, ToFromStateMapCount[CurrentToFrom] + 1);
			}
			else {
				TransitionErrorFlag[InputTransitions[IndexCurrent]] = true;
			}
		}
		for (auto& iter : FromToStateMapCount) {
			if (FromToConstantDimensionalityOfOperation.Contains(iter.Key.X) && !FromToMaxDimensionalityOfOperation.Contains(iter.Key.X)) {
				if (iter.Value != FromToConstantDimensionalityOfOperation[iter.Key.X]) {
					int32 Temp = FMath::Max(iter.Value, FromToConstantDimensionalityOfOperation[iter.Key.X]);
					FromToMaxDimensionalityOfOperation.Add(iter.Key.X, Temp);
					FromToConstantDimensionalityOfOperation.Remove(iter.Key.X);
				}
			}
			else if (!FromToConstantDimensionalityOfOperation.Contains(iter.Key.X) && !FromToMaxDimensionalityOfOperation.Contains(iter.Key.X)) {
				FromToConstantDimensionalityOfOperation.Add(iter.Key.X, iter.Value);
			}
			else if (!FromToConstantDimensionalityOfOperation.Contains(iter.Key.X) && FromToMaxDimensionalityOfOperation.Contains(iter.Key.X)) {
				int32 Temp = FMath::Max(iter.Value, FromToConstantDimensionalityOfOperation[iter.Key.X]);
				FromToMaxDimensionalityOfOperation.Add(iter.Key.X, Temp);
			}
		}
		for (auto& iter : ToFromStateMapCount) {
			if (ToFromConstantDimensionalityOfOperation.Contains(iter.Key.X) && !ToFromMaxDimensionalityOfOperation.Contains(iter.Key.X)) {
				if (iter.Value != ToFromConstantDimensionalityOfOperation[iter.Key.X]) {
					int32 Temp = FMath::Max(iter.Value, ToFromConstantDimensionalityOfOperation[iter.Key.X]);
					ToFromMaxDimensionalityOfOperation.Add(iter.Key.X, Temp);
					ToFromConstantDimensionalityOfOperation.Remove(iter.Key.X);
				}
			}
			else if (!ToFromConstantDimensionalityOfOperation.Contains(iter.Key.X) && !ToFromMaxDimensionalityOfOperation.Contains(iter.Key.X)) {
				ToFromConstantDimensionalityOfOperation.Add(iter.Key.X, iter.Value);
			}
			else if (!ToFromConstantDimensionalityOfOperation.Contains(iter.Key.X) && ToFromMaxDimensionalityOfOperation.Contains(iter.Key.X)) {
				int32 Temp = FMath::Max(iter.Value, ToFromConstantDimensionalityOfOperation[iter.Key.X]);
				ToFromMaxDimensionalityOfOperation.Add(iter.Key.X, Temp);
			}
		}
	}

	return;
}

void UQuantumLandBlueprintFxnLibrary::ReturnNormalsPerOperation(
	TMap<FIntVector, FVector2D>& TransitionMatrices,
	TMap<FIntPoint, FVector2D>& InitialKets,
	TMap<int32, float>& MaxSizeOutput,
	TMap<int32, float>& MaxSizeKetOutput,
	TMap<int32, float>& MaxSizeTransitionOutput) {
	MaxSizeOutput.Empty();
	MaxSizeKetOutput.Empty();
	TArray<int32> LocalArrayKets;
	LocalArrayKets.Empty();
	for (auto& iter : InitialKets) {
		if (!LocalArrayKets.Contains(iter.Key.X)) {
			LocalArrayKets.Add(iter.Key.X);
		}
	}
	for (auto& iter : LocalArrayKets) {
		MaxSizeKetOutput.Add(iter, 0.0);
	}
	for (auto& iter : InitialKets) {
		float TempFloatKet = FMath::Max(InitialKets[iter.Key].Size(), MaxSizeKetOutput[iter.Key.X]);
		MaxSizeKetOutput.Add(iter.Key.X, TempFloatKet);

	}
	MaxSizeTransitionOutput.Empty();
	TArray<int32> LocalArrayTransitions;
	LocalArrayTransitions.Empty();
	for (auto& iter : TransitionMatrices) {
		if (!LocalArrayTransitions.Contains(iter.Key.X)) {
			LocalArrayTransitions.Add(iter.Key.X);

		}
	}
	for (auto& iter : LocalArrayTransitions) {
		MaxSizeTransitionOutput.Add(iter, 0.0);
	}
	for (auto& iter : TransitionMatrices) {
		float TempFloatMatrix = FMath::Max(TransitionMatrices[iter.Key].Size(), MaxSizeTransitionOutput[iter.Key.X]);
		MaxSizeTransitionOutput.Add(iter.Key.X, TempFloatMatrix);
	}
}
void UQuantumLandBlueprintFxnLibrary::CombineIntPointMapToIntVectorMapComplexValues(
	TMap<FIntVector, FVector2D>& RefTargetMap,
	TMap<FIntPoint, FVector2D>& InputAppendMap,
	int32 InputFirstCoord,
	TMap<FIntVector, FVector2D>& CoordinateCollisions) {
	CoordinateCollisions.Empty();
	for (auto& iter : InputAppendMap) {
		FIntVector NewKey = FIntVector(InputFirstCoord, iter.Key.X, iter.Key.Y);
		if (RefTargetMap.Contains(NewKey)) {
			CoordinateCollisions.Add(NewKey, iter.Value);
		}
		else {
			RefTargetMap.Add(NewKey, iter.Value);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::CombineIntMapToIntPointMapComplexValues(
	TMap<FIntPoint, FVector2D>& RefTargetMap,
	TMap<int32, FVector2D>& InputAppendMap,
	int32 InputFirstCoord,
	TMap<FIntPoint, FVector2D>& CoordinateCollisions) {
	CoordinateCollisions.Empty();
	for (auto& iter : InputAppendMap) {
		FIntPoint NewKey = FIntPoint(InputFirstCoord, iter.Key);
		if (RefTargetMap.Contains(NewKey)) {
			CoordinateCollisions.Add(NewKey, iter.Value);
		}
		else {
			RefTargetMap.Add(NewKey, iter.Value);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::GetAllTransitionOperationKet(
	TArray<FQuantumGateSpecifier>& GateArray,
	TMap<int32, FVector2D>& StartingKet,
	TMap<FIntVector, FVector2D>& OperationsMatrices,
	TMap<FIntVector, FVector2D>& TransitionsMatrices,
	TMap<FIntPoint, FVector2D>& InitialKets) {
	OperationsMatrices.Empty();
	TransitionsMatrices.Empty();
	InitialKets.Empty();
	TMap<int32, FVector2D> PlaceHolderIntMap;
	TMap<FIntPoint, FVector2D> PlaceHolderIntPointMap;
	TMap<FIntVector, FVector2D> PlaceHolderIntVectorMap;
	TMap<int32, FVector2D> TempKet;
	TMap<int32, FVector2D> CurrentKet = StartingKet;
	TMap<FIntPoint, FVector2D> TempOperatorMatrix;
	TMap<FIntPoint, FVector2D> TempTransitionMatrix;
	CombineIntMapToIntPointMapComplexValues(InitialKets, CurrentKet, 0, PlaceHolderIntPointMap);
	//check(PlaceHolderIntPointMap.Num() == 0);
	for (int OperationIndex = 0; OperationIndex < GateArray.Num(); OperationIndex++) {
		InitializeQuantumOperatorWithSpecifier(
			GateArray[OperationIndex], 
			TempOperatorMatrix);
		int32 test = TempOperatorMatrix.Num();
		MultiplyOperatorWithKetToOperatorKet(
			TempOperatorMatrix, 
			CurrentKet, 
			TempTransitionMatrix, 
			TempKet);
		CombineIntMapToIntPointMapComplexValues(
			InitialKets, 
			TempKet, 
			OperationIndex + 1, 
			PlaceHolderIntPointMap);
		//check(PlaceHolderIntPointMap.Num() == 0);
		CombineIntPointMapToIntVectorMapComplexValues(
			OperationsMatrices, 
			TempOperatorMatrix, 
			OperationIndex, 
			PlaceHolderIntVectorMap);
		//check(PlaceHolderIntVectorMap.Num() == 0);
		CombineIntPointMapToIntVectorMapComplexValues(
			TransitionsMatrices, 
			TempTransitionMatrix, 
			OperationIndex, 
			PlaceHolderIntVectorMap);
		//check(PlaceHolderIntVectorMap.Num() == 0);
		CurrentKet = TempKet;
	}
}
void UQuantumLandBlueprintFxnLibrary::GetAllTransitionOperationKetFlagged(
	TArray<FQuantumGateSpecifier>& GateArray,
	TMap<int32, FVector2D>& StartingKet,
	int32 InputQubitCount,
	TMap<FIntVector, FVector2D>& OperationsMatrices,
	TMap<FIntVector, FVector2D>& TransitionsMatrices,
	TMap<FIntPoint, FVector2D>& InitialKets,
	bool& SuccessFlag) {
	OperationsMatrices.Empty();
	TransitionsMatrices.Empty();
	InitialKets.Empty();
	TMap<int32, FVector2D> PlaceHolderIntMap;
	TMap<FIntPoint, FVector2D> PlaceHolderIntPointMap;
	TMap<FIntVector, FVector2D> PlaceHolderIntVectorMap;
	TMap<int32, FVector2D> TempKet;
	TMap<int32, FVector2D> CurrentKet = StartingKet;
	TMap<FIntPoint, FVector2D> TempOperatorMatrix;
	TMap<FIntPoint, FVector2D> TempTransitionMatrix;
	CombineIntMapToIntPointMapComplexValues(InitialKets, CurrentKet, 0, PlaceHolderIntPointMap);
	//check(PlaceHolderIntPointMap.Num() == 0);
	for (int OperationIndex = 0; OperationIndex < GateArray.Num(); OperationIndex++) {
		InitializeQuantumOperatorWithSpecifier(
			GateArray[OperationIndex],
			TempOperatorMatrix);
		int32 test = TempOperatorMatrix.Num();
		MultiplyOperatorWithKetToOperatorKet(
			TempOperatorMatrix,
			CurrentKet,
			TempTransitionMatrix,
			TempKet);
		CombineIntMapToIntPointMapComplexValues(
			InitialKets,
			TempKet,
			OperationIndex + 1,
			PlaceHolderIntPointMap);
		//check(PlaceHolderIntPointMap.Num() == 0);
		CombineIntPointMapToIntVectorMapComplexValues(
			OperationsMatrices,
			TempOperatorMatrix,
			OperationIndex,
			PlaceHolderIntVectorMap);
		//check(PlaceHolderIntVectorMap.Num() == 0);
		CombineIntPointMapToIntVectorMapComplexValues(
			TransitionsMatrices,
			TempTransitionMatrix,
			OperationIndex,
			PlaceHolderIntVectorMap);
		//check(PlaceHolderIntVectorMap.Num() == 0);
		CurrentKet = TempKet;
	}
	SuccessFlag = true;
}
void UQuantumLandBlueprintFxnLibrary::GetTransitionPhaseBlocksTransformArray(
	float TargetSizeSubBlocks,
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float AngleStartDegrees,
	float AngleEndDegrees,
	float SpokeProportionStart,
	float SpokeProportionEnd,
	FVector StartPosition,
	FVector EndPosition,
	FVector DimensionsOfStaticRectangularMesh,
	FVector TowardsZeroDegreesNormalizedDirection,
	FVector FlattenedOriginPosition,
	int32 SubBlockHighlightMultiplier,
	TArray<FTransform>& TransformBlockArray,
	TArray<int32>& SubBlockHighlightOffsets) {
	//TArray<FTransform>& TransformBlockArrayFlattened
	// additional steps for fixing towards viewer implementation
	FVector AxisOfRotationForPhase = 
		UKismetMathLibrary::Cross_VectorVector(TowardsZeroDegreesNormalizedDirection, FVector(0.0, 0.0, 1.0));
	// back to existing code
	FVector FromToVector = EndPosition - StartPosition;
	float WaveDistance = FromToVector.Size();
	int32 TargetNumberOfBlocks = FMath::CeilToInt(WaveDistance / TargetSizeSubBlocks);
	int32 NumberOfDivisions = FMath::CeilToInt(TargetNumberOfBlocks / SubBlockHighlightMultiplier);
	int32 NumberOfBlocks = NumberOfDivisions * SubBlockHighlightMultiplier;
	float BlockLength = WaveDistance / NumberOfBlocks;
	for (int32 Index = 0; Index <= NumberOfBlocks; Index++) {
		if (Index % SubBlockHighlightMultiplier == 0) {
			SubBlockHighlightOffsets.Add(Index);
		}
		float ProportionCompletedAngle = (1.0 * Index) / (1.0 * NumberOfBlocks);
		float DistancePortionStart = Index / (NumberOfBlocks + 1.0);
		float DistancePortionEnd = (Index + 1.0) / (NumberOfBlocks + 1.0);
		float DistancePortionSet = (Index + 0.5) / (NumberOfBlocks + 1.0);
		//float DistancePortionCenter = (DistancePortionStart + DistancePortionEnd) / 2.0;
		FVector PositionOfSpokeStart =
			FromToVector * DistancePortionSet + StartPosition;
		float CurrentAngle =
			(AngleEndDegrees - AngleStartDegrees) * ProportionCompletedAngle + AngleStartDegrees;
		float RadiusOfSpokeSpin = BaseRadius * TransitionRadiusFraction;
		FVector PositionOfSpokeEndAtZeroDegrees = FVector(0.0, RadiusOfSpokeSpin, 0.0);
		FVector PositionOfSpokeEnd = PositionOfSpokeStart +
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(1.0, 0.0, 0.0));
		FVector ParamaterizedPositionOfSpokeStart = PositionOfSpokeStart +
			SpokeProportionStart * UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(1.0, 0.0, 0.0));
		FVector ParamaterizedPositionOfSpokeEnd = PositionOfSpokeStart +
			SpokeProportionEnd * UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(1.0, 0.0, 0.0));

		FVector DimensionsVector = FVector(BlockLength, WidthSubBlocks, RadiusOfSpokeSpin);
		FTransform LocalTransform;
		GetRectangularTransformPointToPointFromZ(
			ParamaterizedPositionOfSpokeStart,
			ParamaterizedPositionOfSpokeEnd,
			DimensionsOfStaticRectangularMesh,
			BlockLength,
			WidthSubBlocks,
			TowardsZeroDegreesNormalizedDirection,
			LocalTransform);
		TransformBlockArray.Add(LocalTransform);
		//FVector RelativePositionOfSpokeEndFlattenedAtZeroDegrees =
		//	UKismetMathLibrary::RotateAngleAxis(
		//		PositionOfSpokeEnd, 90, FVector(0.0, 0.0, 1.0));
		//FVector IntermediatePositionOfFlattenedSpokeEnd =
		//	UKismetMathLibrary::RotateAngleAxis(
		//		PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(-1.0, 0.0, 0.0));
		FVector IntermediatePositionOfFlattenedSpokeEnd =
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, AxisOfRotationForPhase);

	}
}
void UQuantumLandBlueprintFxnLibrary::GetTransitionFlattenedTransformArray(
	int32 NumberOfBlocks,
	float LengthSizeSubBlocks,
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float AngleStartDegrees,
	float AngleEndDegrees,
	FVector FlattenedOriginPosition,
	FVector DimensionsOfStaticRectangularMesh,
	FVector DirectionOfZeroDegrees,
	FVector AxisOfRotation,
	TArray<FTransform>& TransformBlockArrayFlattened){
	for (int32 Index = 0; Index <= NumberOfBlocks; Index++) {
		float ProportionCompletedAngle = (1.0 * Index) / (1.0 * NumberOfBlocks);
		float CurrentAngle =
			(AngleEndDegrees - AngleStartDegrees) * ProportionCompletedAngle + AngleStartDegrees;
		float RadiusOfSpokeSpin = BaseRadius * TransitionRadiusFraction;
		FVector PositionOfSpokeEndAtZeroDegrees = RadiusOfSpokeSpin * DirectionOfZeroDegrees;
		//FVector PositionOfSpokeEnd = PositionOfSpokeStart +
		//	UKismetMathLibrary::RotateAngleAxis(
		//		PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(-1.0, 0.0, 0.0));
		//FVector RelativePositionOfSpokeEndFlattenedAtZeroDegrees =
		//	UKismetMathLibrary::RotateAngleAxis(
		//		PositionOfSpokeEnd, 90, FVector(0.0, 0.0, 1.0));
		FVector PositionOfFlattenedSpokeEnd = FlattenedOriginPosition + 
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, AxisOfRotation);
		FTransform LocalTransformFlattened;
		GetRectangularTransformPointToPointFromZ(
			FlattenedOriginPosition,
			PositionOfFlattenedSpokeEnd,
			DimensionsOfStaticRectangularMesh,
			LengthSizeSubBlocks,
			WidthSubBlocks,
			DirectionOfZeroDegrees,
			LocalTransformFlattened);
		TransformBlockArrayFlattened.Add(LocalTransformFlattened);
	}
}
void UQuantumLandBlueprintFxnLibrary::GetTransitionPhaseBlocksFromStartRadiusTransformArray(
	float TargetSizeSubBlocks,
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float RadiusFinalFractionStart,
	float AngleStartDegrees,
	float AngleEndDegrees,
	FVector StartPosition,
	FVector EndPosition,
	FVector DimensionsOfStaticRectangularMesh,
	FVector TowardsViewerNormalizedDirection,
	int32 SubBlockHighlightMultiplier,
	TArray<FTransform>& TransformBlockArray,
	TArray<int32>& SubBlockHighlightOffsets) {
	FVector FromToVector = EndPosition - StartPosition;
	float WaveDistance = FromToVector.Size();
	int32 TargetNumberOfBlocks = FMath::CeilToInt(WaveDistance / TargetSizeSubBlocks);
	int32 NumberOfDivisions = FMath::CeilToInt(TargetNumberOfBlocks / SubBlockHighlightMultiplier);
	int32 NumberOfBlocks = NumberOfDivisions * SubBlockHighlightMultiplier;
	float BlockLength = WaveDistance / NumberOfBlocks;
	for (int32 Index = 0; Index <= NumberOfBlocks; Index++) {
		if (Index % SubBlockHighlightMultiplier == 0) {
			SubBlockHighlightOffsets.Add(Index);
		}
		float ProportionCompletedAngle = (1.0 * Index) / (1.0 * NumberOfBlocks);
		float DistancePortionStart = Index / (NumberOfBlocks + 1.0);
		float DistancePortionEnd = (Index + 1.0) / (NumberOfBlocks + 1.0);
		float DistancePortionSet = (Index + 0.5) / (NumberOfBlocks + 1.0);
		FVector PositionOfSpokeStart =
			FromToVector * DistancePortionSet + StartPosition;
		float CurrentAngle =
			(AngleEndDegrees - AngleStartDegrees) * ProportionCompletedAngle + AngleStartDegrees;
		float RadiusOfSpokeSpin = BaseRadius * TransitionRadiusFraction;
		FVector PositionOfSpokeStartModifiedAtZeroDegrees =
			FVector(0.0, RadiusOfSpokeSpin * RadiusFinalFractionStart, 0.0);
		FVector PositionOfSpokeStartModified = PositionOfSpokeStart +
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeStartModifiedAtZeroDegrees, CurrentAngle, FVector(1.0, 0.0, 0.0));
		FVector PositionOfSpokeEndAtZeroDegrees = FVector(0.0, RadiusOfSpokeSpin, 0.0);
		FVector PositionOfSpokeEnd = PositionOfSpokeStart +
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(1.0, 0.0, 0.0));
		FTransform LocalTransform;
		GetRectangularTransformPointToPointFromZ(
			PositionOfSpokeStartModified,
			PositionOfSpokeEnd,
			DimensionsOfStaticRectangularMesh,
			BlockLength,
			WidthSubBlocks,
			FVector(0.0, 1.0, 0.0),
			LocalTransform);
		TransformBlockArray.Add(LocalTransform);
	}
}
void UQuantumLandBlueprintFxnLibrary::GetRectangularTransformPointToPointFromZ(
	FVector StartPosition,
	FVector EndPosition,
	FVector DimensionsOfStaticRectangularMesh,
	float ThicknessX,
	float ThicknessY,
	FVector DirectionTowardsAxisY,
	FTransform& TransformOfRectangle) {
	FVector DimensionsVector = FVector(ThicknessX, ThicknessY, (EndPosition - StartPosition).Size());
	FVector ScaleVector = DimensionsVector / DimensionsOfStaticRectangularMesh;
	FVector FinalPosition = (StartPosition + EndPosition) / 2.0;
	FVector DirectionTravel = (EndPosition - StartPosition).GetSafeNormal();
	FRotator FinalRotator = UKismetMathLibrary::MakeRotFromZY(DirectionTravel, DirectionTowardsAxisY);
	TransformOfRectangle = FTransform(FinalRotator, FinalPosition, ScaleVector);
}
void UQuantumLandBlueprintFxnLibrary::GetCylindricalTransformPointToPointFromZ(
	FVector StartPosition,
	FVector EndPosition,
	FVector DimensionsOfStaticCylindricalMesh,
	float InputRadius,
	FVector DirectionTowardsAxisY,
	FTransform& TransformOfCylinder) {
	FVector DimensionsVector = FVector(2*InputRadius, 2*InputRadius, (EndPosition - StartPosition).Size());
	FVector ScaleVector = DimensionsVector / DimensionsOfStaticCylindricalMesh;
	FVector FinalPosition = (StartPosition + EndPosition) / 2.0;// -ScaledOffset;
	FVector DirectionTravel = (EndPosition - StartPosition).GetSafeNormal();
	FRotator FinalRotator = UKismetMathLibrary::MakeRotFromZY(DirectionTravel, DirectionTowardsAxisY);
	TransformOfCylinder = FTransform(FinalRotator, FinalPosition, ScaleVector);
}
void UQuantumLandBlueprintFxnLibrary::GetFlattenedTransformArrayPlaneZY(
	int32 NumberOfBlocks,
	float LengthSizeSubBlocks,
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float AngleStartDegrees,
	float AngleEndDegrees,
	FVector FlattenedOriginPosition,
	FVector DimensionsOfStaticRectangularMesh,
	//FVector DirectionOfZeroDegrees,
	//FVector AxisOfRotation,
	TArray<FTransform>& TransformBlockArrayFlattened) {
	for (int32 Index = 0; Index <= NumberOfBlocks; Index++) {
		float ProportionCompletedAngle = (1.0 * Index) / (1.0 * NumberOfBlocks);
		float CurrentAngle =
			(AngleEndDegrees - AngleStartDegrees) * ProportionCompletedAngle + AngleStartDegrees;
		float RadiusOfSpokeSpin = BaseRadius * TransitionRadiusFraction;
		FVector PositionOfSpokeEndAtZeroDegrees = RadiusOfSpokeSpin * FVector(1.0, 0.0, 0.0);
		//FVector PositionOfSpokeEnd = PositionOfSpokeStart +
		//	UKismetMathLibrary::RotateAngleAxis(
		//		PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(-1.0, 0.0, 0.0));
		//FVector RelativePositionOfSpokeEndFlattenedAtZeroDegrees =
		//	UKismetMathLibrary::RotateAngleAxis(
		//		PositionOfSpokeEnd, 90, FVector(0.0, 0.0, 1.0));
		FVector PositionOfFlattenedSpokeEnd = FlattenedOriginPosition +
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(0.0, 1.0, 0.0));
		FVector DimensionsVector = FVector(WidthSubBlocks, LengthSizeSubBlocks, (PositionOfFlattenedSpokeEnd - FlattenedOriginPosition).Size());
		FVector ScaleVector = DimensionsVector / DimensionsOfStaticRectangularMesh;
		FVector FinalPosition = (FlattenedOriginPosition + PositionOfFlattenedSpokeEnd) / 2.0;// -ScaledOffset;
		FVector DirectionTravel = (PositionOfFlattenedSpokeEnd - FlattenedOriginPosition);
		FRotator FinalRotator = UKismetMathLibrary::MakeRotFromZY(DirectionTravel, FVector(0.0, 1.0, 0.0));
		FTransform LocalTransformFlattened = FTransform(FinalRotator, FinalPosition, ScaleVector);

		TransformBlockArrayFlattened.Add(LocalTransformFlattened);
	}
}
void UQuantumLandBlueprintFxnLibrary::GetFlattenedFromStartRadiusTransformArrayPlaneZY(
	int32 NumberOfBlocks,
	float LengthSizeSubBlocks,
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float AngleStartDegrees,
	float AngleEndDegrees,
	float SpokeProportionStart,
	float SpokeProportionEnd,
	FVector FlattenedOriginPosition,
	FVector DimensionsOfStaticRectangularMesh,
	TArray<FTransform>& TransformBlockArrayFlattened) {
	for (int32 Index = 0; Index <= NumberOfBlocks; Index++) {
		float ProportionCompletedAngle = (1.0 * Index) / (1.0 * NumberOfBlocks);
		float CurrentAngle =
			(AngleEndDegrees - AngleStartDegrees) * ProportionCompletedAngle + AngleStartDegrees;
		float RadiusOfSpokeSpin = BaseRadius * TransitionRadiusFraction;
		FVector PositionOfSpokeEndAtZeroDegrees = RadiusOfSpokeSpin * FVector(1.0, 0.0, 0.0);
		FVector PositionOfFlattenedSpokeEnd = FlattenedOriginPosition +
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(0.0, -1.0, 0.0));
		FVector FromStartPositionInputProportion = FlattenedOriginPosition +
			SpokeProportionStart * UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(0.0, -1.0, 0.0));
		FVector FromStopPositionInputProportion = FlattenedOriginPosition +
			SpokeProportionEnd * UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, FVector(0.0, -1.0, 0.0));
		FVector DimensionsVector = FVector(WidthSubBlocks, LengthSizeSubBlocks, (FromStopPositionInputProportion - FromStartPositionInputProportion).Size());
		FVector ScaleVector = DimensionsVector / DimensionsOfStaticRectangularMesh;
		FVector FinalPosition = (FromStartPositionInputProportion + FromStopPositionInputProportion) / 2.0;// -ScaledOffset;
		FVector DirectionTravel = (FromStopPositionInputProportion - FromStartPositionInputProportion);
		FRotator FinalRotator = UKismetMathLibrary::MakeRotFromZY(DirectionTravel, FVector(0.0, 1.0, 0.0));
		FTransform LocalTransformFlattened = FTransform(FinalRotator, FinalPosition, ScaleVector);

		TransformBlockArrayFlattened.Add(LocalTransformFlattened);
	}
}
void UQuantumLandBlueprintFxnLibrary::GetPathOfIntVectorMapToVector2D(
	TMap<FIntVector, FVector2D>& NormalizedTransitionToKetMap,
	bool StackingPositionsFlag,
	TMap<FIntVector, FVector2D>& OutputStartPoints,
	TMap<FIntVector, FVector2D>& OutputStopPoints) {
	OutputStartPoints.Empty();
	OutputStopPoints.Empty();
	if (StackingPositionsFlag) {
		FVector2D LocalRunningSum = FVector2D(0.0, 0.0);
		for (auto& iter : NormalizedTransitionToKetMap) {
			OutputStartPoints.Add(iter.Key, FVector2D(LocalRunningSum.X, LocalRunningSum.Y));
			LocalRunningSum += iter.Value;
			OutputStopPoints.Add(iter.Key, FVector2D(LocalRunningSum.X, LocalRunningSum.Y));
		}
	}
	else {
		for (auto& iter : NormalizedTransitionToKetMap) {
			OutputStartPoints.Add(iter.Key, FVector2D(0.0, 0.0));
			OutputStopPoints.Add(iter.Key, iter.Value);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::GetPathOfIntPointMapToVector2D(
	TMap<FIntPoint, FVector2D>& NormalizedKetToKetMap,
	bool StackingPositionsFlag,
	TMap<FIntPoint, FVector2D>& OutputStartPoints,
	TMap<FIntPoint, FVector2D>& OutputStopPoints) {
	FVector2D LocalRunningSum = FVector2D(0.0, 0.0);
	for (auto& iter : NormalizedKetToKetMap) {
		if (StackingPositionsFlag) {
			OutputStartPoints.Add(iter.Key, FVector2D(LocalRunningSum.X, LocalRunningSum.Y));
			LocalRunningSum += iter.Value;
			OutputStopPoints.Add(iter.Key, FVector2D(LocalRunningSum.X, LocalRunningSum.Y));
		}
		else {
			OutputStartPoints.Add(iter.Key, FVector2D(0.0, 0.0));
			OutputStopPoints.Add(iter.Key, iter.Value);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::GetMagnitudePositivePhaseInDegrees(
	FVector2D InputVector2D,
	float& OutputMagnitude,
	float& OutputPhase) {
	float TempValue = UKismetMathLibrary::DegAtan2(InputVector2D.Y, InputVector2D.X);
	if (TempValue > 0.0) {
		OutputPhase = TempValue;
	}
	else {
		TempValue = 360.0 + TempValue;
	}
	OutputMagnitude = InputVector2D.Size();
}
void UQuantumLandBlueprintFxnLibrary::GetCubeTransformToDialFacingY(
	FVector StartLocation,
	float DepthBounds,
	float Thickness,
	float Magnitude,
	float AngleFromPlusX,
	FVector SizeOfSM,
	FTransform& TransformOfCube) {
	FVector StopLocation = StartLocation +
		FVector(Magnitude * FMath::Cos(AngleFromPlusX), 0.0, Magnitude * FMath::Sin(AngleFromPlusX));
	FVector LocationOfCube = (StartLocation + StopLocation) / 2.0;
	FVector RawSize = FVector(Magnitude, Thickness, DepthBounds);
	FVector ScaleOfCube = RawSize / SizeOfSM;
	FRotator RotatorOfCube = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector(0.0, 1.0, 0.0), AngleFromPlusX);
	TransformOfCube = FTransform(RotatorOfCube, LocationOfCube, ScaleOfCube);
}
void UQuantumLandBlueprintFxnLibrary::GetMaxMagFromIntVectorMapToVector2D(
	TMap<FIntVector, FVector2D>& InputMap,
	float& MaxMagnitude) {
	MaxMagnitude = 0.0;
	for (auto& iter : InputMap) {
		MaxMagnitude = FMath::Max(MaxMagnitude, iter.Value.Size());
	}
}
void UQuantumLandBlueprintFxnLibrary::GetMaxMagFromIntPointMapToVector2D(
	TMap<FIntPoint, FVector2D>& InputMap,
	float& MaxMagnitude) {
	MaxMagnitude = 0.0;
	for (auto& iter : InputMap) {
		MaxMagnitude = FMath::Max(MaxMagnitude, iter.Value.Size());
	}
}
void UQuantumLandBlueprintFxnLibrary::GetNormalizedIntVectorMapToVector2D(
	TMap<FIntVector, FVector2D>& InputMap,
	TMap<FIntVector, FVector2D>& OutputMap) {
	float LocalMaxMagnitude;
	GetMaxMagFromIntVectorMapToVector2D(InputMap, LocalMaxMagnitude);
	OutputMap.Empty();
	GetNormalizedToValueIntVectorMapToVector2D(LocalMaxMagnitude, InputMap, OutputMap);
}
void UQuantumLandBlueprintFxnLibrary::GetMasterNormalizeIndexMaps(
	TMap<FIntVector, FVector2D>& InputIntVectorMap,
	TMap<FIntPoint, FVector2D>& InputIntPointMap,
	bool& PositiveValueFlag,
	float& OutputMaxValue) {
	OutputMaxValue = 0.0;
	if (InputIntVectorMap.Num() == 0) {
		GetMaxMagFromIntPointMapToVector2D(InputIntPointMap, OutputMaxValue);
	}
	else if (InputIntVectorMap.Num()!=0 && InputIntPointMap.Num()!=0) {
		TMap<FIntPoint, float> MaxValues;
		TMap<FIntPoint, FVector2D> RunningSum;
		TMap<FIntPoint, bool> WhetherToSum;
		for (auto& iter : InputIntVectorMap) {
			FIntPoint LocalTargetIntPoint = FIntPoint(iter.Key.X + 1, iter.Key.Z);
			if (InputIntPointMap.Contains(LocalTargetIntPoint)) {
				WhetherToSum.Add(LocalTargetIntPoint, true);
				MaxValues.Add(LocalTargetIntPoint, InputIntPointMap[LocalTargetIntPoint].Size());
				RunningSum.Add(LocalTargetIntPoint, FVector2D(0.0, 0.0));
			}
			else {
				if (!WhetherToSum.Contains(LocalTargetIntPoint)) {
					WhetherToSum.Add(LocalTargetIntPoint, false);
				}
			}
		}
		for (auto& iter : InputIntVectorMap) {
			FIntPoint LocalTargetIntPoint = FIntPoint(iter.Key.X + 1, iter.Key.Z);
			if (WhetherToSum.Contains(LocalTargetIntPoint)) {
				if (WhetherToSum[LocalTargetIntPoint]) {
					FVector2D NewSum = RunningSum[LocalTargetIntPoint] + iter.Value;
					RunningSum.Add(LocalTargetIntPoint, NewSum);
					if (MaxValues[LocalTargetIntPoint] < NewSum.Size()) {
						MaxValues.Add(LocalTargetIntPoint, NewSum.Size());
					}
				}
			}
			if (MaxValues.Contains(LocalTargetIntPoint)) {
				if (MaxValues[LocalTargetIntPoint] < iter.Value.Size()) {
					MaxValues.Add(LocalTargetIntPoint, iter.Value.Size());
				}
			}
		}
		OutputMaxValue = 0.0;
		for (auto& iter : MaxValues) {
			if (OutputMaxValue < iter.Value) {
				OutputMaxValue = 
					iter.Value;
			}
		}
	}
	if (OutputMaxValue > 0.0) {
		PositiveValueFlag = true;
	}
	else {
		PositiveValueFlag = false;
	}
}
void UQuantumLandBlueprintFxnLibrary::GetNormalizedToKetsTransitions(
	bool LockNormalization,
	bool NormalizeIntVector,
	bool NormalizeIntPoint,
	TMap<FIntVector, FVector2D>& InputIntVectorMap,
	TMap<FIntPoint, FVector2D>& InputIntPointMap,
	TMap<FIntVector, FVector2D>& OutputIntVectorMap,
	TMap<FIntPoint, FVector2D>& OutputIntPointMap) {
	float LocalMaxMagnitudeIntVector = 1.0;
	float LocalMaxMagnitudeIntPoint = 1.0;
	float LocalMaxMagnitudeLocked = 1.0;
	OutputIntVectorMap.Empty();
	OutputIntPointMap.Empty();
	if (!LockNormalization) {
		if (NormalizeIntVector) {
			GetMaxMagFromIntVectorMapToVector2D(InputIntVectorMap, LocalMaxMagnitudeIntVector);
			GetNormalizedToValueIntVectorMapToVector2D(LocalMaxMagnitudeIntVector, InputIntVectorMap, OutputIntVectorMap);
		}
		else {
			GetNormalizedToValueIntVectorMapToVector2D(LocalMaxMagnitudeIntVector, InputIntVectorMap, OutputIntVectorMap);
		}
		if (NormalizeIntPoint) {
			GetMaxMagFromIntPointMapToVector2D(InputIntPointMap, LocalMaxMagnitudeIntPoint);
			GetNormalizedToValueIntPointMapToVector2D(LocalMaxMagnitudeIntPoint, InputIntPointMap, OutputIntPointMap);
		}
		else {
			GetNormalizedToValueIntPointMapToVector2D(LocalMaxMagnitudeIntPoint, InputIntPointMap, OutputIntPointMap);
		}
	}
	else {
		GetMaxMagFromIntVectorMapToVector2D(InputIntVectorMap, LocalMaxMagnitudeIntVector);
		GetMaxMagFromIntPointMapToVector2D(InputIntPointMap, LocalMaxMagnitudeIntPoint);
		LocalMaxMagnitudeLocked = FMath::Max(LocalMaxMagnitudeIntVector, LocalMaxMagnitudeIntPoint);
		GetNormalizedToValueIntVectorMapToVector2D(LocalMaxMagnitudeLocked, InputIntVectorMap, OutputIntVectorMap);
		GetNormalizedToValueIntPointMapToVector2D(LocalMaxMagnitudeLocked, InputIntPointMap, OutputIntPointMap);
	}
}
void UQuantumLandBlueprintFxnLibrary::GetNormalizedSingleKetToTransitions(
	bool NormalizePathFlag,
	TMap<FIntVector, FVector2D>& InputIntVectorMap,
	TMap<FIntVector, FVector2D>& OutputIntVectorMap) {
	float LocalMaxMagnitude = 0.0;
	FVector2D CurrentValue = FVector2D(0.0, 0.0);
	float MaxSingleValue = 0.0;
	float MaxSumInOrderValue = 0.0;
	if (NormalizePathFlag) {
		for (auto& iter : InputIntVectorMap) {
			CurrentValue += iter.Value;
			if (MaxSingleValue < iter.Value.Size()) {
				MaxSingleValue = iter.Value.Size();
			}
			if (MaxSumInOrderValue < CurrentValue.Size()) {
				MaxSumInOrderValue = CurrentValue.Size();
			}
		}
		LocalMaxMagnitude = FMath::Max(MaxSingleValue, MaxSumInOrderValue);
		GetNormalizedToValueIntVectorMapToVector2D(LocalMaxMagnitude, InputIntVectorMap, OutputIntVectorMap);
	}
	else {
		for (auto& iter : InputIntVectorMap) {
			if (LocalMaxMagnitude < iter.Value.Size()) {
				LocalMaxMagnitude = iter.Value.Size();
			}
		}
		GetNormalizedToValueIntVectorMapToVector2D(LocalMaxMagnitude, InputIntVectorMap, OutputIntVectorMap);
	}
}
void UQuantumLandBlueprintFxnLibrary::GetNormalizedIntPointMapToVector2D(
	TMap<FIntPoint, FVector2D>& InputMap,
	TMap<FIntPoint, FVector2D>& OutputMap) {
	float LocalMaxMagnitude;
	GetMaxMagFromIntPointMapToVector2D(InputMap, LocalMaxMagnitude);
	OutputMap.Empty();
	GetNormalizedToValueIntPointMapToVector2D(LocalMaxMagnitude, InputMap, OutputMap);
}
void UQuantumLandBlueprintFxnLibrary::GetNormalizedToValueIntVectorMapToVector2D(
	float InputMax,
	TMap<FIntVector, FVector2D>& InputMap,
	TMap<FIntVector, FVector2D>& OutputMap) {
	OutputMap.Empty();
	if (InputMax > 0.0) {
		for (auto& iter : InputMap) {
			OutputMap.Add(iter.Key, iter.Value / InputMax);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::GetNormalizedToValueIntPointMapToVector2D(
	float InputMax,
	TMap<FIntPoint, FVector2D>& InputMap,
	TMap<FIntPoint, FVector2D>& OutputMap) {
	OutputMap.Empty();
	if (InputMax > 0.0) {
		for (auto& iter : InputMap) {
			OutputMap.Add(iter.Key, iter.Value / InputMax);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::GetSubsetMapIntVector(
	TMap<FIntVector, FVector2D>& InputMap,
	TArray<FIntVector>& InputArray,
	TMap<FIntVector, FVector2D>& OutputMap,
	TArray<FIntVector>& RejectedArray) {
	OutputMap.Empty();
	RejectedArray.Empty();
	for (auto& iter : InputArray) {
		if (InputMap.Contains(iter)) {
			OutputMap.Add(iter, InputMap[iter]);
		}
		else {
			RejectedArray.Add(iter);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::GetSubsetMapIntPoint(
	TMap<FIntPoint, FVector2D>& InputMap,
	TArray<FIntPoint>& InputArray,
	TMap<FIntPoint, FVector2D>& OutputMap,
	TArray<FIntPoint>& RejectedArray) {
	for (auto& iter : InputArray) {
		if (InputMap.Contains(iter)) {
			OutputMap.Add(iter, InputMap[iter]);
		}
		else {
			RejectedArray.Add(iter);
		}
	}

}
void UQuantumLandBlueprintFxnLibrary::GetRunningSumValues(
	TMap<FIntVector, FVector2D>& InputMap,
	bool& SuccessFlag,
	TMap<FIntVector, FTwoVectors>& OutputMap) {
	OutputMap.Empty();
	TMap<int32, FVector> LocalMap;
	TArray<FIntVector> LocalArray;
	int32 ReturnValueLocal = InputMap.GetKeys(LocalArray);
	if (LocalArray.Num() != 0) {
		bool IdenticalOpKetToFlag = true;
		FIntPoint LocalFixedKetStateTo = FIntPoint(LocalArray[0].X, LocalArray[0].Y);
		for (auto& iter : InputMap) {
			if (LocalFixedKetStateTo.X == iter.Key.X || LocalFixedKetStateTo.Y == iter.Key.Y) {
				LocalMap.Add(iter.Key.Z,FVector(iter.Value.X,iter.Value.Y,0.0));
			}
			else IdenticalOpKetToFlag = false;
		}
		if (IdenticalOpKetToFlag) {
			TArray<int32> LocalIntArray;
			LocalMap.GetKeys(LocalIntArray);
			LocalIntArray.Sort();
			FVector RunningSum = FVector(0.0, 0.0, 0.0);
			FVector PreviousSum = RunningSum;
			for (auto& iter : LocalIntArray) {
				PreviousSum = RunningSum;
				RunningSum = PreviousSum + LocalMap[iter];
				OutputMap.Add(
					FIntVector(LocalFixedKetStateTo.X, LocalFixedKetStateTo.Y, iter),
					FTwoVectors(PreviousSum, RunningSum));
			}
			SuccessFlag = true;
		}
		else SuccessFlag = false;
	}
	else SuccessFlag = false;
}

//void CreateStaticMesh() {
//
//	int32 RadialN;
//	int32 AxialN;
//	float Radius;
//	float AxialSpacing;
//	TMap<int32, FTwoVectors> AxialNormalPair;
//	TMap<FIntPoint, int32> VertexMapCoords;
//	TMap<FIntPoint, FVector> VertexMapLocation;
//	for (int32 AxialIndex = 1; AxialIndex < RadialN; AxialIndex++) {
//		for (int32 RadialIndex = 0; RadialIndex < RadialN; RadialIndex++) {
//
//		}
//	}
//	TMap<FIntVector, int32> FaceMap;
//	for (int32 AxialIndex = 1;  AxialIndex < RadialN; AxialIndex++) {
//		for (int32 RadialIndex = 0; RadialIndex < RadialN; RadialIndex++) {
//			FaceMap.Add(FIntVector(
//				VertexMap.Find(FIntPoint(AxialIndex - 1, RadialIndex % RadialN)),
//				VertexMap.Find(FIntPoint(AxialIndex - 1, (RadialIndex - 1) % RadialN)),
//				VertexMap.Find(FIntPoint(AxialIndex, (RadialIndex - 1) % RadialN))));
//			FaceMap.Add(FIntVector(
//				VertexMap.Find(FIntPoint(AxialIndex, (RadialIndex - 1) % RadialN)),
//				VertexMap.Find(FIntPoint(AxialIndex, RadialIndex),
//				VertexMap.Find(FIntPoint(AxialIndex - 1, RadialIndex));
//			
//		}
//	}
//
//	// Object Details
//	FString ObjectName = FString("MyObject");
//
//
//	TArray Vertices;
//	Vertices.Add(FVector(86.6, 75, 0));
//	Vertices.Add(FVector(-86.6, 75, 0));
//	Vertices.Add(FVector(2.13, 25, 175));
//	Vertices.Add(FVector(2.13, -75, 0));
//	int numberOfVertices = Vertices.Num();
//
//	struct Face {
//		unsigned int v1;
//		unsigned int v2;
//		unsigned int v3;
//		short materialID;
//		FVector2D uvCoords1;
//		FVector2D uvCoords2;
//		FVector2D uvCoords3;
//	};
//	mesh
//	TArray<Faces>;
//	Face oneFace;
//	oneFace = { 1,3,0,  0,  FVector2D(0,0), FVector2D(1, 0), FVector2D(0.5, 1) };
//	Faces.Add(oneFace);
//	oneFace = { 0,2,1,  1,  FVector2D(0,0), FVector2D(1, 0), FVector2D(0.5, 1) };
//	Faces.Add(oneFace);
//	oneFace = { 3,2,0,  0,  FVector2D(0,0), FVector2D(1, 0), FVector2D(0.5, 1) };
//	Faces.Add(oneFace);
//	oneFace = { 1,2,3,  1,  FVector2D(0,0), FVector2D(1, 0), FVector2D(0.5, 1) };
//	Faces.Add(oneFace);
//	int numberOfFaces = Faces.Num();
//
//	TArray Materials; //This should contain the real Materials, this is just an example
//	Materials.Add(FStaticMaterial());
//	Materials.Add(FStaticMaterial());
//	int numberOfMaterials = Materials.Num();
//
//	// Create Package
//	FString pathPackage = FString("/Game/MyStaticMeshes/");
//	FString absolutePathPackage = FPaths::GameContentDir() + "/MyStaticMeshes/";
//
//	FPackageName::RegisterMountPoint(*pathPackage, *absolutePathPackage);
//
//	UPackage* Package = CreatePackage(nullptr, *pathPackage);
//
//	// Create Static Mesh
//	FName StaticMeshName = MakeUniqueObjectName(Package, UStaticMesh::StaticClass(), FName(*ObjectName));
//	UStaticMesh* myStaticMesh = NewObject(Package, StaticMeshName, RF_Public | RF_Standalone);
//
//	if (myStaticMesh != NULL)
//	{
//		FRawMesh myRawMesh = FRawMesh();
//		FColor WhiteVertex = FColor(255, 255, 255, 255);
//		FVector EmptyVector = FVector(0, 0, 0);
//
//		// Vertices
//		for (int vertIndex = 0; vertIndex < numberOfVertices; vertIndex++) {
//			myRawMesh.VertexPositions.Add(Vertices[vertIndex]);
//		}
//		// Faces and UV/Normals
//		for (int faceIndex = 0; faceIndex < numberOfFaces; faceIndex++) {
//			myRawMesh.WedgeIndices.Add(Faces[faceIndex].v1);
//			myRawMesh.WedgeIndices.Add(Faces[faceIndex].v2);
//			myRawMesh.WedgeIndices.Add(Faces[faceIndex].v3);
//
//			myRawMesh.WedgeColors.Add(WhiteVertex);
//			myRawMesh.WedgeColors.Add(WhiteVertex);
//			myRawMesh.WedgeColors.Add(WhiteVertex);
//
//			myRawMesh.WedgeTangentX.Add(EmptyVector);
//			myRawMesh.WedgeTangentX.Add(EmptyVector);
//			myRawMesh.WedgeTangentX.Add(EmptyVector);
//
//			myRawMesh.WedgeTangentY.Add(EmptyVector);
//			myRawMesh.WedgeTangentY.Add(EmptyVector);
//			myRawMesh.WedgeTangentY.Add(EmptyVector);
//
//			myRawMesh.WedgeTangentZ.Add(EmptyVector);
//			myRawMesh.WedgeTangentZ.Add(EmptyVector);
//			myRawMesh.WedgeTangentZ.Add(EmptyVector);
//
//			// Materials
//			myRawMesh.FaceMaterialIndices.Add(Faces[faceIndex].materialID);
//
//			myRawMesh.FaceSmoothingMasks.Add(0xFFFFFFFF); // Phong
//
//			for (int UVIndex = 0; UVIndex < MAX_MESH_TEXTURE_COORDS; UVIndex++)
//			{
//				myRawMesh.WedgeTexCoords[UVIndex].Add(Faces[faceIndex].uvCoords1);
//				myRawMesh.WedgeTexCoords[UVIndex].Add(Faces[faceIndex].uvCoords2);
//				myRawMesh.WedgeTexCoords[UVIndex].Add(Faces[faceIndex].uvCoords3);
//			}
//		}
//
//		// Saving mesh in the StaticMesh
//		new(myStaticMesh->SourceModels) FStaticMeshSourceModel();
//		myStaticMesh->SourceModels[0].RawMeshBulkData->SaveRawMesh(myRawMesh);
//
//		FStaticMeshSourceModel& SrcModel = myStaticMesh->SourceModels[0];
//
//		// Model Configuration
//		myStaticMesh->SourceModels[0].BuildSettings.bRecomputeNormals = true;
//		myStaticMesh->SourceModels[0].BuildSettings.bRecomputeTangents = true;
//		myStaticMesh->SourceModels[0].BuildSettings.bUseMikkTSpace = false;
//		myStaticMesh->SourceModels[0].BuildSettings.bGenerateLightmapUVs = true;
//		myStaticMesh->SourceModels[0].BuildSettings.bBuildAdjacencyBuffer = false;
//		myStaticMesh->SourceModels[0].BuildSettings.bBuildReversedIndexBuffer = false;
//		myStaticMesh->SourceModels[0].BuildSettings.bUseFullPrecisionUVs = false;
//		myStaticMesh->SourceModels[0].BuildSettings.bUseHighPrecisionTangentBasis = false;
//
//		// Assign the Materials to the Slots (optional
//
//		for (int32 MaterialID = 0; MaterialID < numberOfMaterials; MaterialID++) {
//			myStaticMesh->StaticMaterials.Add(Materials[MaterialID]);
//			myStaticMesh->SectionInfoMap.Set(0, MaterialID, FMeshSectionInfo(MaterialID));
//		}
//
//		// Processing the StaticMesh and Marking it as not saved
//		myStaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
//		myStaticMesh->CreateBodySetup();
//		myStaticMesh->SetLightingGuid();
//		myStaticMesh->PostEditChange();
//		Package->MarkPackageDirty();
//
//		UE_LOG(LogTemp, Log, TEXT("Static Mesh created: %s"), &ObjectName);
//
//	};
//}
void UQuantumLandBlueprintFxnLibrary::FxnGetValidDivisor(
	TArray<FVector2D>& InputArray,
	int32 MaximumToCheck,
	float ToleranceLevel,
	bool& FoundValidDivisor,
	int32& OutputExponentialLevel) {
	FoundValidDivisor = false;
	for (OutputExponentialLevel = 0; !FoundValidDivisor && OutputExponentialLevel < MaximumToCheck; OutputExponentialLevel++) {
		bool CurrentValidLevel = true;
		float CurrentMultiplier;
		if (OutputExponentialLevel == 0) {
			CurrentMultiplier = 1.0;
		}
		else {
			CurrentMultiplier = FMath::Pow(2.0, OutputExponentialLevel);
		}
		for (auto& iter : InputArray) {
			float CurrentMagReal = iter.X;
			float AdjustedMagReal = CurrentMagReal * CurrentMultiplier;
			float AdjustedMagRadicalReal = AdjustedMagReal / FMath::Sqrt(2.0);
			bool AdjustedMagValidReal = 
				FMath::IsNearlyEqual(AdjustedMagReal, FMath::RoundToInt(AdjustedMagReal), ToleranceLevel);
			bool AdjustedMagRadicalValidReal =
				FMath::IsNearlyEqual(AdjustedMagRadicalReal, FMath::RoundToInt(AdjustedMagRadicalReal), ToleranceLevel);
			bool CurrentValidLevelReal = 
				(AdjustedMagValidReal || AdjustedMagRadicalValidReal);
			float CurrentMagImaginary = iter.Y;
			float AdjustedMagImaginary = CurrentMagImaginary * CurrentMultiplier;
			float AdjustedMagRadicalImaginary = AdjustedMagImaginary / FMath::Sqrt(2.0);
			bool AdjustedMagValidImaginary =
				FMath::IsNearlyEqual(AdjustedMagImaginary, FMath::RoundToInt(AdjustedMagImaginary), ToleranceLevel);
			bool AdjustedMagRadicalValidImaginary =
				FMath::IsNearlyEqual(AdjustedMagRadicalImaginary, FMath::RoundToInt(AdjustedMagRadicalImaginary), ToleranceLevel);
			bool CurrentValidLevelImaginary =
				(AdjustedMagValidImaginary || AdjustedMagRadicalValidImaginary);
			if (!CurrentValidLevelReal || !CurrentValidLevelImaginary) {
				CurrentValidLevel = false;
			}
		}
		if (CurrentValidLevel) FoundValidDivisor = true;
	}
}
void UQuantumLandBlueprintFxnLibrary::FxnGetIntVectorDyadicMapFromIntVectorComplex(
	TMap<FIntVector, FVector2D>& InputMapIntVectorToComplex,
	float ToleranceLevel,
	int32 InputPowerOfTwo,
	TMap<FIntVector, FQuantumDyadicComplexRadical>& OutputMapIntVectorToDyadic,
	bool& SuccessFlag) {
	SuccessFlag = true;
	for (auto& iter : InputMapIntVectorToComplex) {
		FQuantumDyadicComplexRadical CurrentDyadic =
			GetDyadicFromComplex(iter.Value, InputPowerOfTwo, ToleranceLevel);
		if (CurrentDyadic.PowerOfTwoDenominator < 0) {
			SuccessFlag = false;
		}
		else {
			OutputMapIntVectorToDyadic.Add(iter.Key, CurrentDyadic);
		}
	}
}
void UQuantumLandBlueprintFxnLibrary::FxnGetIntPointDyadicMapFromIntPointComplex(
	TMap<FIntPoint, FVector2D>& InputMapIntVectorToComplex,
	float ToleranceLevel,
	int32 InputPowerOfTwo,
	TMap<FIntPoint, FQuantumDyadicComplexRadical>& OutputMapIntVectorToDyadic,
	bool& SuccessFlag) {
	SuccessFlag = true;
	for (auto& iter : InputMapIntVectorToComplex) {
		FQuantumDyadicComplexRadical CurrentDyadic =
			GetDyadicFromComplex(iter.Value, InputPowerOfTwo, ToleranceLevel);
		if (CurrentDyadic.PowerOfTwoDenominator < 0) {
			SuccessFlag = false;
		}
		else {
			OutputMapIntVectorToDyadic.Add(iter.Key, CurrentDyadic);
		}
	}
}
FQuantumDyadicComplexRadical UQuantumLandBlueprintFxnLibrary::GetDyadicFromComplex(
	FVector2D InputComplex,
	int32 InputPowerOfTwo,
	float ToleranceLevel) {
	bool ErrorFlagCurrent = false;
	FQuantumDyadicComplexRadical OutputDyadic;
	float CurrentMultiplier;
	if (InputPowerOfTwo == 0) {
		CurrentMultiplier = 1.0;
	}
	else {
		CurrentMultiplier = FMath::Pow(2.0, InputPowerOfTwo);
	}
	int32 CurrentIntMultiplier = FMath::RoundToInt(CurrentMultiplier);
	float CurrentReal = InputComplex.X * CurrentMultiplier;
	float CurrentRealRadical = CurrentReal / FMath::Sqrt(2.0);
	if (FMath::IsNearlyEqual(CurrentReal, FMath::RoundToInt(CurrentReal), ToleranceLevel)) {
		OutputDyadic.NumeratorReal = FMath::RoundToInt(CurrentReal);
		OutputDyadic.RationalReal = true;
	}
	else if (FMath::IsNearlyEqual(CurrentRealRadical, FMath::RoundToInt(CurrentRealRadical), ToleranceLevel)) {
		OutputDyadic.NumeratorReal = FMath::RoundToInt(CurrentRealRadical);
		OutputDyadic.RationalReal = false;
	}
	else {
		ErrorFlagCurrent = true;
	}
	float CurrentImaginary = InputComplex.X * CurrentMultiplier;
	float CurrentImaginaryRadical = CurrentImaginary / FMath::Sqrt(2.0);
	if (FMath::IsNearlyEqual(CurrentImaginary, FMath::RoundToInt(CurrentImaginary), ToleranceLevel)) {
		OutputDyadic.NumeratorImaginary = FMath::RoundToInt(CurrentImaginary);
		OutputDyadic.RationalImaginary = true;
	}
	else if (FMath::IsNearlyEqual(CurrentImaginaryRadical, FMath::RoundToInt(CurrentImaginaryRadical), ToleranceLevel)) {
		OutputDyadic.NumeratorImaginary = FMath::RoundToInt(CurrentImaginaryRadical);
		OutputDyadic.RationalImaginary = false;
	}
	else {
		ErrorFlagCurrent = true;
	}
	if (ErrorFlagCurrent) {
		OutputDyadic.PowerOfTwoDenominator = -1;
	}
	else {
		if (OutputDyadic.NumeratorReal == FMath::RoundToInt(FMath::Pow(2.0, OutputDyadic.PowerOfTwoDenominator))
			&& OutputDyadic.NumeratorImaginary == 0 && OutputDyadic.RationalReal) {
			OutputDyadic.NumeratorReal = 1;
			OutputDyadic.PowerOfTwoDenominator = 0;
		}
		else if (OutputDyadic.NumeratorReal == -FMath::RoundToInt(FMath::Pow(2.0, OutputDyadic.PowerOfTwoDenominator))
			&& OutputDyadic.NumeratorImaginary == 0 && OutputDyadic.RationalReal) {
			OutputDyadic.NumeratorReal = -1;
			OutputDyadic.PowerOfTwoDenominator = 0;
		}
		else if (OutputDyadic.NumeratorReal == 0 && OutputDyadic.RationalImaginary
			&& OutputDyadic.NumeratorImaginary == FMath::RoundToInt(FMath::Pow(2.0, OutputDyadic.PowerOfTwoDenominator))) {
			OutputDyadic.NumeratorImaginary = 1;
			OutputDyadic.PowerOfTwoDenominator = 0;
		}
		else if (OutputDyadic.NumeratorReal == 0 && OutputDyadic.RationalImaginary
			&& OutputDyadic.NumeratorImaginary == -FMath::RoundToInt(FMath::Pow(2.0, OutputDyadic.PowerOfTwoDenominator))) {
			OutputDyadic.NumeratorImaginary = -1;
			OutputDyadic.PowerOfTwoDenominator = 0;
		}
		else {
			OutputDyadic.PowerOfTwoDenominator = InputPowerOfTwo;
		}
	}
	return OutputDyadic;
}
FIntVector UQuantumLandBlueprintFxnLibrary::GetDyadicCodedFromDyadic(
	FQuantumDyadicComplexRadical InputDyadic) {
	int32 LocalValueZ = 0;
	if (InputDyadic.NumeratorReal == FMath::RoundToInt(FMath::Pow(2.0, InputDyadic.PowerOfTwoDenominator)) 
		&& InputDyadic.NumeratorImaginary == 0 && InputDyadic.RationalReal) {
		return FIntVector(1, 0, 3);
	}
	else if (InputDyadic.NumeratorReal == 0 && InputDyadic.RationalImaginary
		&& InputDyadic.NumeratorImaginary == FMath::RoundToInt(FMath::Pow(2.0, InputDyadic.PowerOfTwoDenominator))) {
		return FIntVector(0, 1, 3);
	}
	else {
		if (InputDyadic.RationalReal || InputDyadic.NumeratorReal == 0) {
			LocalValueZ += 1;
		}
		if (InputDyadic.RationalImaginary || InputDyadic.NumeratorImaginary == 0) {
			LocalValueZ += 2;
		}
		LocalValueZ += (4 * InputDyadic.PowerOfTwoDenominator);
		return FIntVector(InputDyadic.NumeratorReal, InputDyadic.NumeratorImaginary, LocalValueZ);
	}
}
void UQuantumLandBlueprintFxnLibrary::FxnGetDyadicFromComplex(
	FVector2D InputComplex,
	int32 InputPowerOfTwo,
	float ToleranceLevel,
	//UPARAM(ref) TMap<FIntPoint, FVector2D>& InputRefTMapMatrixKetSpace);
	FQuantumDyadicComplexRadical& OutputQuantumDyadicComplexRadical) {
	OutputQuantumDyadicComplexRadical = GetDyadicFromComplex(InputComplex,InputPowerOfTwo,ToleranceLevel);
}
void UQuantumLandBlueprintFxnLibrary::FxnGetDyadicCodedFromDyadic(
	UPARAM(ref) FQuantumDyadicComplexRadical& InputQuantumDyadicComplexRadical,
	FIntVector& OutputCodedIntVector) {
	OutputCodedIntVector = GetDyadicCodedFromDyadic(InputQuantumDyadicComplexRadical);
}
