// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class QuantumCircuitElementBasic {
public:
	TArray<FString> GateSpecifiers;
	//FString GetFStringAt(uint32 InputIndex) {
	//	return GateSpecifiers[InputIndex];
	//}
	QuantumCircuitElementBasic(TArray<FString> InputGateSpecifiers) {
		GateSpecifiers = InputGateSpecifiers;
	}
};
class QuantumCircuitBasic {

public:

	uint32 n_qubits, n_bits;
	TArray<QuantumCircuitElementBasic> data;
	void set_registers(uint32 n, uint32 m);
	void add(QuantumCircuitBasic qc2);
	void initialize(TArray<float> ket);
	void x(uint32 q);
	void rx(float theta, uint32 q);
	void h(uint32 q);
	void cx(uint32 s, uint32 t);
	void measure(uint32 q, uint32 b);
	void rz(float theta, uint32 q);
	void ry(float theta, uint32 q);
	void z(uint32 q);
	void y(uint32 q);

};

class MICROQISKITUNREALENGINE_API MicroQiskitSimulator 
{
	// Contains functions required to simulate a circuit and provide output data
	TArray<FVector2D> SimulateCircuit(QuantumCircuitBasic qc);

	TArray<float> get_probs(QuantumCircuitBasic qc);

public:
	uint32 shots;

	MicroQiskitSimulator();
	~MicroQiskitSimulator();
	TArray<FVector2D> get_statevector(QuantumCircuitBasic qc);

	TArray<FString> get_memory(QuantumCircuitBasic qc);

	TMap<FString, uint32> get_counts(QuantumCircuitBasic qc);
	
	FString get_qiskit(QuantumCircuitBasic qc);

};