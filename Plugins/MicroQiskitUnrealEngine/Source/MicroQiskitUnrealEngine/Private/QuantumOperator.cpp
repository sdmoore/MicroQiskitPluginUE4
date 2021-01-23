// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantumOperator.h"

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

uint64 UQuantumOperator::FxnGetHash(uint32 InputFromState, uint32 InputToState) {
    uint64 OutputHashValue = InputToState * MAX_uint32 + InputFromState;
    return OutputHashValue;
}
uint32 UQuantumOperator::FxnGetInverseHashFromState(uint64 InputHash) {
    uint32 OutputValue;
    OutputValue = InputHash % ((uint64)MAX_uint32);
    return OutputValue;
}
uint32 UQuantumOperator::FxnGetInverseHashToState(uint64 InputHash) {
    uint32 OutputValue;
    OutputValue = InputHash / ((uint64)MAX_uint32);
    return OutputValue;
}
UQuantumOperator::UQuantumOperator() {
	QubitCount = 0;
}
UQuantumOperator::UQuantumOperator(FQuantumGateSpecifier InputFQuantumGateSpecifier) {
    if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::CX) {
        QubitCount = 1 + 
            FMath::Max(InputFQuantumGateSpecifier.ControlQubit, 
                InputFQuantumGateSpecifier.TargetQubit);
    }
    else {
        QubitCount = 1 + InputFQuantumGateSpecifier.TargetQubit;
    }
    float LocalSqrtTwo = FMath::Sqrt(2.0);
    uint32 LocalHilbertSpaceDim = static_cast<uint32>(HilbertSpaceDim);
    uint32 LocalTargetQubit = static_cast<uint32>(
        InputFQuantumGateSpecifier.TargetQubit);
    uint32 LocalControlQubit = static_cast<uint32>(
        InputFQuantumGateSpecifier.ControlQubit);
    for (uint32 Index = 0; Index < LocalHilbertSpaceDim; Index++) {
        //uint64 CurrentHashUnchanged = FxnGetHash(Index, Index);
        uint32 IndexTargetBitFipped = ToggleBit(Index, LocalTargetQubit);
		//uint64 CurrentHashTargetBitFlipped = FxnGetHash(Index, IndexTargetBitFipped);
		uint64 CurrentHashZeroToZero = 
            FxnGetHash(Index, Index);
		uint64 CurrentHashZeroToOne = 
            FxnGetHash(Index, IndexTargetBitFipped);
		uint64 CurrentHashOneToZero = 
            FxnGetHash(IndexTargetBitFipped, Index);
		uint64 CurrentHashOneToOne = 
            FxnGetHash(IndexTargetBitFipped, IndexTargetBitFipped);
		bool bTargetQubit = bCheckBit(Index, LocalTargetQubit);
		bool bControlQubit = bCheckBit(Index, LocalControlQubit);
        switch (InputFQuantumGateSpecifier.EnumGateType) {
            case EQuantumGateType::CX:
				if (bControlQubit) {
					if (bTargetQubit) {
						TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(1.0, 0.0));
					}
					else {
						TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
					}
				}
				else {
					if (bTargetQubit) {
						TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(1.0, 0.0));
					}
					else {
						TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(1.0, 0.0));
					}
				}
            case EQuantumGateType::Hadamard:
				if (bTargetQubit) {
					TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(LocalSqrtTwo, 0.0));
	    			TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-LocalSqrtTwo, 0.0));
				}
				else {
					TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(LocalSqrtTwo, 0.0));
					TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(LocalSqrtTwo, 0.0));
				}
            case EQuantumGateType::X:
                if (bTargetQubit) {
                    TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(1.0, 0.0));
                }
                else {
                    TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(1.0, 0.0));
                }
            case EQuantumGateType::Y:
                if (bTargetQubit) {
                    TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(0.0, 1.0));
                }
                else {
                    TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(0.0, -1.0));
                }
            case EQuantumGateType::Z:
                if (bTargetQubit) {
                    TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-1.0, 0.0));
                }
                else {
                    TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
                }
            case EQuantumGateType::S:
                if (bTargetQubit) {
                    TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, 1.0));
                }
                else {
                    TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
                }
            case EQuantumGateType::SDagger:
                if (bTargetQubit) {
                    TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, -1.0));
                }
                else {
                    TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
                }
            case EQuantumGateType::T:
                if (bTargetQubit) {
                    TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, LocalSqrtTwo));
                }
                else {
                    TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
                }
            case EQuantumGateType::TDagger:
                if (bTargetQubit) {
                    TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, -LocalSqrtTwo));
                }
                else {
                    TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
                }
            }
    }

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
UQuantumOperator::UQuantumOperator(UQuantumOperator OperatorLHS, UQuantumOperator OperatorRHS) {
    for (auto& iterLHS : OperatorLHS.TMapMatrixKetSpace) {
        //uint32 ToStateConjugateLHS = FxnGetInverseHashFromState(iterLHS.Key);
        //uint32 FromStateConjugateLHS = FxnGetInverseHashToState(iterLHS.Key);
        uint32 FromStateLHS = FxnGetInverseHashFromState(iterLHS.Key);
        uint32 ToStateLHS = FxnGetInverseHashToState(iterLHS.Key);
        for (auto& iterRHS : OperatorRHS.TMapMatrixKetSpace) {
            uint32 FromStateRHS = FxnGetInverseHashFromState(iterRHS.Key);
            uint32 ToStateRHS = FxnGetInverseHashToState(iterRHS.Key);
            if (OperatorLHS.TMapMatrixKetSpace.Contains(FxnGetHash(FromStateLHS, ToStateRHS)) &&
                OperatorRHS.TMapMatrixKetSpace.Contains(iterRHS.Key)) {
                //FVector2D AddedValue = FxnComplexMultiplyConjugate(
                //    OperatorRHS.TMapMatrixKetSpace[iterRHS.Key],
                //    OperatorLHS.TMapMatrixKetSpace[FxnGetHash(FromStateLHS, ToStateRHS)],
                //    true);
                FVector2D Input0 = OperatorRHS.TMapMatrixKetSpace[iterRHS.Key];
                FVector2D Input1 = OperatorLHS.TMapMatrixKetSpace[FxnGetHash(FromStateLHS, ToStateRHS)];
                FVector2D AddedValue = FVector2D(
                    Input0.X * Input1.X + Input0.Y * Input1.Y,
                    -Input0.X * Input1.Y + Input0.Y * Input1.X
                );
                uint64 AddedKey = FxnGetHash(ToStateLHS, ToStateRHS);
                if (TMapMatrixKetSpace.Contains(AddedKey)) {
                    FVector2D NewValue = TMapMatrixKetSpace[AddedKey] + AddedValue;
                    TMapMatrixKetSpace[AddedKey] = NewValue;
                }
                else TMapMatrixKetSpace.Add(AddedKey, AddedValue);

            }
        }
    }
}
UQuantumCircuit::UQuantumCircuit() {
	//QubitCount = 0;
}
UQuantumGate::UQuantumGate() {
	//QubitCount = 0;
}
//UQuantumOperator UQuantumCircuit::GetOperatorSubset(int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1) {
//    for()
//    UQuantumOperator = 
//}
//void UQuantumCircuit::AddGate(FQuantumGateSpecifier) {
//
//}
