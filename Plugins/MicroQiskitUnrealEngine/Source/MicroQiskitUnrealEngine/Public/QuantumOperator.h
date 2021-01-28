//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Math/UnrealMathUtility.h"
//#include "UObject/NoExportTypes.h"
//#include "QuantumOperator.generated.h"
//
///**
// * 
// */
////UCLASS()
////class MICROQISKITUNREALENGINE_API UQuantumOperator : public UObject
////{
////	GENERATED_BODY()
////	
////};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumHilbertSpace : public UObject {
//	GENERATED_BODY()
//public:
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;
//	bool CheckHilbertSpace(UQuantumHilbertSpace* InputHilbertSpace) {
//		return (this->QubitCount == InputHilbertSpace->QubitCount);
//	}
//	UQuantumHilbertSpace() {
//		QubitCount = 0;
//		HilbertSpaceDim = 1;
//	}
//	void SetHilbertSpaceConstructorOnly(int32 InputNewQubitCount) {
//		if (InputNewQubitCount >= 0 && InputNewQubitCount < 16) {
//			QubitCount = InputNewQubitCount;
//			uint32 TempDim = 1;
//			HilbertSpaceDim = static_cast<int32>(FMath::Abs(TempDim << QubitCount));
//		}
//		else {
//			QubitCount = 0;
//			HilbertSpaceDim = 1;
//		}
//	}
//	UQuantumHilbertSpace(UQuantumHilbertSpace* InputQuantumHilbertSpace) {
//		QubitCount = InputQuantumHilbertSpace->QubitCount;
//		HilbertSpaceDim = InputQuantumHilbertSpace->HilbertSpaceDim;
//	}
//	UQuantumHilbertSpace(int32 InputQubitCount) {
//		if(InputQubitCount >= 0 && InputQubitCount<16) {
//			QubitCount = InputQubitCount;
//			uint32 TempDim = 1;
//			HilbertSpaceDim = static_cast<int32>(FMath::Abs(TempDim << QubitCount));
//		}
//		else {
//			QubitCount = 0;
//			HilbertSpaceDim = 1;
//		}
//	}
//};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumKet : public UQuantumHilbertSpace
//{
//	GENERATED_BODY()
//public:
//	TMap<uint32, FVector2D> TMapKetSpace;
//	UQuantumKet();
//	UQuantumKet(int32 InputQubitCount);
//	UQuantumKet(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	UQuantumKet(TMap<uint32, FVector2D>& InputTMapKetSpace, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//};
//
//UENUM(BlueprintType)
//enum class EQuantumGateType : uint8
//{
//	Identity,
//	Hadamard,
//	X,
//	Y,
//	Z,
//	T,
//	TDagger,
//	S,
//	SDagger,
//	CX,
//	CustomUnitary,
//};
//USTRUCT(BlueprintType)
//struct FQuantumGateSpecifier
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
//	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
//};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumOperator : public UQuantumHilbertSpace
//{
//	GENERATED_BODY()
//public:
//	void ComplexMatrixMultiply(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint64, FVector2D>& MatrixRHS, TMap<uint64, FVector2D>& MatrixOutput);
//	void ComplexKetMultiply(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint32, FVector2D>& KetRHS, TMap<uint32, FVector2D>& KetResult);
//	void ComplexKetMultiplyFullData(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint32, FVector2D>& KetRHS, TMap<uint64, FVector2D>& MatrixResult);
//	uint64 FxnGetHash(uint32 InputFromState, uint32 InputToState);
//	uint32 FxnGetInverseHashFromState(uint64 InputHash);
//	uint32 FxnGetInverseHashToState(uint64 InputHash);
//	TWeakObjectPtr<UQuantumHilbertSpace> WeakPtrUQuantumHilbertSpaceOwning;
//	TMap<uint64, FVector2D> TMapMatrixKetSpace;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FQuantumGateSpecifier QuantumGateSpecifier;
//	UQuantumOperator();
//	UQuantumOperator(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	UQuantumOperator(FQuantumGateSpecifier InputQuantumGateSpecifier);
//	UQuantumOperator(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	UQuantumOperator(UQuantumOperator* OperatorLHS, UQuantumOperator* OperatorRHS, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	void GetChangedQuantumKet(UQuantumKet* InputQuantumKet, UQuantumKet* OutputQuantumKet);
//	void ProductWithOperatorPair(UQuantumOperator OperatorLHS, UQuantumOperator OperatorRHS, UQuantumOperator* OperatorResult, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	void LeftHandProductWithOperator(UQuantumOperator* OperatorRHS, UQuantumOperator* OperatorResult);
//	//UQuantumOperator* RightHandProductWithOperator(UQuantumOperator OperatorLHS);
//};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumOperatorApplied : public UQuantumOperator
//{
//	GENERATED_BODY()
//public:
//	TMap<uint64, FVector2D> TMapMatrixAppliedToKetSpace;
//	TWeakObjectPtr<UQuantumKet> WeakPtrUQuantumKetInitial;
//	UQuantumKet* FinalQuantumKet;
//	UQuantumOperatorApplied(UQuantumOperator* InputQuantumOperator);
//	void UpdateForNewKet();
//	UQuantumOperatorApplied();
//	UQuantumOperatorApplied(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	UQuantumOperatorApplied(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	UQuantumOperatorApplied(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumKet* InputQuantumKet, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
//	//UQuantumOperatorApplied(UQuantumOperator* InputQuantumOperator, UQuantumKet* InputQuantumKet);
//};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumCircuit : public UQuantumHilbertSpace
//{
//	GENERATED_BODY()
//public:
//	void AppendGate(FQuantumGateSpecifier InputQuantumGateSpecifier);
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UQuantumKet* InitialQuantumCircuitKet;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumOperatorApplied*> CurrentGates;
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void GetOperatorSubset(UQuantumOperator* OutputOperator, int32 InputStartGateIndex, int32 InputEndGateIndex);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void GetOperatorAppliedSubset(UQuantumOperatorApplied* OutputOperatorApplied, int32 InputStartGateIndex, int32 InputEndGateIndex);
//	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumKet* ApplyCircuitToKet(UQuantumKet* InputQuantumKet, InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void AddGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGateIndex = -1);
//	UQuantumCircuit();
//	//UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList);
//	UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, int32 InputQubitCount);
//	//UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, UQuantumHilbertSpace InputQuantumHilbertSpace);
//	//~UQuantumCircuit();
//};
////UCLASS(BlueprintType)
////class MICROQISKITUNREALENGINE_API UQuantumUnitaryDisplay : public UQuantumCircuit
////{
////	GENERATED_BODY()
////	UQuantumOperator* GetOperatorSubset(int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
////public:
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumOperator* > QuantumOperatorMapUpToIndex;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumOperator* > QuantumOperatorMapAfterIndex;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumGate*> CurrentGates;
////	UQuantumCircuit();
////	UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, UQuantumHilbertSpace InputQuantumHilbertSpace);
////	//~UQuantumCircuit();
////};
////UCLASS(BlueprintType)
////class MICROQISKITUNREALENGINE_API UQuantumCircuitResult : public UObject
////{
////	GENERATED_BODY()
////	
////public:
////	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetFromState(FQuantumGateSpecifier InputQuantumGate);
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumKet*> CurrentGates;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap< UQuantumKet*> CurrentGates;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;
////	//const uint32 QubitCount;
////	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<FQuantumGateSpecifier> QuantumGateList;
////	//void AddCircuit(UQuantumCircuit);
////	//void AddGate(UQuantumGate);
////	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetFromState(int32 InputFromIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
////	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetConversionInputToOutputFrom(int32 InputToIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
////	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumKet GetModifiedKet(FQuantumKet InputKet, int32 InputEndIndex = -1);
////	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumOperator GetOperatorSubset(int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
////	UQuantumCircuitResult();
////	UQuantumCircuitResult(TArray<FQuantumGateSpecifier> InputGateList, int32 InputQubitCount = 0);
////	//~UQuantumCircuitOperations();
////};