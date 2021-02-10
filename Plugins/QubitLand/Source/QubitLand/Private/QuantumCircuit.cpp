//This program is free software : you can redistribute itand /or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.If not, see < https://www.gnu.org/licenses/>.

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
int32 GetMaxFromGateSpecifier(FQuantumGateSpecifier InputQuantumGateSpecifier ) {
	if (InputQuantumGateSpecifier.EnumGateType == EQuantumGateType::CX) {
		return (FMath::Max(InputQuantumGateSpecifier.ControlQubitArray[0], InputQuantumGateSpecifier.TargetQubitArray[0]) + 1);
	}
	else if (InputQuantumGateSpecifier.EnumGateType == EQuantumGateType::CustomUnitary || InputQuantumGateSpecifier.EnumGateType == EQuantumGateType::Identity) {
		return 0;
	}
	else {
		return (InputQuantumGateSpecifier.TargetQubitArray[0] + 1);
	}
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
FString UQuantumCircuit::FxnGetFStringComplexNumber(FVector2D InputVector2D) {
	FString StringOutput = FString("");
	float ThresholdFloat = 0.001; 
	bool ValidReal = ((InputVector2D.X > ThresholdFloat) || (InputVector2D.X < -ThresholdFloat));
	bool ValidImag = ((InputVector2D.Y > ThresholdFloat) || (InputVector2D.Y < -ThresholdFloat));
	bool NegReal = InputVector2D.X < 0;
	bool NegImag = InputVector2D.Y < 0;
	if (ValidReal && ValidImag) {
		//if (NegReal) {
		//	StringOutput.Append("-");
		//}
		StringOutput.Append(FString::SanitizeFloat(InputVector2D.X));
		if (NegImag) {
			//StringOutput.Append("-");
		}
		else {
			StringOutput.Append("+");
		}
		StringOutput.Append(FString::SanitizeFloat(InputVector2D.Y));
		StringOutput.Append("*i");
	}
	else if (ValidReal && !ValidImag) {
		//if (NegReal) {
		//	StringOutput.Append("-");
		//}
		StringOutput.Append(FString::SanitizeFloat(InputVector2D.X));
	}
	else if (!ValidReal && ValidImag) {
		//if (NegImag) {
		//	StringOutput.Append("-");
		//}
		StringOutput.Append(FString::SanitizeFloat(InputVector2D.Y));
		StringOutput.Append("*i");
	}
	else if (!ValidReal && !ValidImag) {
		StringOutput.Append("   0");; // FString::SanitizeFloat(0.0));
	}
	return StringOutput;
}
//const TMap<int32, FVector2D> FQuantumKet::DefaultQuantumKetAllZero = { {0, FVector2D(1.0,0.0)} };
FQuantumKet::FQuantumKet() { ; }
FQuantumKet::FQuantumKet(TMap<int32, FVector2D>& InputTMapKetSpace) {
	TMapKetSpace = InputTMapKetSpace;
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
FQuantumOperator::FQuantumOperator() { };
void FQuantumOperator::InitializeQuantumOperator(FQuantumGateSpecifier InputFQuantumGateSpecifier, uint8 InputQubitCount) {
	uint32 LocalHilbertSpaceDim = static_cast<int32>(static_cast<uint32>(1) << static_cast<uint32>(InputQubitCount));
	float LocalSqrtTwo = FMath::Sqrt(2.0);
	float LocalOneOverSqrtTwo = 1.0 / LocalSqrtTwo;
	uint32 LocalTargetQubit = static_cast<uint32>(
		InputFQuantumGateSpecifier.TargetQubitArray[0]);
	uint32 LocalControlQubit = static_cast<uint32>(
		InputFQuantumGateSpecifier.ControlQubitArray[0]);
	for (uint32 Index = 0; Index < LocalHilbertSpaceDim; Index++) {
		//uint64 CurrentHashUnchanged = FxnGetHash(Index, Index);
		uint32 IndexTargetBitFipped = ToggleBit(Index, LocalTargetQubit);
		//uint64 CurrentHashTargetBitFlipped = FxnGetHash(Index, IndexTargetBitFipped);
		FIntPoint CurrentHashUnchanged = FIntPoint(Index, Index);
		//FxnGetHash(Index, Index);
		FIntPoint CurrentHashTargetBitFlipped = FIntPoint(Index, IndexTargetBitFipped);

		////uint64 CurrentHashUnchanged = FxnGetHash(Index, Index);
		//uint32 IndexTargetBitFipped = ToggleBit(Index, LocalTargetQubit);
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
				TMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(1.0, 0.0));
				//if (bTargetQubit) {
				//	TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(1.0, 0.0));
				//}
				//else {
				//	TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(1.0, 0.0));
				//}
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
				//if (bTargetQubit) {
				//	TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(1.0, 0.0));
				//}
				//else {
				//	TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
				//}
			}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Hadamard) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(-LocalOneOverSqrtTwo, 0.0));
				TMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(LocalOneOverSqrtTwo, 0.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(LocalOneOverSqrtTwo, 0.0));
				TMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(LocalOneOverSqrtTwo, 0.0));
			}
			//if (bTargetQubit) {
			//	TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(LocalSqrtTwo, 0.0));
			//	TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-LocalSqrtTwo, 0.0));
			//}
			//else {
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(LocalSqrtTwo, 0.0));
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(LocalSqrtTwo, 0.0));
			//}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::X) {
			TMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(1.0, 0.0));
			//if (bTargetQubit) {
			//	//check(!TMapMatrixKetSpace.Contains(CurrentHashOneToZero));
			//	TMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(1.0, 0.0));
			//	//check(TMapMatrixKetSpace.Contains(CurrentHashOneToZero));
			//}
			//else {
			//	//check(!TMapMatrixKetSpace.Contains(CurrentHashZeroToOne));
			//	TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
			//	//check(TMapMatrixKetSpace.Contains(CurrentHashZeroToOne));
			//}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Y) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(0.0, 1.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashTargetBitFlipped, FVector2D(0.0, -1.0));
			}
			//if (bTargetQubit) {
			//	TMapMatrixKetSpace.Add(CurrentHashOneToZero, FVector2D(0.0, 1.0));
			//}
			//else {
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToOne, FVector2D(0.0, -1.0));
			//}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::Z) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(-1.0, 0.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
			}
			//if (bTargetQubit) {
			//	TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(-1.0, 0.0));
			//}
			//else {
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			//}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::S) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(0.0, 1.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
			}
			//if (bTargetQubit) {
			//	TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, 1.0));
			//}
			//else {
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			//}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::SDagger) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(0.0, -1.0));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
			}
			//if (bTargetQubit) {
			//	TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(0.0, -1.0));
			//}
			//else {
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			//}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::T) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(LocalOneOverSqrtTwo, LocalOneOverSqrtTwo));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
			}
			//if (bTargetQubit) {
			//	TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, LocalSqrtTwo));
			//}
			//else {
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			//}
		}
		else if (InputFQuantumGateSpecifier.EnumGateType == EQuantumGateType::TDagger) {
			if (bTargetQubit) {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(LocalOneOverSqrtTwo, -LocalOneOverSqrtTwo));
			}
			else {
				TMapMatrixKetSpace.Add(CurrentHashUnchanged, FVector2D(1.0, 0.0));
			}
			//if (bTargetQubit) {
			//	TMapMatrixKetSpace.Add(CurrentHashOneToOne, FVector2D(LocalSqrtTwo, -LocalSqrtTwo));
			//}
			//else {
			//	TMapMatrixKetSpace.Add(CurrentHashZeroToZero, FVector2D(1.0, 0.0));
			//}
		}
	}
	return;
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
	uint8 QubitMinGate = 0; // QuantumGateSpecifier.GetMinimumQubitsGateSpecifier();
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
	uint8 QubitMinOperator = 0; // QuantumGateSpecifier.GetMinimumQubitsGateSpecifier();
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
//void FQuantumOperatorApplied::UpdateForNewKet(TSharedPtr<FQuantumKet> InputPtrQuantumKetInitial, float InputErrorMargin) {
//void FQuantumOperatorApplied::UpdateForNewKet(FQuantumKet& InputRefQuantumKetInitial, float InputErrorMargin) {
//void FQuantumOperatorApplied::UpdateForNewKet(float InputErrorMargin) {
//	//WeakPtrQuantumKetInitial(InputPtrQuantumKetInitial);
//	//RefQuantumKetInitial = InputRefQuantumKetInitial;
//	//TMap<int32, FVector2D> InputPlaceHolder;
//	FQuantumKet InputQuantumKetEmpty = FQuantumKet();
//	UpdateForNewKet(InputQuantumKetEmpty, InputErrorMargin);
//	return;
//}
//void FQuantumOperatorApplied::UpdateForNewKet(TMap<int32,FVector2D> KetRHS, float InputErrorMargin) {
void FQuantumOperatorApplied::UpdateForNewKet(FQuantumKet& RefQuantumKetInitial, float InputErrorMargin) {
	TMap<FIntPoint, FVector2D>& MatrixLHS = TMapMatrixKetSpace;
	TMap<int32, FVector2D>& KetRHS = RefQuantumKetInitial.TMapKetSpace;
	TMap<FIntPoint, FVector2D>& MatrixResult = TMapMatrixAppliedToKetSpace;
	TMap<int32, FVector2D>& KetResult = FinalQuantumKet.TMapKetSpace;
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
	}
	return;
}
FQuantumOperatorApplied::FQuantumOperatorApplied() { };
FQuantumOperatorApplied::FQuantumOperatorApplied(
	FQuantumKet& InputRefQuantumKetInitial,
	FQuantumGateSpecifier InputQuantumGateSpecifier,
	uint8 InputQubitCount)
{
	InitializeQuantumOperator(InputQuantumGateSpecifier, InputQubitCount);
	UpdateForNewKet(InputRefQuantumKetInitial, 0.001);
}
UQuantumCircuit::UQuantumCircuit() {
	QubitCount = 0;
	HilbertSpaceDim = 1;
	InitialQuantumCircuitKet.TMapKetSpace.Add(0, FVector2D(1.0, 0.0));
}
// Completely empties gate array
int32 UQuantumCircuit::ResetQuantumCircuit() {
	CurrentGates.Empty();
	return 0;
}
// Clears all gates and builds circuit based on an input array of gate specifiers
// NOTE: Right now default behavior is to use the minimum number of qubits possible
int32 UQuantumCircuit::InitializeQuantumCircuit(const TArray<FQuantumGateSpecifier>& InputGateSpecifierList) {
	ResetQuantumCircuit();
	QubitCount = 0;
	uint8 LocalQubitCount = 0;
	for (auto iter : InputGateSpecifierList) {
		uint8 SubLocalQubitCount = iter.GetMinimumQubitsGateSpecifier();
		if (LocalQubitCount < SubLocalQubitCount) {
			LocalQubitCount = SubLocalQubitCount;
		}
	}
	if (LocalQubitCount >= 0 && LocalQubitCount < 16) {
		QubitCount = LocalQubitCount;
		HilbertSpaceDim = static_cast<int32>(static_cast<uint32>(1) << QubitCount);
		for (auto iter : InputGateSpecifierList) {
			AddQuantumCircuitGate(iter);
		}
	}
	return 0;
}
// Returns positive index value if successful, and "-1" if unsuccessful
int32 UQuantumCircuit::AddQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier) {
	int32 ReturnIndexValue = -1;
	if (CurrentGates.Num() == 0) {
		FQuantumOperatorApplied LocalQuantumOperatorApplied =
			FQuantumOperatorApplied(InitialQuantumCircuitKet, InputQuantumGateSpecifier, QubitCount);
		ReturnIndexValue = CurrentGates.Add(LocalQuantumOperatorApplied);
	}
	else if (InputQuantumGateSpecifier.GetMinimumQubitsGateSpecifier() <= QubitCount) {
		//FQuantumKet* LocalPtrQuantumKet = &(CurrentGates.Last().FinalQuantumKet);
		//FQuantumOperatorApplied LocalQuantumOperatorApplied =
		//	FQuantumOperatorApplied(LocalPtrQuantumKet, InputQuantumGateSpecifier, QubitCount);
		FQuantumOperatorApplied LocalQuantumOperatorApplied =
			FQuantumOperatorApplied(CurrentGates.Last().FinalQuantumKet, InputQuantumGateSpecifier, QubitCount);
		ReturnIndexValue = CurrentGates.Add(LocalQuantumOperatorApplied);
	}
	return ReturnIndexValue;
}
// Returns positive index value if successful, and "-1" if unsuccessful
int32 UQuantumCircuit::InsertQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition) {
	int32 ReturnIndexValue = -1;
	if (InputGatePosition >= 0 && InputGatePosition < CurrentGates.Num()) {
		//FQuantumKet* LocalPtrQuantumKet = &(CurrentGates[InputGatePosition - 1].FinalQuantumKet);
		//FQuantumOperatorApplied LocalQuantumOperatorApplied =
		//	FQuantumOperatorApplied(LocalPtrQuantumKet, InputQuantumGateSpecifier, QubitCount);
		if (InputGatePosition == 0) {

		}
		else {
			FQuantumOperatorApplied LocalQuantumOperatorApplied =
				FQuantumOperatorApplied(CurrentGates[InputGatePosition - 1].FinalQuantumKet, InputQuantumGateSpecifier, QubitCount);
			ReturnIndexValue = CurrentGates.Insert(LocalQuantumOperatorApplied, InputGatePosition);
		}
		for (int32 CurrentGateIndex = InputGatePosition + 1; CurrentGateIndex < CurrentGates.Num(); CurrentGateIndex++) {
			//FQuantumKet* SubLocalPtrQuantumKet = &(CurrentGates[CurrentGateIndex - 1].FinalQuantumKet);
			//CurrentGates[CurrentGateIndex].UpdateForNewKet(SubLocalPtrQuantumKet, 0.001);
			CurrentGates[CurrentGateIndex].UpdateForNewKet(CurrentGates[CurrentGateIndex - 1].FinalQuantumKet, 0.001);
		}
	}
	else if (InputGatePosition >= CurrentGates.Num()) {
		ReturnIndexValue = AddQuantumCircuitGate(InputQuantumGateSpecifier);
	}
	return ReturnIndexValue;
}
TArray<FString> UQuantumCircuit::GetIndex(int32 InputIndex) {
	TArray<FString> StringArrayOutput;
	if (InputIndex < CurrentGates.Num()) {
		for (int32 LocalIndexFrom = 0; LocalIndexFrom < HilbertSpaceDim; LocalIndexFrom++) {
			FString StringOutput = FString("");
			for (int32 LocalIndexTo = 0; LocalIndexTo < HilbertSpaceDim; LocalIndexTo++) {
				if (LocalIndexTo > 0) {
					StringOutput.Append(",");
				}
				FIntPoint LocalFIntPointKey = FIntPoint(LocalIndexFrom, LocalIndexTo);
				FVector2D LocalFVector2D;
				if (CurrentGates[InputIndex].TMapMatrixKetSpace.Contains(LocalFIntPointKey)) {
					StringOutput.Append(FxnGetFStringComplexNumber(CurrentGates[InputIndex].TMapMatrixKetSpace[LocalFIntPointKey]));
				}
				else {
					StringOutput.Append(FxnGetFStringComplexNumber(FVector2D(0.0, 0.0)));
				}
				//	float ThresholdFloat = FMath::Abs(0.001 / static_cast<float>(HilbertSpaceDim));
				//	bool ValidReal = (LocalFVector2D.X > ThresholdFloat);
				//	bool ValidImag = (LocalFVector2D.Y > ThresholdFloat);
				//	bool NegReal = LocalFVector2D.X < 0;
				//	bool NegImag = LocalFVector2D.Y < 0;
				//	if (ValidReal && ValidImag) {
				//		if (NegReal) {
				//			StringOutput.Append("-");
				//		}
				//		StringOutput.Append(FString::SanitizeFloat(LocalFVector2D.X));
				//		if (NegImag) {
				//			StringOutput.Append("-");
				//		}
				//		else {
				//			StringOutput.Append("+");
				//		}
				//		StringOutput.Append(FString::SanitizeFloat(LocalFVector2D.Y));
				//		StringOutput.Append("*i");
				//	}
				//	else if (ValidReal && !ValidImag) {
				//		if (NegReal) {
				//			StringOutput.Append("-");
				//		}
				//		StringOutput.Append(FString::SanitizeFloat(LocalFVector2D.X));
				//	}
				//	else if (!ValidReal && ValidImag) {
				//		if (NegImag) {
				//			StringOutput.Append("-");
				//		}
				//		StringOutput.Append(FString::SanitizeFloat(LocalFVector2D.Y));
				//		StringOutput.Append("*i");
				//	}
				//	else if (!ValidReal && !ValidImag) {
				//		StringOutput.Append("   0");; // FString::SanitizeFloat(0.0));
				//	}
			}
			StringArrayOutput.Add(StringOutput);
		}
	}
	return StringArrayOutput;
}
// Completely empties gate array
int32 UQuantumCircuit::FxnResetQuantumCircuit_Implementation() {
	return ResetQuantumCircuit();
	//CurrentGates.Empty();
	//return 0;
}
//// Clears all gates and builds circuit based on an input array of gate specifiers
//// NOTE: Right now default behavior is to use the minimum number of qubits possible
int32 UQuantumCircuit::FxnInitializeQuantumCircuit_Implementation(const TArray<FQuantumGateSpecifier>& InputGateSpecifierList) {
	return InitializeQuantumCircuit(InputGateSpecifierList);
	//FxnResetQuantumCircuit_Implementation();
	//QubitCount = 0;
	//uint8 LocalQubitCount = 0;
	//for (auto iter : InputGateSpecifierList) {
	//	uint8 SubLocalQubitCount = iter.GetMinimumQubitsGateSpecifier();
	//	if (LocalQubitCount < SubLocalQubitCount) {
	//		LocalQubitCount = SubLocalQubitCount;
	//	}
	//}
	//if (LocalQubitCount >= 0 && LocalQubitCount < 16) {
	//	QubitCount = LocalQubitCount;
	//	HilbertSpaceDim = static_cast<int32>(static_cast<uint32>(1) << QubitCount);
	//	for (auto iter : InputGateSpecifierList) {
	//		FxnAddQuantumCircuitGate_Implementation(iter);
	//	}
	//}
	//return 0;
}
// Returns positive index value if successful, and "-1" if unsuccessful
int32 UQuantumCircuit::FxnAddQuantumCircuitGate_Implementation(FQuantumGateSpecifier InputQuantumGateSpecifier)
{
	return AddQuantumCircuitGate(InputQuantumGateSpecifier);
	//int32 ReturnIndexValue = -1;
	//if (CurrentGates.Num() == 0) {
	//	FQuantumOperatorApplied LocalQuantumOperatorApplied =
	//		FQuantumOperatorApplied(InitialQuantumCircuitKet, InputQuantumGateSpecifier, QubitCount);
	//	ReturnIndexValue = CurrentGates.Add(LocalQuantumOperatorApplied);
	//}
	//else if (InputQuantumGateSpecifier.GetMinimumQubitsGateSpecifier() <= QubitCount) {
	//	//FQuantumKet* LocalPtrQuantumKet = &(CurrentGates.Last().FinalQuantumKet);
	//	//FQuantumOperatorApplied LocalQuantumOperatorApplied =
	//	//	FQuantumOperatorApplied(LocalPtrQuantumKet, InputQuantumGateSpecifier, QubitCount);
	//	FQuantumOperatorApplied LocalQuantumOperatorApplied =
	//		FQuantumOperatorApplied(CurrentGates.Last().FinalQuantumKet, InputQuantumGateSpecifier, QubitCount);
	//	ReturnIndexValue = CurrentGates.Add(LocalQuantumOperatorApplied);
	//}
	//return ReturnIndexValue;
	////return 1;
}
// Returns positive index value if successful, and "-1" if unsuccessful
int32 UQuantumCircuit::FxnInsertQuantumCircuitGate_Implementation(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition) {
	return InsertQuantumCircuitGate(InputQuantumGateSpecifier, InputGatePosition);
}


TMap< FIntPoint, FVector2D > UQuantumCircuit::FxnGetRefMatrixOperatorAtIndex_Implementation(int32 InputIndex) {
	return CurrentGates[InputIndex].TMapMatrixKetSpace;
	//const TMap< FIntPoint, FVector2D >& OutputRef = CurrentGates[InputIndex].TMapMatrixKetSpace;
	////return const_cast<const TMap< FIntPoint, FVector2D >&>(CurrentGates[InputIndex].TMapMatrixKetSpace);
	//return OutputRef;
}
TMap< FIntPoint, FVector2D > UQuantumCircuit::FxnGetRefMatrixOperatorAppliedAtIndex_Implementation(int32 InputIndex) {
	return CurrentGates[InputIndex].TMapMatrixAppliedToKetSpace;
	//return const_cast<const TMap< FIntPoint, FVector2D >&>(CurrentGates[InputIndex].TMapMatrixAppliedToKetSpace);
}
TMap< int32, FVector2D > UQuantumCircuit::FxnGetRefInitialKetAtIndex_Implementation(int32 InputIndex) {
	if (InputIndex == 0)
	{
		return InitialQuantumCircuitKet.TMapKetSpace;
	}
	else if (CurrentGates.IsValidIndex(InputIndex - 1)) {
		return CurrentGates[InputIndex - 1].FinalQuantumKet.TMapKetSpace;
	}
	else {
		TMap<int32, FVector2D> EmptyKetMap;
		return EmptyKetMap;
	}
}
