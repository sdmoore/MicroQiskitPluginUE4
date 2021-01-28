// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/NoExportTypes.h"
#include "QuantumCircuit.generated.h"

///**
// * 
// */
////FVector2D FxnComplexMultiplyConjugate(FVector2D Input0, FVector2D Input1, bool ConjugateFlag1 = false)
////{
////    if (ConjugateFlag1)
////    {
////        return FVector2D(
////            Input0.X * Input1.X + Input0.Y * Input1.Y,
////            -Input0.X * Input1.Y + Input0.Y * Input1.X
////        );
////    }
////    else
////    {
////        return FVector2D(
////            Input0.X * Input1.X - Input0.Y * Input1.Y,
////            Input0.X * Input1.Y + Input0.Y * Input1.X
////        );
////    }
////}
//
////USTRUCT(BlueprintType)
////struct FQuantumKet
////{
////    GENERATED_BODY()
////public:
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidKetFlag;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<FVector2D> KetValues;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
////};
////USTRUCT(BlueprintType)
////struct FQuantumOperator
////{
////    GENERATED_BODY()
////public:
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidKetFlag;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<FIntPoint, FVector2D> OperatorValues;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidOperatorFlag;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
////};

UENUM(BlueprintType)
enum class EQuantumGateType : uint8
{
	Identity,
	Hadamard,
	X,
	Y,
	Z,
	T,
	TDagger,
	S,
	SDagger,
	CX,
	CustomUnitary,
};
USTRUCT(BlueprintType)
struct FQuantumGate {
	GENERATED_BODY()
public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidGateFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
	uint8 GetMinimumQubitsGateSpecifier();
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
};


//
//
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumCircuit : public UObject
//{
//    GENERATED_BODY()
//    //bool ValidIndex(int32 InputIndex);
//public:
//    //UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetRow(FQuantumGate InputQuantumGate);
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
//    //const uint32 QubitCount;
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<FQuantumGate> QuantumGateList;
//    //void AddCircuit(UQuantumCircuit);
//    //void AddGate(FQuantumGate);
//    //UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetRow(int32 InputFromIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//    //UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetConversionInputToOutputFrom(int32 InputToIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//    //UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumKet GetModifiedKet(FQuantumKet InputKet, int32 InputEndIndex = -1);
//    //UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumOperator GetOperatorSubset(int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//    UQuantumCircuit();
//    //UQuantumCircuit(TArray<FQuantumGate> InputGateList);
//    ~UQuantumCircuit();
//};






/**
 * 
 */
//UCLASS()
//class MICROQISKITUNREALENGINE_API UQuantumOperator : public UObject
//{
//	GENERATED_BODY()
//	
//};
//USTRUCT(BlueprintType)
//struct MICROQISKITUNREALENGINE_API FQuantumHilbertSpace {
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
USTRUCT(BlueprintType)
struct FQuantumKet
{
	GENERATED_BODY()
public:
	TMap<int32, FVector2D> TMapKetSpace;
	uint8 GetMinimumQubitsKet();
	//UQuantumKet();
	//UQuantumKet(int32 InputQubitCount);
	//UQuantumKet(FQuantumHilbertSpace InputQuantumHilbertSpaceOwning);
	//UQuantumKet(TMap<uint32, FVector2D>& InputTMapKetSpace, FQuantumHilbertSpace InputQuantumHilbertSpaceOwning);
};

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
USTRUCT(BlueprintType)
struct FQuantumGateSpecifier
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
	uint8 GetMinimumQubitsGateSpecifier();
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
};
USTRUCT(BlueprintType)
struct FQuantumOperator
{
	GENERATED_BODY()
public:
	//void ComplexMatrixMultiply(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint64, FVector2D>& MatrixRHS, TMap<uint64, FVector2D>& MatrixOutput);
	//void ComplexKetMultiply(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint32, FVector2D>& KetRHS, TMap<uint32, FVector2D>& KetResult);
	//void ComplexKetMultiplyFullData(TMap<uint64, FVector2D>& MatrixLHS, TMap<uint32, FVector2D>& KetRHS, TMap<uint64, FVector2D>& MatrixResult);
	uint8 GetMinimumQubitsOperator();
	//uint64 FxnGetHash(uint32 InputFromState, uint32 InputToState);
	//uint32 FxnGetInverseHashFromState(uint64 InputHash);
	//uint32 FxnGetInverseHashToState(uint64 InputHash);
	//TWeakObjectPtr<UQuantumHilbertSpace> WeakPtrUQuantumHilbertSpaceOwning;
	FQuantumGateSpecifier QuantumGateSpecifier;
	TMap<FIntPoint, FVector2D> TMapMatrixKetSpace;
	//TMap<uint64, FVector2D> TMapMatrixKetSpace;
	void InitializeQuantumOperator(FQuantumGateSpecifier InputFQuantumGateSpecifier, uint8 InputQubitCount);
	FQuantumOperator LeftSideMultiplyOperator(FQuantumOperator& InputQuantumOperator);
	FQuantumKet LeftSideMultiplyOperatorKet(FQuantumKet& InputQuantumKet);
	//UQuantumOperator(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
	FQuantumOperator();
	FQuantumOperator(FQuantumGateSpecifier InputQuantumGateSpecifier, uint8 InputQubitCount);
	//UQuantumOperator(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
	//UQuantumOperator(UQuantumOperator* OperatorLHS, UQuantumOperator* OperatorRHS, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
	//void GetChangedQuantumKet(UQuantumKet* InputQuantumKet, UQuantumKet* OutputQuantumKet);
	//void ProductWithOperatorPair(UQuantumOperator OperatorLHS, UQuantumOperator OperatorRHS, UQuantumOperator* OperatorResult, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
	//void LeftHandProductWithOperator(UQuantumOperator* OperatorRHS, UQuantumOperator* OperatorResult);
	//UQuantumOperator* RightHandProductWithOperator(UQuantumOperator OperatorLHS);
};
USTRUCT(BlueprintType)
struct FQuantumOperatorApplied : public FQuantumOperator
{
	GENERATED_BODY()
public:
	TMap<FIntPoint, FVector2D> TMapMatrixAppliedToKetSpace;
	FQuantumKet* PtrQuantumKetInitial;
	FQuantumKet FinalQuantumKet;
	//FQuantumOperatorApplied(FQuantumOperator* InputQuantumOperator);
	//FQuantumOperatorApplied LeftSideMultiplyOperatorApplied(FQuantumOperatorApplied& InputQuantumOperatorApplied);
	FQuantumOperatorApplied();
	FQuantumOperatorApplied(FQuantumKet* InputPtrQuantumKetInitial, FQuantumGateSpecifier InputQuantumGateSpecifier, uint8 InputQubitCount);
	void UpdateForNewKet(float InputErrorMargin);
	void UpdateForNewKet(FQuantumKet* InputPtrQuantumKetInitial, float InputErrorMargin);
	uint8 GetMinimumQubitsOperatorApplied();
	//UQuantumOperatorApplied();
	//UQuantumOperatorApplied(UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
	//UQuantumOperatorApplied(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
	//UQuantumOperatorApplied(FQuantumGateSpecifier InputQuantumGateSpecifier, UQuantumKet* InputQuantumKet, UQuantumHilbertSpace* InputQuantumHilbertSpaceOwning);
	////UQuantumOperatorApplied(UQuantumOperator* InputQuantumOperator, UQuantumKet* InputQuantumKet);
};
UCLASS(BlueprintType)
class MICROQISKITUNREALENGINE_API UQuantumCircuit : public UObject
{
	GENERATED_BODY()
public:
	void AppendGate(FQuantumGateSpecifier InputQuantumGateSpecifier);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UQuantumKet* InitialQuantumCircuitKet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< FQuantumOperatorApplied > CurrentGates;
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void GetOperatorSubset(UQuantumOperator* OutputOperator, int32 InputStartGateIndex, int32 InputEndGateIndex);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void GetOperatorAppliedSubset(UQuantumOperatorApplied* OutputOperatorApplied, int32 InputStartGateIndex, int32 InputEndGateIndex);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumKet* ApplyCircuitToKet(UQuantumKet* InputQuantumKet, InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void AddGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGateIndex = -1);
	UQuantumCircuit();
	void AddGate(FQuantumGateSpecifier InputQuantumGateSpecifier);
	void InitializeQuantumCircuit();
	void InitializeQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList);
	//UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, int32 InputQubitCount);
	//UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, UQuantumHilbertSpace InputQuantumHilbertSpace);
	//~UQuantumCircuit();
};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumUnitaryDisplay : public UQuantumCircuit
//{
//	GENERATED_BODY()
//	UQuantumOperator* GetOperatorSubset(int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//public:
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumOperator* > QuantumOperatorMapUpToIndex;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumOperator* > QuantumOperatorMapAfterIndex;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumGate*> CurrentGates;
//	UQuantumCircuit();
//	UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList, UQuantumHilbertSpace InputQuantumHilbertSpace);
//	//~UQuantumCircuit();
//};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumCircuitResult : public UObject
//{
//	GENERATED_BODY()
//	
//public:
//	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetFromState(FQuantumGateSpecifier InputQuantumGate);
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumKet*> CurrentGates;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap< UQuantumKet*> CurrentGates;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;
//	//const uint32 QubitCount;
//	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<FQuantumGateSpecifier> QuantumGateList;
//	//void AddCircuit(UQuantumCircuit);
//	//void AddGate(UQuantumGate);
//	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetFromState(int32 InputFromIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetConversionInputToOutputFrom(int32 InputToIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumKet GetModifiedKet(FQuantumKet InputKet, int32 InputEndIndex = -1);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumOperator GetOperatorSubset(int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
//	UQuantumCircuitResult();
//	UQuantumCircuitResult(TArray<FQuantumGateSpecifier> InputGateList, int32 InputQubitCount = 0);
//	//~UQuantumCircuitOperations();
//};