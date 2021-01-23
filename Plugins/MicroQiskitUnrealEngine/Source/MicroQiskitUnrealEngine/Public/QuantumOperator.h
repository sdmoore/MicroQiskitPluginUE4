// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/NoExportTypes.h"
#include "QuantumOperator.generated.h"

/**
 * 
 */
//UCLASS()
//class MICROQISKITUNREALENGINE_API UQuantumOperator : public UObject
//{
//	GENERATED_BODY()
//	
//};
UENUM(BlueprintType)
enum class EQuantumGateType : uint8
{
	Hadamard,
	X,
	Y,
	Z,
	T,
	TDagger,
	S,
	SDagger,
	CX,
};
USTRUCT(BlueprintType)
struct FQuantumGateSpecifier
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
};
UCLASS(BlueprintType)
class MICROQISKITUNREALENGINE_API UQuantumOperator : public UObject
{
    GENERATED_BODY()
    TMap<uint64, FVector2D> TMapMatrixKetSpace;
    //uint64 FxnGetHash(int32 InputFromState, int32 InputToState) {
    //    uint64 uint64FromState, uint64ToState, Outputuint64;
    //    if (InputFromState < 0) uint64FromState = MAX_int32 - InputFromState;
    //    else uint64FromState = InputFromState;
    //    if (InputFromState < 0) uint64ToState = MAX_int32 - InputToState;
    //    else uint64ToState = InputToState;
    //    Outputuint64 = uint64FromState * MAX_uint32 + uint64ToState;
    //    return Outputuint64;
    //}
    //FIntPoint FxnGetInverseHash(uint64 InputHash) {
    //    FIntPoint OutputValue;
    //    uint64 uint64FromState, uint64ToState, Outputuint64;
    //    uint64FromState = InputHash / ((uint64)MAX_uint32);
    //    uint64ToState = InputHash % ((uint64)MAX_uint32);
    //    uint64 Outputuint64 = 0;
    //    if (uint64ToState > MAX_uint32) OutputValue.X = (int32)MAX_int32 - uint64FromState;
    //    else OutputValue.X = (int32)uint64ToState;
    //    if (uint64FromState > MAX_uint32) OutputValue.Y = (int32)MAX_int32 - uint64FromState;
    //    else OutputValue.Y = (int32)uint64FromState;
    //    return OutputValue;
    //}
    uint64 FxnGetHash(uint32 InputFromState, uint32 InputToState);
    uint32 FxnGetInverseHashFromState(uint64 InputHash);
    uint32 FxnGetInverseHashToState(uint64 InputHash);
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<FIntPoint, FVector2D> OperatorValues;
public:
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidOperatorFlag;
    uint8 QubitCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;
	//TMap<int32,FVector2D> GetFromStateToFinal(int32 InputFromStateIndex);
    //TArray<FVector2D> GetToStateFromInitial(int32 InputToStateIndex);
	UQuantumOperator();
	UQuantumOperator(FQuantumGateSpecifier);
    UQuantumOperator(UQuantumOperator OperatorLHS, UQuantumOperator OperatorRHS);
};
UCLASS(BlueprintType)
class MICROQISKITUNREALENGINE_API UQuantumGate : public UQuantumOperator
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FQuantumGateSpecifier QuantumGateID;
	UQuantumGate();
};

UCLASS(BlueprintType)
class MICROQISKITUNREALENGINE_API UQuantumCircuit : public UObject
{
	GENERATED_BODY()
		//bool ValidIndex(int32 InputIndex);
public:
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetFromState(FQuantumGateSpecifier InputQuantumGate);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< UQuantumGate*> CurrentGates;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;
	//const uint32 QubitCount;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<FQuantumGateSpecifier> QuantumGateList;
	//void AddCircuit(UQuantumCircuit);
	//void AddGate(UQuantumGate);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetFromState(int32 InputFromIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FVector2D> GetConversionInputToOutputFrom(int32 InputToIndex, int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumKet GetModifiedKet(FQuantumKet InputKet, int32 InputEndIndex = -1);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing") UQuantumOperator GetOperatorSubset(int32 InputStartGateIndex = 0, int32 InputEndGateIndex = -1);
	UQuantumCircuit();
	//UQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateList);
	//~UQuantumCircuit();
};
