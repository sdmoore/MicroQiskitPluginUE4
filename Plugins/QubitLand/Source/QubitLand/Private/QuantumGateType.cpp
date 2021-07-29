
#include "QuantumGateType.h"

//FQuantumGateImplemented::FQuantumGateImplemented() {};


int32 FQuantumGateSpecifier::InitializeQuantumGate(EQuantumGateType InputGateType, uint8 InputQubitCount, TArray<uint8> InputControlQubitArray, TArray<uint8> InputTargetQubitArray)
{
	EnumGateType = InputGateType;
	QubitCount = InputQubitCount;
	ControlQubitArray = InputControlQubitArray;
	TargetQubitArray = InputTargetQubitArray;

	for (auto& iter : ControlQubitArray) {
		if (iter >= QubitCount) {
			EnumGateType = EQuantumGateType::Invalid;
		}
	}
	for (auto& iter : TargetQubitArray) {
		if (iter >= QubitCount) {
			EnumGateType = EQuantumGateType::Invalid;
		}
	}
	return 0;
}
FQuantumGateSpecifier::FQuantumGateSpecifier() {
	EnumGateType = EQuantumGateType::Invalid;
}
uint8 FQuantumGateSpecifier::GetMinimumQubitsGateSpecifier() {
	uint8 LocalValue = 0;
	if (EnumGateType == EQuantumGateType::CX) {
		if (ControlQubitArray[0] > TargetQubitArray[0]) {
			LocalValue = ControlQubitArray[0] + 1;
		}
		else {
			LocalValue = TargetQubitArray[0] + 1;
		}
	}
	else if (EnumGateType == EQuantumGateType::CustomUnitary || EnumGateType == EQuantumGateType::Identity) {
		LocalValue = 0;
	}
	else {
		LocalValue = TargetQubitArray[0] + 1;
	}
	return LocalValue;
}
//
//int32 FQuantumGateImplemented::InitializeQuantumGateImplemented(EQuantumGateType InputGateType, uint8 InputQubitCount, TArray<uint8> InputControlQubitArray, TArray<uint8> InputTargetQubitArray)
//	
//{
//	this->InitializeGateImplemented(InputGateType, InputQubitCount, InputControlQubitArray, InputTargetQubitArray);
//
//	return 0;
//}
