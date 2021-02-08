// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "QuantumGateType.generated.h"

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
struct FQuantumGateSpecifier
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EQuantumGateType EnumGateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 ControlQubit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 TargetQubit;
	uint8 GetMinimumQubitsGateSpecifier() {
		uint8 LocalValue;
		if (EnumGateType == EQuantumGateType::CX) {
			if (ControlQubit > TargetQubit) {
				LocalValue = ControlQubit + 1;
			}
			else {
				LocalValue = TargetQubit + 1;
			}
		}
		else if (EnumGateType == EQuantumGateType::CustomUnitary || EnumGateType == EQuantumGateType::Identity) {
			LocalValue = 0;
		}
		else {
			LocalValue = TargetQubit + 1;
		}
		return LocalValue;
	}
};
