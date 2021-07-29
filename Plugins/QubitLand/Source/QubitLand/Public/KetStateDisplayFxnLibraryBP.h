//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Kismet/BlueprintFunctionLibrary.h"
//#include "KetStateDisplayFxnLibraryBP.generated.h"
//
///**
// * 
// */
//
//USTRUCT()
//struct FQuantumKetDisplayParameters
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) EQuantumGateType EnumGateType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 QubitCount;
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 ControlQubit;
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 TargetQubit;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<uint8> ControlQubitArray;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<uint8> TargetQubitArray;
//	FQuantumGateSpecifier();
//	int32 InitializeQuantumGate(EQuantumGateType InputGateType, uint8 InputQubitCount, TArray<uint8> InputControlQubitArray, TArray<uint8> InputTargetQubitArray);
//	//	: EnumGateType{ InputGateType }, QubitCount{ InputQubitCount }, ControlQubitArray{ InputControlQubitArray }, TargetQubitArray{ InputTargetQubitArray }
//	//{
//	//	for (auto& iter : ControlQubitArray) {
//	//		if (iter >= QubitCount) {
//	//			EnumGateType = EQuantumGateType::Invalid;
//	//		}
//	//	}
//	//	for (auto& iter : TargetQubitArray) {
//	//		if (iter >= QubitCount) {
//	//			EnumGateType = EQuantumGateType::Invalid;
//	//		}
//	//	}
//	//}
//	uint8 GetMinimumQubitsGateSpecifier();
//	//{
//	//	if (ControlQubitArray.Max() > TargetQubitArray.Max()) {
//	//		LocalValue = ControlQubitArray[0];
//	//	}
//	//	uint8 LocalValue;
//	//	if (EnumGateType == EQuantumGateType::CX) {
//	//		if (ControlQubitArray[0] > TargetQubitArray[0]) {
//	//			LocalValue = ControlQubit + 1;
//	//		}
//	//		else {
//	//			LocalValue = TargetQubit + 1;
//	//		}
//	//	}
//	//	else if (EnumGateType == EQuantumGateType::CustomUnitary || EnumGateType == EQuantumGateType::Identity) {
//	//		LocalValue = 0;
//	//	}
//	//	else {
//	//		LocalValue = TargetQubitArray[0] + 1;
//	//	}
//	//	return LocalValue;
//	//}
//};
//USTRUCT()
//struct FQuantumKetDisplaySettings
//{
//	GENERATED_BODY()
//public:
//	float DistanceOfOperation;
//	float DistanceOfStates;
//	float ProportionOfOperationDistanceForStates;
//	float ProportionOfOperationDistanceForSubstates;
//	float ProportionOfStateDistanceForStateAndSubstates;
//	float ProportionOfSubstateDistanceForSubstates;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) EQuantumGateType EnumGateType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 QubitCount;
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 ControlQubit;
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 TargetQubit;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<uint8> ControlQubitArray;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<uint8> TargetQubitArray;
//	FQuantumGateSpecifier();
//	int32 InitializeQuantumGate(EQuantumGateType InputGateType, uint8 InputQubitCount, TArray<uint8> InputControlQubitArray, TArray<uint8> InputTargetQubitArray);
//	//	: EnumGateType{ InputGateType }, QubitCount{ InputQubitCount }, ControlQubitArray{ InputControlQubitArray }, TargetQubitArray{ InputTargetQubitArray }
//	//{
//	//	for (auto& iter : ControlQubitArray) {
//	//		if (iter >= QubitCount) {
//	//			EnumGateType = EQuantumGateType::Invalid;
//	//		}
//	//	}
//	//	for (auto& iter : TargetQubitArray) {
//	//		if (iter >= QubitCount) {
//	//			EnumGateType = EQuantumGateType::Invalid;
//	//		}
//	//	}
//	//}
//	uint8 GetMinimumQubitsGateSpecifier();
//	//{
//	//	if (ControlQubitArray.Max() > TargetQubitArray.Max()) {
//	//		LocalValue = ControlQubitArray[0];
//	//	}
//	//	uint8 LocalValue;
//	//	if (EnumGateType == EQuantumGateType::CX) {
//	//		if (ControlQubitArray[0] > TargetQubitArray[0]) {
//	//			LocalValue = ControlQubit + 1;
//	//		}
//	//		else {
//	//			LocalValue = TargetQubit + 1;
//	//		}
//	//	}
//	//	else if (EnumGateType == EQuantumGateType::CustomUnitary || EnumGateType == EQuantumGateType::Identity) {
//	//		LocalValue = 0;
//	//	}
//	//	else {
//	//		LocalValue = TargetQubitArray[0] + 1;
//	//	}
//	//	return LocalValue;
//	//}
//};
//
//UCLASS()
//class QUBITLAND_API UKetStateDisplayFxnLibraryBP : public UBlueprintFunctionLibrary
//{
//	GENERATED_BODY()
//	//FMath::CartesianToPolar()
//};
