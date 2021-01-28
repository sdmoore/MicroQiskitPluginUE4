// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantumCircuit.h"

uint32 SetBit(uint32 InputInteger, uint32 InputTargetBit) {
	const uint32 OneUnsignedLong = 1;
	uint32 BitTargeted = (OneUnsignedLong << (InputTargetBit));
	uint32 OutputInteger = InputInteger;
	OutputInteger |= BitTargeted;
	return OutputInteger;
}
uint32 ClearBit(uint32 InputInteger, uint32 InputTargetBit) {
	const uint32 OneUnsignedLong = 1;
	uint32 BitTargeted = (OneUnsignedLong << (InputTargetBit));
	uint32 OutputInteger = InputInteger;
	OutputInteger &= ~BitTargeted;
	return OutputInteger;
}
uint32 ToggleBit(uint32 InputInteger, uint32 InputTargetBit) {
	const uint32 OneUnsignedLong = 1;
	uint32 BitTargeted = (OneUnsignedLong << (InputTargetBit));
	uint32 OutputInteger = InputInteger;
	OutputInteger ^= BitTargeted;
	return OutputInteger;
}
bool bCheckBit(uint32 InputInteger, uint32 InputTargetBit) {
	const uint32 OneUnsignedLong = 1;
	bool OutputBool = ((InputInteger >> (InputTargetBit)) & OneUnsignedLong);
	return OutputBool;
}

uint8 FxnGetMaxQubitsFromHilbert64(uint64 InputValue) {
	uint64 Temp1UL = 1;
	uint8 OutputValue = 0;
	while (InputValue >= (Temp1UL << OutputValue)) {
		OutputValue++;
	}
	return OutputValue;
}
uint8 FxnGetMaxQubitsFromHilbert32(uint32 InputInt) {
	return FxnGetMaxQubitsFromHilbert64(static_cast<uint64>(InputInt));
}
uint8 FxnGetMaxQubitsFromHilbertSigned32(int32 InputInt) {
	return FxnGetMaxQubitsFromHilbert64(static_cast<uint64>(FMath::Abs(InputInt)));
}
int32 FxnGetMaxValueFromMapKeys(TMap<FIntPoint, FVector2D> InputMap) {
	int32 CurrentMax = 0;
	for (auto& iter : InputMap) {
		if (CurrentMax < iter.Key.GetMax()) {
			CurrentMax = iter.Key.GetMax();
		}
	}
	return CurrentMax;
}
uint8 FxnGetMaxQubitsFromMapKeys(TMap<FIntPoint, FVector2D> InputMap) {
	return FxnGetMaxQubitsFromHilbert64(static_cast<uint64>(FMath::Abs(FxnGetMaxValueFromMapKeys(InputMap))));
}
int32 FxnGetMaxValueFromMapKeys32(TMap<int32, FVector2D> InputMap) {
	int32 CurrentMax = 0;
	for (auto& iter : InputMap) {
		if (CurrentMax < iter.Key) {
			CurrentMax = iter.Key;
		}
	}
	return CurrentMax;
}
uint8 FxnGetMaxQubitsFromMapKeys32(TMap<int32, FVector2D> InputMap) {
	return FxnGetMaxQubitsFromHilbert64(static_cast<uint64>(FMath::Abs(FxnGetMaxValueFromMapKeys32(InputMap))));
}


uint8 FQuantumGateSpecifier::GetMinimumQubitsGateSpecifier() {
	if (EnumGateType == EQuantumGateType::CX) {
		return (FMath::Max(ControlQubit, TargetQubit) + 1);
	}
	else if (EnumGateType == EQuantumGateType::CustomUnitary || EnumGateType == EQuantumGateType::Identity) {
		return 0;
	}
	else {
		return (TargetQubit + 1);
	}
}
uint8 FQuantumKet::GetMinimumQubitsKet() {
	uint8 LocalQubitCount = 0;
	for (auto& iter : TMapKetSpace) {
		//int32 LocalMax = iter.Key;
		uint8 LocalMax = FxnGetMaxQubitsFromHilbert32(iter.Key);
		if (LocalQubitCount < LocalMax) {
			LocalQubitCount = LocalMax;
		}
	}
	return LocalQubitCount;
}
//uint64 FQuantumOperator::FxnGetHash(uint32 InputFromState, uint32 InputToState) {
//	uint64 OutputHashValue = InputToState * MAX_uint32 + InputFromState;
//	return OutputHashValue;
//}
//uint32 FQuantumOperator::FxnGetInverseHashFromState(uint64 InputHash) {
//	uint32 OutputValue;
//	OutputValue = InputHash % ((uint64)MAX_uint32);
//	return OutputValue;
//}
//uint32 FQuantumOperator::FxnGetInverseHashToState(uint64 InputHash) {
//	uint32 OutputValue;
//	OutputValue = InputHash / ((uint64)MAX_uint32);
//	return OutputValue;
//}
//FIntPoint FQuantumOperator::FxnGetHash(uint32 InputFromState, uint32 InputToState) {
//	FIntPoint OutputHashValue = FIntPoint(static_cast<int32>(InputFromState), static_cast<int32>(InputToState));
//	return OutputHashValue;
//}
//int32 FQuantumOperator::FxnGetInverseHashFromState(FIntPoint InputHash) {
//	return InputHash.X;
//}
//int32 FQuantumOperator::FxnGetInverseHashToState(FIntPoint InputHash) {
//	return InputHash.Y;
//}
FQuantumOperator::FQuantumOperator() {
	int32 x = 0;
}
void FQuantumOperator::InitializeQuantumOperator(FQuantumGateSpecifier InputFQuantumGateSpecifier, uint8 InputQubitCount) {
	//if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::CX) {
	//    QubitCount = 1 + 
	//        FMath::Max(InputFQuantumGateSpecifier.ControlQubit, 
	//            InputFQuantumGateSpecifier.TargetQubit);
	//}
	//else {
	//    QubitCount = 1 + InputFQuantumGateSpecifier.TargetQubit;
	//}
	//WeakPtrUQuantumHilbertSpaceOwning = InputQuantumHilbertSpaceOwning;
	uint32 LocalHilbertSpaceDim = static_cast<int32>(static_cast<uint32>(1) << static_cast<uint32>(InputQubitCount));
	float LocalSqrtTwo = FMath::Sqrt(2.0);
	uint32 LocalTargetQubit = static_cast<uint32>(
		InputFQuantumGateSpecifier.TargetQubit);
	uint32 LocalControlQubit = static_cast<uint32>(
		InputFQuantumGateSpecifier.ControlQubit);
	for (uint32 Index = 0; Index < LocalHilbertSpaceDim; Index++) {
		//uint64 CurrentHashUnchanged = FxnGetHash(Index, Index);
		uint32 IndexTargetBitFipped = ToggleBit(Index, LocalTargetQubit);
		//uint64 CurrentHashTargetBitFlipped = FxnGetHash(Index, IndexTargetBitFipped);
		FIntPoint CurrentHashZeroToZero = FIntPoint(Index, Index);
			//FxnGetHash(Index, Index);
		FIntPoint CurrentHashZeroToOne = FIntPoint(Index, IndexTargetBitFipped);
			//FxnGetHash(Index, IndexTargetBitFipped);
		FIntPoint CurrentHashOneToZero = FIntPoint(IndexTargetBitFipped, Index);
			//FxnGetHash(IndexTargetBitFipped, Index);
		FIntPoint CurrentHashOneToOne = FIntPoint(IndexTargetBitFipped, IndexTargetBitFipped);
			//FxnGetHash(IndexTargetBitFipped, IndexTargetBitFipped);
		bool bTargetQubit = bCheckBit(Index, LocalTargetQubit);
		bool bControlQubit = bCheckBit(Index, LocalControlQubit);
		if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::CX) {
			if (bControlQubit) {
				if (bTargetQubit) {
					TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(1.0, 0.0));
				}
				else {
					TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(1.0, 0.0));
				}
			}
			else {
				if (bTargetQubit) {
					TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(1.0, 0.0));
				}
				else {
					TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
				}
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Hadamard) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(LocalSqrtTwo, 0.0));
				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-LocalSqrtTwo, 0.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(LocalSqrtTwo, 0.0));
				TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(LocalSqrtTwo, 0.0));
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::X) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(1.0, 0.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(1.0, 0.0));
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Y) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(0.0, 1.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(0.0, -1.0));
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Z) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-1.0, 0.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::S) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, 1.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::SDagger) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, -1.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::T) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, LocalSqrtTwo));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::TDagger) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, -LocalSqrtTwo));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			}
		}
	}

}
FQuantumOperator::FQuantumOperator(FQuantumGateSpecifier InputFQuantumGateSpecifier, uint8 InputQubitCount) {
	InitializeQuantumOperator(InputFQuantumGateSpecifier, InputQubitCount);
}

/*
 Left Hand Side (LHS) and Right Hand Side (RHS) refer to order Matrix Multiplication
 LHS refers to quantum gates or operators that apply to a quantum state AFTER RHS
 Typically a quantum circuit is shown in reverse direction than Matrix Multiplication
 which is typically used by physicist and mathematicians.

 We want to avoid confusion on Columns, Rows, Kets, Bras, etc. which would result
 regarding the question of whether unitary operators are Hermitian (identical in
 the conjugate transpose space, which is true of X or y but NOT true of T or T-Dagger).
 So instead of Kets (traditionally columns) being acted on by a Matrix we will
 identify a Matrix entry by the 2D integer coordinates of "From" and "To" to.  This
 allows the transition to represented with natural language.

*/
FQuantumOperator FQuantumOperator::LeftSideMultiplyOperator(FQuantumOperator& InputQuantumOperator) {
	FQuantumOperator OutputQuantumOperator = FQuantumOperator();
	TMap<FIntPoint, FVector2D>& MatrixLHS = TMapMatrixKetSpace;
	TMap<FIntPoint, FVector2D>& MatrixRHS = InputQuantumOperator.TMapMatrixKetSpace;
	TMap<FIntPoint, FVector2D>& MatrixOutput = OutputQuantumOperator.TMapMatrixKetSpace;
	MatrixOutput.Empty();
	for (auto& iterLHS : MatrixLHS) {
		//uint32 ToStateConjugateLHS = FxnGetInverseHashFromState(iterLHS.Key);
		//uint32 FromStateConjugateLHS = FxnGetInverseHashToState(iterLHS.Key);
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
				if (MatrixOutput.Contains(AddedKey)) {
					FVector2D NewValue = MatrixOutput[AddedKey] + AddedValue;
					MatrixOutput[AddedKey] = NewValue;
				}
				else MatrixOutput.Add(AddedKey, AddedValue);
			}
		}
	}
	return OutputQuantumOperator;
}
FQuantumKet FQuantumOperator::LeftSideMultiplyOperatorKet(FQuantumKet& InputQuantumKet) {
	FQuantumKet OutputQuantumKet = FQuantumKet();
	TMap<FIntPoint, FVector2D>& MatrixLHS = TMapMatrixKetSpace;
	TMap<int32, FVector2D>& KetRHS = InputQuantumKet.TMapKetSpace;
	TMap<int32, FVector2D>& KetResult = OutputQuantumKet.TMapKetSpace;
	KetResult.Empty();
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
				if (KetResult.Contains(AddedKey)) {
					FVector2D NewValue = KetResult[AddedKey] + AddedValue;
					KetResult[AddedKey] = NewValue;
				}
				else KetResult.Add(AddedKey, AddedValue);
			}
		}
	}
	return OutputQuantumKet;
}
uint8 FQuantumOperator::GetMinimumQubitsOperator() {
	uint8 QubitMinCurrent = 0;
	uint8 QubitMinGate = QuantumGateSpecifier.GetMinimumQubitsGateSpecifier();
	uint8 QubitMinMatrix = FxnGetMaxQubitsFromMapKeys(TMapMatrixKetSpace);
	if (QubitMinCurrent < QubitMinGate) {
		QubitMinCurrent = QubitMinGate;
	}
	if (QubitMinCurrent < QubitMinMatrix) {
		QubitMinCurrent = QubitMinMatrix;
	}
	return QubitMinCurrent;
}

uint8 FQuantumOperatorApplied::GetMinimumQubitsOperatorApplied() {
	uint8 QubitMinCurrent = 0;
	uint8 QubitMinOperator = QuantumGateSpecifier.GetMinimumQubitsGateSpecifier();
	uint8 QubitMinMatrixKet = FxnGetMaxQubitsFromMapKeys(TMapMatrixAppliedToKetSpace);
	uint8 QubitMinFinalKet = FxnGetMaxQubitsFromMapKeys32(FinalQuantumKet.TMapKetSpace);
	if (QubitMinCurrent < QubitMinOperator) {
		QubitMinCurrent = QubitMinOperator;
	}
	if (QubitMinCurrent < QubitMinMatrixKet) {
		QubitMinCurrent = QubitMinMatrixKet;
	}
	if (QubitMinCurrent < QubitMinFinalKet) {
		QubitMinCurrent = QubitMinFinalKet;
	}
	return QubitMinCurrent;
}
void FQuantumOperatorApplied::UpdateForNewKet(float InputErrorMargin = 0.001) {
	TMap<FIntPoint, FVector2D>& MatrixLHS = TMapMatrixKetSpace;
	TMap<int32, FVector2D>& KetRHS = PtrQuantumKetInitial->TMapKetSpace;
	TMap<FIntPoint, FVector2D>& MatrixResult = TMapMatrixAppliedToKetSpace;
	TMap<int32, FVector2D>& KetResult = FinalQuantumKet.TMapKetSpace;
	MatrixResult.Empty();
	KetResult.Empty();
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
				//FIntPoint AddedKeyMatrix = FxnGetHash(FromStateLHS, ToStateRHS);
				FIntPoint AddedKeyMatrix = iterLHS.Key;
				if (MatrixResult.Contains(AddedKeyMatrix)) {
					FVector2D NewValue = MatrixResult[AddedKeyMatrix] + AddedValue;
					MatrixResult[AddedKeyMatrix] = NewValue;
				}
				else {
					MatrixResult.Add(AddedKeyMatrix, AddedValue);
				}
				if (KetResult.Contains(AddedKeyKet)) {
					FVector2D NewValue = KetResult[AddedKeyKet] + AddedValue;
					KetResult[AddedKeyKet] = NewValue;
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
		for (auto& iter : KetResult) {
			if (iter.Value.Size() < LocalKetErrorMargin) {
				KetResult.Remove(iter.Key);
			}
		}
	}
	return;
}
FQuantumOperatorApplied::FQuantumOperatorApplied() {
	int32 x = 0;
}
FQuantumOperatorApplied::FQuantumOperatorApplied(
	FQuantumKet* InputPtrQuantumKetInitial,
	FQuantumGateSpecifier InputQuantumGateSpecifier, 
	uint8 InputQubitCount) 
	: PtrQuantumKetInitial{InputPtrQuantumKetInitial} {
	InitializeQuantumOperator(InputQuantumGateSpecifier, InputQubitCount);
	UpdateForNewKet(InputPtrQuantumKetInitial, 0.001);
}
void FQuantumOperatorApplied::UpdateForNewKet(FQuantumKet* InputPtrQuantumKetInitial, float InputErrorMargin = 0.001) {
	PtrQuantumKetInitial = InputPtrQuantumKetInitial;
	UpdateForNewKet(InputErrorMargin);
	return;
}
UQuantumCircuit::UQuantumCircuit() {
	QubitCount = 0;
}
void UQuantumCircuit::InitializeQuantumCircuit() {
	CurrentGates.Empty();
	return;
}
void UQuantumCircuit::InitializeQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList) {
	InitializeQuantumCircuit();
	QubitCount = 0;
	for (auto& iter : InputGateSpecifierList) {
		int32 LocalMax = iter.GetMinimumQubitsGateSpecifier();
		if (QubitCount < LocalMax) {
			QubitCount = LocalMax;
		}
	}
	HilbertSpaceDim = static_cast<int32>(static_cast<uint32>(1) << QubitCount);
	for (auto& iter : InputGateSpecifierList) {
		int32 LocalMax = iter.GetMinimumQubitsGateSpecifier();
		if (QubitCount < LocalMax) {
			QubitCount = LocalMax;
		}
	}
	return;
}
void UQuantumCircuit::AddGate(FQuantumGateSpecifier InputQuantumGateSpecifier) {
	if (InputQuantumGateSpecifier.GetMinimumQubitsGateSpecifier() <= QubitCount) {
		FQuantumKet* LocalPtrQuantumKet = &(CurrentGates.Last().FinalQuantumKet);
		CurrentGates.Add(FQuantumOperatorApplied(LocalPtrQuantumKet, InputQuantumGateSpecifier, QubitCount));
	}
	return;
}
