// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/Interface.h"
//#include "QuantumGateType.h"
//#include "QuantumCircuitDisplay.generated.h"
////enum class EQuantumGateType : uint8;
//// This class does not need to be modified.

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/NoExportTypes.h"
#include "QuantumGateType.h"
#include "QuantumCircuitDisplay.generated.h"

//UINTERFACE(MinimalAPI)
//class UQuantumCircuitDisplay : public UInterface
//{
//	GENERATED_BODY()
//};
//
///**
// * 
// */
//class QUBITLAND_API IQuantumCircuitDisplay
//{
//	GENERATED_BODY()
//
//	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
//public:
//	//virtual void CurrentOperatorDisplay(
//	//	TMap<FIntVector, FVector2D>& RefInputOperator,
//	//	TMap<FIntVector, FVector2D>& RefInputOperator, 
//	//	TMap<FIntPoint, FVector2D>& RefInputStartingKet);
//	//virtual TMap<FIntPoint, FVector2D> CurrentOperatorAppliedDisplay(int32 GateIndex);
//	//virtual TMap<FIntPoint, FVector2D> CurrentOperatorAppliedDisplay(int32 GateIndex);
//
//};
//USTRUCT(BlueprintType)
//struct FQuantumGateSpecifier;
//USTRUCT(BlueprintType)
//struct FCircuitDisplayGate
//{
//	GENERATED_BODY()
//public:
//	//const static TMap<int32, FVector2D> DefaultQuantumKetAllZero;
//	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FQuantumGateSpecifier CircuitDisplayGateSpecifier;
//	//TMap<FIntPoint,FVector2D>& RefCircuitDisplayGateOperatorValues;
//	//TMap<FIntPoint, FVector2D>& RefCircuitDisplayGateTransitionValues;
//	//TMap<int32, FVector2D>& RefCircuitDisplayGateFinalValues;
//	FCircuitDisplayGate() { ; };
//};
UCLASS(BlueprintType)
class QUBITLAND_API UQuantumCircuitDisplay : public UObject
{
	GENERATED_BODY()
public:
	//TSharedPtr<FQuantumKet> InitialQuantumKet;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<FIntPoint,FVector2D>& VariableName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim;

	//UFUNCTION() TMap< FIntVector, FVector2D > AllOperatorsOutput();
	//UFUNCTION() TMap< FIntPoint, FVector2D > AllStartingKetsOutput();
	UQuantumCircuitDisplay() { ; };
};
