// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/NoExportTypes.h"
#include "QuantumCircuit.generated.h"


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
struct FQuantumKet
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<int32, FVector2D> TMapKetSpace;
	uint8 GetMinimumQubitsKet();
};

USTRUCT(BlueprintType)
struct FQuantumGateSpecifier
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
	uint8 GetMinimumQubitsGateSpecifier();
};
USTRUCT(BlueprintType)
struct FQuantumOperator
{
	GENERATED_BODY()
public:
	uint8 GetMinimumQubitsOperator();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FQuantumGateSpecifier QuantumGateSpecifier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<FIntPoint, FVector2D> TMapMatrixKetSpace;
	void InitializeQuantumOperator(FQuantumGateSpecifier InputFQuantumGateSpecifier, uint8 InputQubitCount);
	FQuantumOperator LeftSideMultiplyOperator(FQuantumOperator& InputQuantumOperator);
	FQuantumKet LeftSideMultiplyOperatorKet(FQuantumKet& InputQuantumKet);
	FQuantumOperator();
	FQuantumOperator(FQuantumGateSpecifier InputQuantumGateSpecifier, uint8 InputQubitCount);
};
USTRUCT(BlueprintType)
struct FQuantumOperatorApplied : public FQuantumOperator
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<FIntPoint, FVector2D> TMapMatrixAppliedToKetSpace;
	TWeakPtr<FQuantumKet> WeakPtrQuantumKetInitial;
	TSharedPtr<FQuantumKet> FinalQuantumKet;
	FQuantumOperatorApplied();
	FQuantumOperatorApplied(TSharedPtr<FQuantumKet> InputPtrQuantumKetInitial, FQuantumGateSpecifier InputQuantumGateSpecifier, uint8 InputQubitCount);
	void UpdateForNewKet(float InputErrorMargin);
	void UpdateForNewKet(TSharedPtr<FQuantumKet> InputPtrQuantumKetInitial, float InputErrorMargin);
	uint8 GetMinimumQubitsOperatorApplied();
};
UCLASS(BlueprintType)
class MICROQISKITUNREALENGINE_API UQuantumCircuit : public UObject
{
	GENERATED_BODY()
public:
	TSharedPtr<FQuantumKet> InitialQuantumKet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< FQuantumOperatorApplied > CurrentGates;
	UQuantumCircuit();
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") int32 AddQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") int32 InsertQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void ResetQuantumCircuit();
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") void InitializeQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList);
	
};
