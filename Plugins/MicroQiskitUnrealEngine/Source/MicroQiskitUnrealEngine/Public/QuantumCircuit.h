//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "QuantumCircuit.generated.h"
//
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
//
////UENUM(BlueprintType)
////enum class EQuantumGateType : uint8;
////{
////	Hadamard,
////	X,
////	Y,
////	Z,
////	T,
////	TDagger,
////	S,
////	SDagger,
////	CX,
////};
//USTRUCT(BlueprintType)
//struct FQuantumGate;
////{
////	GENERATED_BODY()
////public:
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidGateFlag;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
////};
//
//
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
