//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "QuantumOperator.h"
//
//uint32 SetBit(uint32 InputInteger, uint32 InputTargetBit) {
//    const uint32 OneUnsignedLong = 1;
//    uint32 BitTargeted = (OneUnsignedLong << (InputTargetBit));
//    uint32 OutputInteger = InputInteger;
//    OutputInteger |= BitTargeted;
//	return OutputInteger;
//}
//uint32 ClearBit(uint32 InputInteger, uint32 InputTargetBit) {
//    const uint32 OneUnsignedLong = 1;
//    uint32 BitTargeted = (OneUnsignedLong << (InputTargetBit));
//	uint32 OutputInteger = InputInteger;
//	OutputInteger &= ~BitTargeted;
//	return OutputInteger;
//}
//uint32 ToggleBit(uint32 InputInteger, uint32 InputTargetBit) {
//    const uint32 OneUnsignedLong = 1;
//    uint32 BitTargeted = (OneUnsignedLong << (InputTargetBit));
//	uint32 OutputInteger = InputInteger;
//	OutputInteger ^= BitTargeted;
//    return OutputInteger;
//}
//bool bCheckBit(uint32 InputInteger, uint32 InputTargetBit) {
//	const uint32 OneUnsignedLong = 1;
//	bool OutputBool = ((InputInteger >> (InputTargetBit)) & OneUnsignedLong);
//    return OutputBool;
//}
//
//uint64 UQuantumOperator::FxnGetHash(uint32 InputFromState, uint32 InputToState) {
//    uint64 OutputHashValue = InputToState * MAX_uint32 + InputFromState;
//    return OutputHashValue;
//}
//uint32 UQuantumOperator::FxnGetInverseHashFromState(uint64 InputHash) {
//    uint32 OutputValue;
//    OutputValue = InputHash % ((uint64)MAX_uint32);
//    return OutputValue;
//}
//uint32 UQuantumOperator::FxnGetInverseHashToState(uint64 InputHash) {
//    uint32 OutputValue;
//    OutputValue = InputHash / ((uint64)MAX_uint32);
//    return OutputValue;
//}
//UQuantumOperator::UQuantumOperator() {
//	QubitCount = 0;
//    HilbertSpaceDim = 1;
//}
//UQuantumOperator::UQuantumOperator(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//	: UQuantumHilbertSpace(InputQuantumHilbertSpaceOwning->QubitCount) {
//	WeakPtrUQuantumHilbertSpaceOwning = InputQuantumHilbertSpaceOwning;
//	uint32 LocalHilbertSpaceDim = static_cast<uint32>(HilbertSpaceDim);
//	for (uint32 Index = 0; Index < LocalHilbertSpaceDim; Index++) {
//		uint64 CurrentHashDiagonal = FxnGetHash(Index, Index);
//		TMapMatrixKetSpace.Add(CurrentHashDiagonal, FVector2D(1.0, 0.0));
//	}
//}
////UQuantumOperator::UQuantumOperator(InputFQuantumGateSpecifier InputFQuantumGateSpecifier) {
////	uint8 LocalQubitCount = 0;
////	if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::CX) {
////		LocalQubitCount = 1 +
////			FMath::Max(InputFQuantumGateSpecifier.ControlQubit,
////				InputFQuantumGateSpecifier.TargetQubit);
////	}
////	else {
////		LocalQubitCount = 1 + InputFQuantumGateSpecifier.TargetQubit;
////	}
////	QubitCount = LocalQubitCount;
////	uint32 LocalDimSpace = 1;
////	HilbertSpaceDim = static_cast<int32>(LocalDimSpace << LocalQubitCount);
////}
//UQuantumOperator::UQuantumOperator(FQuantumGateSpecifier InputFQuantumGateSpecifier, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//    : UQuantumHilbertSpace(InputQuantumHilbertSpaceOwning->QubitCount) {
//    //if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::CX) {
//    //    QubitCount = 1 + 
//    //        FMath::Max(InputFQuantumGateSpecifier.ControlQubit, 
//    //            InputFQuantumGateSpecifier.TargetQubit);
//    //}
//    //else {
//    //    QubitCount = 1 + InputFQuantumGateSpecifier.TargetQubit;
//    //}
//	WeakPtrUQuantumHilbertSpaceOwning = InputQuantumHilbertSpaceOwning;
//    float LocalSqrtTwo = FMath::Sqrt(2.0);
//    uint32 LocalHilbertSpaceDim = static_cast<uint32>(HilbertSpaceDim);
//    uint32 LocalTargetQubit = static_cast<uint32>(
//        InputFQuantumGateSpecifier.TargetQubit);
//    uint32 LocalControlQubit = static_cast<uint32>(
//        InputFQuantumGateSpecifier.ControlQubit);
//    for (uint32 Index = 0; Index < LocalHilbertSpaceDim; Index++) {
//        //uint64 CurrentHashUnchanged = FxnGetHash(Index, Index);
//        uint32 IndexTargetBitFipped = ToggleBit(Index, LocalTargetQubit);
//		//uint64 CurrentHashTargetBitFlipped = FxnGetHash(Index, IndexTargetBitFipped);
//		uint64 CurrentHashZeroToZero = 
//            FxnGetHash(Index, Index);
//		uint64 CurrentHashZeroToOne = 
//            FxnGetHash(Index, IndexTargetBitFipped);
//		uint64 CurrentHashOneToZero = 
//            FxnGetHash(IndexTargetBitFipped, Index);
//		uint64 CurrentHashOneToOne = 
//            FxnGetHash(IndexTargetBitFipped, IndexTargetBitFipped);
//		bool bTargetQubit = bCheckBit(Index, LocalTargetQubit);
//		bool bControlQubit = bCheckBit(Index, LocalControlQubit);
//		if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::CX) {
//			if (bControlQubit) {
//				if (bTargetQubit) {
//					TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(1.0, 0.0));
//				}
//				else {
//					TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(1.0, 0.0));
//				}
//			}
//			else {
//				if (bTargetQubit) {
//					TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(1.0, 0.0));
//				}
//				else {
//					TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
//				}
//			}
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Hadamard) {
//			if (bTargetQubit) {
//				TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(LocalSqrtTwo, 0.0));
//	    		TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-LocalSqrtTwo, 0.0));
//			}
//			else {
//				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(LocalSqrtTwo, 0.0));
//				TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(LocalSqrtTwo, 0.0));
//			}
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::X){
//            if (bTargetQubit) {
//                TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(1.0, 0.0));
//            }
//            else {
//                TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(1.0, 0.0));
//            }
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Y) {
//            if (bTargetQubit) {
//                TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(0.0, 1.0));
//            }
//            else {
//                TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(0.0, -1.0));
//            }
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Z) {
//            if (bTargetQubit) {
//                TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-1.0, 0.0));
//            }
//            else {
//                TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
//            }
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::S) {
//            if (bTargetQubit) {
//                TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, 1.0));
//            }
//            else {
//                TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
//            }
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::SDagger) {
//			if (bTargetQubit) {
//				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, -1.0));
//			}
//			else {
//				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
//			}
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::T) {
//			if (bTargetQubit) {
//				TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, LocalSqrtTwo));
//			}
//			else {
//				TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
//			}
//		}
//		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::TDagger) {
//            if (bTargetQubit) {
//                TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, -LocalSqrtTwo));
//            }
//            else {
//                TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
//            }
//        }
//    }
//
//}
///* 
// Left Hand Side (LHS) and Right Hand Side (RHS) refer to order Matrix Multiplication
// LHS refers to quantum gates or operators that apply to a quantum state AFTER RHS
// Typically a quantum circuit is shown in reverse direction than Matrix Multiplication
// which is typically used by physicist and mathematicians.
//
// We want to avoid confusion on Columns, Rows, Kets, Bras, etc. which would result 
// regarding the question of whether unitary operators are Hermitian (identical in 
// the conjugate transpose space, which is true of X or y but NOT true of T or T-Dagger). 
// So instead of Kets (traditionally columns) being acted on by a Matrix we will 
// identify a Matrix entry by the 2D integer coordinates of "From" and "To" to.  This 
// allows the transition to represented with natural language.
//
//*/
//void UQuantumOperator::ComplexMatrixMultiply(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint64, FVector2D>& MatrixRHS, TMap<uint64, FVector2D>& MatrixOutput) {
//	MatrixOutput.Empty();
//	for (auto& iterLHS : MatrixLHS) {
//		//uint32 ToStateConjugateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		//uint32 FromStateConjugateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		uint32 FromStateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		uint32 ToStateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		for (auto& iterRHS : MatrixRHS) {
//			uint32 FromStateRHS = FxnGetInverseHashFromState(iterRHS.Key);
//			uint32 ToStateRHS = FxnGetInverseHashToState(iterRHS.Key);
//			if (ToStateRHS == FromStateLHS) {
//				FVector2D Input0 = MatrixRHS[iterRHS.Key];
//				FVector2D Input1 = MatrixLHS[iterLHS.Key];
//				FVector2D AddedValue = FVector2D(
//					Input0.X * Input1.X - Input0.Y * Input1.Y,
//					Input0.X * Input1.Y + Input0.Y * Input1.X
//				);
//				uint64 AddedKey = FxnGetHash(FromStateRHS, ToStateLHS);
//				if (MatrixOutput.Contains(AddedKey)) {
//					FVector2D NewValue = MatrixOutput[AddedKey] + AddedValue;
//					MatrixOutput[AddedKey] = NewValue;
//				}
//				else MatrixOutput.Add(AddedKey, AddedValue);
//			}
//		}
//	}
//	return;
//}
//void UQuantumOperator::ComplexKetMultiply(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint32, FVector2D>& KetRHS, TMap<uint32, FVector2D>& KetResult) {
//	KetResult.Empty();
//	for (auto& iterLHS : MatrixLHS) {
//		uint32 FromStateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		uint32 ToStateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		for (auto& iterRHS : KetRHS) {
//			uint32 ToStateRHS = iterRHS.Key;
//			if (FromStateLHS == ToStateRHS) {
//				FVector2D Input0 = KetRHS[iterRHS.Key];
//				FVector2D Input1 = MatrixLHS[iterLHS.Key];
//				FVector2D AddedValue = FVector2D(
//					Input0.X * Input1.X - Input0.Y * Input1.Y,
//					Input0.X * Input1.Y + Input0.Y * Input1.X
//				);
//				uint32 AddedKey = ToStateLHS;
//				if (KetResult.Contains(AddedKey)) {
//					FVector2D NewValue = KetResult[AddedKey] + AddedValue;
//					KetResult[AddedKey] = NewValue;
//				}
//				else KetResult.Add(AddedKey, AddedValue);
//			}
//		}
//	}
//	return;
//}
//void UQuantumOperator::ComplexKetMultiplyFullData(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint32, FVector2D>& KetRHS, TMap<uint64, FVector2D>& MatrixResult) {
//	MatrixResult.Empty();
//	for (auto& iterLHS : MatrixLHS) {
//		uint32 FromStateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		uint32 ToStateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		for (auto& iterRHS : KetRHS) {
//			uint32 ToStateRHS = iterRHS.Key;
//			if (FromStateLHS == ToStateRHS) {
//				FVector2D Input0 = KetRHS[iterRHS.Key];
//				FVector2D Input1 = MatrixLHS[iterLHS.Key];
//				FVector2D AddedValue = FVector2D(
//					Input0.X * Input1.X - Input0.Y * Input1.Y,
//					Input0.X * Input1.Y + Input0.Y * Input1.X
//				);
//				uint64 AddedKey = iterLHS.Key;
//				if (MatrixResult.Contains(AddedKey)) {
//					FVector2D NewValue = MatrixResult[AddedKey] + AddedValue;
//					MatrixResult[AddedKey] = NewValue;
//				}
//				else MatrixResult.Add(AddedKey, AddedValue);
//			}
//		}
//	}
//	return;
//}
//UQuantumOperator::UQuantumOperator(UQuantumOperator* OperatorLHS, UQuantumOperator* OperatorRHS, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//	: UQuantumHilbertSpace(InputQuantumHilbertSpaceOwning->QubitCount) {
//	if (InputQuantumHilbertSpaceOwning->QubitCount == OperatorLHS->QubitCount && InputQuantumHilbertSpaceOwning->QubitCount == OperatorRHS->QubitCount) {
//		WeakPtrUQuantumHilbertSpaceOwning = InputQuantumHilbertSpaceOwning;
//		ComplexMatrixMultiply(OperatorLHS->TMapMatrixKetSpace, OperatorRHS->TMapMatrixKetSpace, TMapMatrixKetSpace);
//		//for (auto& iterLHS : OperatorLHS->TMapMatrixKetSpace) {
//		//	//uint32 ToStateConjugateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		//	//uint32 FromStateConjugateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		//	uint32 FromStateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		//	uint32 ToStateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		//	for (auto& iterRHS : OperatorRHS->TMapMatrixKetSpace) {
//		//		uint32 FromStateRHS = FxnGetInverseHashFromState(iterRHS.Key);
//		//		uint32 ToStateRHS = FxnGetInverseHashToState(iterRHS.Key);
//		//		if (ToStateRHS == FromStateLHS) {
//		//			FVector2D Input0 = OperatorRHS->TMapMatrixKetSpace[iterRHS.Key];
//		//			FVector2D Input1 = OperatorLHS->TMapMatrixKetSpace[iterLHS.Key];
//		//			FVector2D AddedValue = FVector2D(
//		//				Input0.X * Input1.X - Input0.Y * Input1.Y,
//		//				Input0.X * Input1.Y + Input0.Y * Input1.X
//		//			);
//		//			uint64 AddedKey = FxnGetHash(FromStateRHS, ToStateLHS);
//		//			if (TMapMatrixKetSpace.Contains(AddedKey)) {
//		//				FVector2D NewValue = TMapMatrixKetSpace[AddedKey] + AddedValue;
//		//				TMapMatrixKetSpace[AddedKey] = NewValue;
//		//			}
//		//			else TMapMatrixKetSpace.Add(AddedKey, AddedValue);
//		//		}
//		//	}
//		//}
//	}
//}
//
//void UQuantumOperator::GetChangedQuantumKet(UQuantumKet* InputQuantumKet, UQuantumKet* OutputQuantumKet){
//    //UQuantumKet* OutputQuantumKet = UQuantumKet(QubitCount);
//    if (QubitCount == InputQuantumKet->QubitCount && QubitCount == OutputQuantumKet->QubitCount) {
//		//OutputQuantumKet = UQuantumKet(static_cast<UQuantumHilbertSpace*>(InputQuantumKet));
//		ComplexKetMultiply(TMapMatrixKetSpace, InputQuantumKet->TMapKetSpace, OutputQuantumKet->TMapKetSpace);
//		//for (auto& iter : TMapMatrixKetSpace) {
//		//	//uint32 ToStateConjugateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		//	//uint32 FromStateConjugateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		//	uint32 FromState = FxnGetInverseHashFromState(iter.Key);
//		//	uint32 ToState = FxnGetInverseHashToState(iter.Key);
//		//	if (InputQuantumKet->TMapKetSpace.Contains(FromState)) {
//		//		FVector2D Input0 = InputQuantumKet->TMapKetSpace[FromState];
//		//		FVector2D Input1 = iter.Value;
//		//		FVector2D AddedValue = FVector2D(
//		//			Input0.X * Input1.X + Input0.Y * Input1.Y,
//		//			-Input0.X * Input1.Y + Input0.Y * Input1.X
//		//		);
//		//		if (OutputQuantumKet->TMapKetSpace.Contains(ToState)) {
//		//			FVector2D NewValue = OutputQuantumKet->TMapKetSpace[ToState] + AddedValue;
//		//			OutputQuantumKet->TMapKetSpace[ToState] = NewValue;
//		//		}
//		//		else OutputQuantumKet->TMapKetSpace.Add(ToState, AddedValue);
//		//	}
//		//}
//	}
//  //  else {
//		//OutputQuantumKet = UQuantumKet();
//  //  }
//    //return OutputQuantumKet;
//    return;
//}
//void UQuantumOperator::LeftHandProductWithOperator(UQuantumOperator* OperatorRHS, UQuantumOperator* OperatorResult) {
//    if (QubitCount == OperatorRHS->QubitCount &&
//        QubitCount == OperatorResult->QubitCount) {
//		ComplexMatrixMultiply(TMapMatrixKetSpace, OperatorRHS->TMapMatrixKetSpace, OperatorResult->TMapMatrixKetSpace);
//		//for (auto& iterLHS : TMapMatrixKetSpace) {
//		//	//uint32 ToStateConjugateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		//	//uint32 FromStateConjugateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		//	uint32 FromStateLHS = FxnGetInverseHashFromState(iterLHS.Key);
//		//	uint32 ToStateLHS = FxnGetInverseHashToState(iterLHS.Key);
//		//	for (auto& iterRHS : OperatorRHS.TMapMatrixKetSpace) {
//		//		uint32 FromStateRHS = FxnGetInverseHashFromState(iterRHS.Key);
//		//		uint32 ToStateRHS = FxnGetInverseHashToState(iterRHS.Key);
//		//		if (TMapMatrixKetSpace.Contains(FxnGetHash(FromStateLHS, ToStateRHS)) &&
//		//			OperatorRHS.TMapMatrixKetSpace.Contains(iterRHS.Key)) {
//		//			//FVector2D AddedValue = FxnComplexMultiplyConjugate(
//		//			//    OperatorRHS.TMapMatrixKetSpace[iterRHS.Key],
//		//			//    TMapMatrixKetSpace[FxnGetHash(FromStateLHS, ToStateRHS)],
//		//			//    true);
//		//			FVector2D Input0 = OperatorRHS.TMapMatrixKetSpace[iterRHS.Key];
//		//			FVector2D Input1 = OperatorLHS.TMapMatrixKetSpace[FxnGetHash(FromStateLHS, ToStateRHS)];
//		//			FVector2D AddedValue = FVector2D(
//		//				Input0.X * Input1.X + Input0.Y * Input1.Y,
//		//				-Input0.X * Input1.Y + Input0.Y * Input1.X
//		//			);
//		//			uint64 AddedKey = FxnGetHash(ToStateLHS, ToStateRHS);
//		//			if (OperatorResult->TMapMatrixKetSpace.Contains(AddedKey)) {
//		//				FVector2D NewValue = OperatorResult->TMapMatrixKetSpace[AddedKey] + AddedValue;
//		//				OperatorResult->TMapMatrixKetSpace[AddedKey] = NewValue;
//		//			}
//		//			else OperatorResult->TMapMatrixKetSpace.Add(AddedKey, AddedValue);
//		//		}
//		//	}
//		//}
//    }
//	return;
//}
//UQuantumKet::UQuantumKet()
//	: UQuantumHilbertSpace(0) {
//	// body
//}
//UQuantumKet::UQuantumKet(int32 InputQubitCount)
//	: UQuantumHilbertSpace(InputQubitCount) {
//	// body
//}
//UQuantumKet::UQuantumKet(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//	: UQuantumHilbertSpace(InputQuantumHilbertSpaceOwning->QubitCount) {
//	TMapKetSpace.Add(static_cast<uint32>(0), FVector2D(1.0, 0));
//}
//UQuantumKet::UQuantumKet(TMap<uint32, FVector2D>& InputTMapKetSpace, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//	: UQuantumHilbertSpace(InputQuantumHilbertSpaceOwning->QubitCount) {
//	TMapKetSpace = InputTMapKetSpace;
//}
//
//UQuantumOperatorApplied::UQuantumOperatorApplied(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumKet* InputQuantumKet, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//	: UQuantumOperator(InputQuantumGateSpecifier, InputQuantumHilbertSpaceOwning) {
//	WeakPtrUQuantumKetInitial = InputQuantumKet;
//	FinalQuantumKet->SetHilbertSpaceConstructorOnly(QubitCount);
//	UpdateForNewKet();
//	//if (WeakPtrUQuantumKetInitial.IsValid()) {
//	//	ComplexKetMultiplyFullData(TMapMatrixKetSpace, WeakPtrUQuantumKetInitial->TMapKetSpace, TMapMatrixAppliedToKetSpace);
//	//	ComplexKetMultiply(TMapMatrixKetSpace, WeakPtrUQuantumKetInitial->TMapKetSpace, FinalQuantumKet->TMapKetSpace)
//	//}
//}
//UQuantumOperatorApplied::UQuantumOperatorApplied(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//	: UQuantumOperator(InputQuantumGateSpecifier, InputQuantumHilbertSpaceOwning) {
//
//}
//UQuantumOperatorApplied::UQuantumOperatorApplied(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning)
//	: UQuantumOperator(InputQuantumHilbertSpaceOwning) {
//
//}
//void UQuantumOperatorApplied::UpdateForNewKet() {
//	if (WeakPtrUQuantumKetInitial.IsValid()) {
//		ComplexKetMultiplyFullData(TMapMatrixKetSpace, WeakPtrUQuantumKetInitial->TMapKetSpace, TMapMatrixAppliedToKetSpace);
//		ComplexKetMultiply(TMapMatrixKetSpace, WeakPtrUQuantumKetInitial->TMapKetSpace, FinalQuantumKet->TMapKetSpace);
//	}
//	else {
//		TMapMatrixAppliedToKetSpace.Empty();
//		FinalQuantumKet->TMapKetSpace.Empty();
//	}
//	return;
//}
//UQuantumCircuit::UQuantumCircuit() {
//	//QubitCount = 0;
//}
////UQuantumGate::UQuantumGate(UQuantumGate* InputOwningCircuit, FQuantumGateSpecifier InputGateSpecifier)
////	: UQuantumOperator(InputQubitCount, InputGateSpecifier) {
////    OwningCicruit = InputOwningCircuit;
////	QubitCount = InputQubitCount;
////
////}
////UQuantumGate::UQuantumGate(){
////    QubitCount = 0;
////}
////UQuantumCircuit::UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, int32 InputQubitCount = 0) {
////
////}
//UQuantumCircuit::UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, int32 InputQubitCount) {
//	int32 MaxQubitCount = InputQubitCount;
//	for (auto& iter : InputGateSpecifierList) {
//		if (
//			iter.EnumGateType == EQuantumGateType::CX &&
//			(FMath::Max(iter.ControlQubit, iter.TargetQubit) + 1) > MaxQubitCount) {
//			MaxQubitCount = FMath::Max(iter.ControlQubit, iter.TargetQubit) + 1;
//		}
//		else if (
//			iter.EnumGateType != EQuantumGateType::CX &&
//			(iter.TargetQubit + 1) > MaxQubitCount) {
//			MaxQubitCount = iter.TargetQubit + 1;
//		}
//	}
//	if (MaxQubitCount < 0 || MaxQubitCount >= 16) {
//		QubitCount = 0;
//	}
//	else {
//		QubitCount = MaxQubitCount;
//	}
//	uint32 TempDim = 1;
//	HilbertSpaceDim = static_cast<int32>(FMath::Abs(TempDim << QubitCount));
//	InitialQuantumCircuitKet->SetHilbertSpaceConstructorOnly(QubitCount);
//	InitialQuantumCircuitKet->TMapKetSpace.Add(0, FVector2D(1.0, 0.0));
//	for (auto& iter : InputGateSpecifierList) {
//		bool LegitGateSingle = (iter.EnumGateType == EQuantumGateType::X || iter.EnumGateType == EQuantumGateType::Y || iter.EnumGateType == EQuantumGateType::Z ||
//			iter.EnumGateType == EQuantumGateType::T || iter.EnumGateType == EQuantumGateType::TDagger ||
//			iter.EnumGateType == EQuantumGateType::S || iter.EnumGateType == EQuantumGateType::SDagger) && iter.TargetQubit < MaxQubitCount;
//		bool LegitGateCX = iter.EnumGateType == EQuantumGateType::CX && FMath::Max(iter.ControlQubit, iter.TargetQubit) < MaxQubitCount;
//		if (LegitGateSingle || LegitGateCX || iter.EnumGateType == EQuantumGateType::Identity) {
//			AppendGate(iter);
//		}
//	}
//}
////void UQuantumCircuit::GetOperatorSubset(UQuantumOperatorApplied* OutputOperatorApplied, int32 InputStartGateIndex = 0) {
////	GetOperatorSubset(OutputOperatorApplied, InputStartGateIndex, );
////	int ActualGateIndexEnd;
////	if (InputEndGateIndex < 0)
////		ActualGateIndexEnd = CurrentGates.Num() - InputEndGateIndex;
////	UQuantumOperator* QuantumOperatorOutput = UQuantumOperator(FQuantumGateSpecifier(), static_cast<UQuantumHilbertSpace*>(this))
////		if (ActualGateIndexEnd > 0) {
////			for (int Index = InputStartGateIndex; Index < CurrentGates.Num() && Index < ActualGateIndexEnd) {
////
////			}
////		}
////	return QuantumOperatorOutput;
////}
//void UQuantumCircuit::GetOperatorAppliedSubset(UQuantumOperatorApplied* OutputOperatorApplied, int32 InputStartGateIndex, int32 InputEndGateIndex) {
//	int32 ActualGateIndexEnd;
//	int32 ActualGateIndexStart = InputStartGateIndex + 1;
//	if (InputEndGateIndex < 0)
//		ActualGateIndexEnd = CurrentGates.Num() - InputEndGateIndex;
//	if (ActualGateIndexEnd > 0 && ActualGateIndexEnd < CurrentGates.Num()) {
//		GetOperatorSubset(static_cast<UQuantumOperator*>(OutputOperatorApplied), InputStartGateIndex, InputEndGateIndex);
//		if (InputStartGateIndex == 0) {
//			OutputOperatorApplied->WeakPtrUQuantumKetInitial = InitialQuantumCircuitKet;
//			OutputOperatorApplied->UpdateForNewKet();
//		}
//	}
//	return;
//}
//void UQuantumCircuit::GetOperatorSubset(UQuantumOperator* OutputOperatorApplied, int32 InputStartGateIndex, int32 InputEndGateIndex) {
//	int32 ActualGateIndexEnd;
//	int32 ActualGateIndexStart = InputStartGateIndex + 1;
//	if (InputEndGateIndex < 0)
//		ActualGateIndexEnd = CurrentGates.Num() - InputEndGateIndex;
//	TMap<uint64, FVector2D> TempMapComplexMatrixRHS;
//	bool FirstLoop = true;
//	if (ActualGateIndexEnd > 0 && ActualGateIndexEnd < CurrentGates.Num()) {
//		for (int32 Index = ActualGateIndexStart + 1; Index <= ActualGateIndexEnd; Index++) {
//			if (FirstLoop) {
//				OutputOperatorApplied->ComplexMatrixMultiply(
//					CurrentGates[Index]->TMapMatrixKetSpace,
//					CurrentGates[Index - 1]->TMapMatrixKetSpace,
//					OutputOperatorApplied->TMapMatrixKetSpace);
//				TempMapComplexMatrixRHS = OutputOperatorApplied->TMapMatrixKetSpace;
//				FirstLoop = false;
//			}
//			else {
//				OutputOperatorApplied->ComplexMatrixMultiply(
//					CurrentGates[Index]->TMapMatrixKetSpace,
//					TempMapComplexMatrixRHS,
//					OutputOperatorApplied->TMapMatrixKetSpace);
//				TempMapComplexMatrixRHS = OutputOperatorApplied->TMapMatrixKetSpace;
//			}
//		}
//	}
//	return;
//}
////void UQuantumCircuit::AddGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGateIndex) {
////	if (InputGateIndex < 0) ActualGateIndex = CurrentGates.Num() - InputGateIndex;
////	if (ActualGateIndex >= 0 && ActualGateIndex < CurrentGates.Num()) {
////
////	}
////	if (ActualGateIndex >= CurrentGates.Num())
////		AppendGate(InputQuantumGateSpecifier);
////}
//void UQuantumCircuit::AppendGate(FQuantumGateSpecifier InputQuantumGateSpecifier) {
//	if (CurrentGates.Num() == 0) {
//		CurrentGates.Add(NewObject<UQuantumOperatorApplied>(InputQuantumGateSpecifier, 
//			InitialQuantumCircuitKet, 
//			static_cast<UQuantumHilbertSpace*>(this)));
//	}
//	else {
//		CurrentGates.Add(UQuantumOperatorApplied(InputQuantumGateSpecifier, 
//			CurrentGates.Last()->FinalQuantumKet,
//			static_cast<UQuantumHilbertSpace*>(this)));
//	}
//	return;
//}