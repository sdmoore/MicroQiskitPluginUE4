//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "QuantumGate.generated.h"
//
/////**
//// * 
//// */
////
//UENUM(BlueprintType)
//enum class EQuantumGateType : uint8
//{
//    Hadamard,
//    X,
//    Y,
//    Z,
//    T,
//    TDagger,
//    S,
//    SDagger,
//    CX,
//};
//USTRUCT(BlueprintType)
//struct FQuantumGate
//{
//    GENERATED_BODY()
//public:
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidGateFlag;
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
//};
//UCLASS(BlueprintType)
//class MICROQISKITUNREALENGINE_API UQuantumGate : public UObject
//{
//    GENERATED_BODY()
//	UQuantumKet();
//	const EQuantumGateType EnumGateType;
//    const TArray<int32> ControlQubits;
//    const int32 TargetQubit;
//    const int32 QubitCount;
//};
////
////UENUM(BlueprintType)
////enum class EQuantumGateType : uint8
////{
////    Hadamard,
////    X,
////    Y,
////    Z,
////    T,
////    TDagger,
////    S,
////    SDagger,
////    CX,
////};
////USTRUCT(BlueprintType)
////struct FQuantumGate
////{
////    GENERATED_BODY()
////public:
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool ValidGateFlag;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) EQuantumGateType EnumGateType;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 ControlQubit;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 TargetQubit;
////    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount;
////};