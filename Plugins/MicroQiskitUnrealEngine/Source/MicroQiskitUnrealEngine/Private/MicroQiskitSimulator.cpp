// Fill out your copyright notice in the Description page of Project Settings.


#include "MicroQiskitSimulator.h"
const uint32 n_qubits_max = 8; // At most 8 qubits
void QuantumCircuitBasic::set_registers(uint32 n, uint32 m = 0) {
	n_qubits = n;
	n_bits = m;
}

void QuantumCircuitBasic::add(QuantumCircuitBasic qc2) {

	n_bits = FMath::Max(n_bits, qc2.n_bits);

	for (uint32 g = 0; g < uint32(qc2.data.Num()); g++) {
		data.Add(qc2.data[g]);
	}
}

void QuantumCircuitBasic::initialize(TArray<float> ket) {
	TArray<FString> gate;
	gate.Add("initialize");
	for (uint32 j = 0; j < (uint32)ket.Num(); j++) {
		gate.Add(/* */FString::SanitizeFloat(ket[j]));
	}
	QuantumCircuitElementBasic FinalGate = QuantumCircuitElementBasic(gate);
	data.Add(gate);
}
void QuantumCircuitBasic::x(uint32 q) {
	TArray<FString> gate;
	gate.Add("x");
	gate.Add(/* */FString::FromInt((int32)q));
	QuantumCircuitElementBasic FinalGate = QuantumCircuitElementBasic(gate);
	data.Add(gate);
}
void QuantumCircuitBasic::rx(float theta, uint32 q) {
	TArray<FString> gate;
	gate.Add("rx");
	gate.Add(/* */FString::SanitizeFloat(theta));
	gate.Add(/* */FString::FromInt((int32)q));
	QuantumCircuitElementBasic FinalGate = QuantumCircuitElementBasic(gate);
	data.Add(gate);
}
void QuantumCircuitBasic::h(uint32 q) {
	TArray<FString> gate;
	gate.Add("h");
	gate.Add(/* */FString::FromInt((int32)q));
	QuantumCircuitElementBasic FinalGate = QuantumCircuitElementBasic(gate);
	data.Add(gate);
}
void QuantumCircuitBasic::cx(uint32 s, uint32 t) {
	TArray<FString> gate;
	gate.Add("cx");
	gate.Add(/* */FString::FromInt((int32)s));
	gate.Add(/* */FString::FromInt((int32)t));
	QuantumCircuitElementBasic FinalGate = QuantumCircuitElementBasic(gate);
	data.Add(gate);
}
void QuantumCircuitBasic::measure(uint32 q, uint32 b) {
	TArray<FString> gate;
	gate.Add("m");
	gate.Add(/* */FString::FromInt((int32)b));
	gate.Add(/* */FString::FromInt((int32)q));
	QuantumCircuitElementBasic FinalGate = QuantumCircuitElementBasic(gate);
	data.Add(gate);
}
void QuantumCircuitBasic::rz(float theta, uint32 q) {
	h(q);
	rx(theta, q);
	h(q);
}
void QuantumCircuitBasic::ry(float theta, uint32 q) {
	rx(PI / 2, q);
	h(q);
	rx(theta, q);
	h(q);
	rx(-PI / 2, q);
}
void QuantumCircuitBasic::z(uint32 q) {
	rz(PI, q);
}
void QuantumCircuitBasic::y(uint32 q) {
	z(q);
	x(q);
}


TArray<FVector2D> MicroQiskitSimulator::SimulateCircuit(QuantumCircuitBasic qc) {
	//qc = qcInput;
	TArray<FVector2D> ket;

	for (uint32 j = 0; j < pow(2, qc.n_qubits); j++) {
		ket.Add(FVector2D((float)0.0, (float)0.0));
	}
	ket[0].X = 1.0;


	for (uint32 g = 0; g < (uint32)qc.data.Num(); g++) {

		if (qc.data[g].GateSpecifiers[0] == "initialize") {

			for (uint32 j = 0; j < pow(2, qc.n_qubits); j++) {
				ket[j].X = FCString::Atof(*(qc.data[g].GateSpecifiers[j + 1]));
			}

		}
		else if ((qc.data[g].GateSpecifiers[0] == "x") || (qc.data[g].GateSpecifiers[0] == "rx") || (qc.data[g].GateSpecifiers[0] == "h")) {

			uint32 q;
			q = (uint32)FCString::Atoi(*(qc.data[g].GateSpecifiers[qc.data[g].GateSpecifiers.Num() - 1]));
			uint32 Local_1UL = 1;
			for (uint32 i0 = 0; i0 < pow(2, q); i0++) {
				for (uint32 i1 = 0; i1 < pow(2, qc.n_qubits - q - 1); i1++) {
					uint32 b0, b1;
					//b0 = i0 + uint32(pow(2, q + 1)) * i1;
					b0 = i0 + uint32(Local_1UL << (q + 1)) * i1;
					//b1 = b0 + uint32(pow(2, q));
					b1 = b0 + uint32(Local_1UL << (q));

					FVector2D e0, e1;
					e0 = ket[b0];
					e1 = ket[b1];

					if (qc.data[g].GateSpecifiers[0] == "x") {
						ket[b0] = e1;
						ket[b1] = e0;
					}
					else if (qc.data[g].GateSpecifiers[0] == "rx") {
						float theta = FCString::Atof(*(qc.data[g].GateSpecifiers[1]));
						ket[b0].X = e0.X * cos(theta / 2) + e1.Y * sin(theta / 2);
						ket[b0].Y = e0.Y * cos(theta / 2) - e1.X * sin(theta / 2);
						ket[b1].X = e1.X * cos(theta / 2) + e0.Y * sin(theta / 2);
						ket[b1].Y = e1.Y * cos(theta / 2) - e0.X * sin(theta / 2);
					}
					else if (qc.data[g].GateSpecifiers[0] == "h") {
						ket[b0].X = (e0.X + e1.X) / sqrt(2);
						ket[b1].X = (e0.X - e1.X) / sqrt(2);
						ket[b0].Y = (e0.Y + e1.Y) / sqrt(2);
						ket[b1].Y = (e0.Y - e1.Y) / sqrt(2);
					}

				}
			}

		}
		else if (qc.data[g].GateSpecifiers[0] == "cx") {
			uint32 s, t, l, h;
			s = abs(FCString::Atoi(*(qc.data[g].GateSpecifiers[qc.data[g].GateSpecifiers.Num() - 2])));
			t = abs(FCString::Atoi(*(qc.data[g].GateSpecifiers[qc.data[g].GateSpecifiers.Num() - 1])));
			if (s > t) {
				h = s;
				l = t;
			}
			else {
				h = t;
				l = s;
			}

			for (uint32 i0 = 0; i0 < pow(2, l); i0++) {
				for (uint32 i1 = 0; i1 < pow(2, h - l - 1); i1++) {
					for (uint32 i2 = 0; i2 < pow(2, qc.n_qubits - h - 1); i2++) {

						uint32 b0, b1;
						b0 = i0 + pow(2, l + 1) * i1 + pow(2, h + 1) * i2 + pow(2, s);
						b1 = b0 + pow(2, t);

						FVector2D e0, e1;
						e0 = ket[b0];
						e1 = ket[b1];

						ket[b0] = e1;
						ket[b1] = e0;

					}
				}
			}

		}

	}

	return ket;

}

TArray<float> MicroQiskitSimulator::get_probs(QuantumCircuitBasic qc) {

	TArray<FVector2D> ket;
	ket = SimulateCircuit(qc);

	TArray<float> probs;
	for (uint32 j = 0; j < (uint32)ket.Num(); j++) {

		probs.Add(pow(ket[j].X, 2) + pow(ket[j].Y, 2));

	}

	return probs;

}


//MicroQiskitSimulator::MicroQiskitSimulator() {
//	shots = 1024;
//}

TArray<FVector2D> MicroQiskitSimulator::get_statevector(QuantumCircuitBasic qc) {

	TArray<FVector2D> ket;
	ket = SimulateCircuit(qc);

	TArray<FVector2D> complex_ket;
	for (uint32 j = 0; j < (uint32)ket.Num(); j++) {

		FVector2D e = FVector2D(ket[j].X, ket[j].Y);
		complex_ket.Add(e);

	}

	return complex_ket;

}

TArray<FString> MicroQiskitSimulator::get_memory(QuantumCircuitBasic qc) {

	TArray<float> probs;
	probs = get_probs(qc);

	TArray<FString> memory;

	for (uint32 s = 0; s < shots; s++) {

		float cumu = 0;
		bool un = true;
		float r = FMath::RandRange(float(0.0), float(1.0));
		TBitArray< FDefaultBitArrayAllocator> Local_TBitArray;
		for (uint32 j = 0; j < (uint32)probs.Num(); j++) {
			cumu += probs[j];
			if ((r < cumu) && un) {
				uint32 CurrentIndex = j;
				uint32 Local_1UL = 1;
				Local_TBitArray.Empty();
				for (uint32 LocalIndex = 0; LocalIndex < n_qubits_max; LocalIndex++) {
					bool LocalBit = (CurrentIndex >> LocalIndex) & Local_1UL;
					Local_TBitArray.Add(LocalBit);
				}
				FString FString_long_out_reverse_endian;
				for (uint32 LocalIndex = 0; LocalIndex < n_qubits_max; LocalIndex++) {
					if (Local_TBitArray[LocalIndex]) {
						FString_long_out_reverse_endian += '1';
					}
					else {
						FString_long_out_reverse_endian += '0';
					}
				}
				FString FString_long_out = FString_long_out_reverse_endian.Reverse();
				FString FString_out = FString_long_out.Mid(n_qubits_max - qc.n_qubits, n_qubits_max);
				memory.Add(FString_out);
				un = false;
			}
		}

	}

	return memory;

}

TMap<FString, uint32> MicroQiskitSimulator::get_counts(QuantumCircuitBasic qc) {

	TMap<FString, uint32>  counts;

	TArray<FString> memory = get_memory(qc);

	for (uint32 s = 0; s < shots; s++) {
		counts[memory[s]] += 1;
	}

	return counts;

}

FString MicroQiskitSimulator::get_qiskit(QuantumCircuitBasic qc) {

	FString qiskit_py;

	if (qc.n_bits == 0) {
		qiskit_py += "qc = QuantumCircuitBasic(" +/* */FString::FromInt(qc.n_qubits) + ")\n";
	}
	else {
		qiskit_py += "qc = QuantumCircuitBasic(" +/* */FString::FromInt(qc.n_qubits) + "," +/* */FString::FromInt(qc.n_bits) + ")\n";
	}

	for (uint32 g = 0; g < (uint32)qc.data.Num(); g++) {
		if (qc.data[g].GateSpecifiers[0] == "x") {
			qiskit_py += "qc.x(" + qc.data[g].GateSpecifiers[1] + ")\n";
		}
		else if (qc.data[g].GateSpecifiers[0] == "rx") {
			qiskit_py += "qc.rx(" + qc.data[g].GateSpecifiers[1] + "," + qc.data[g].GateSpecifiers[2] + ")\n";
		}
		else if (qc.data[g].GateSpecifiers[0] == "h") {
			qiskit_py += "qc.h(" + qc.data[g].GateSpecifiers[1] + ")\n";
		}
		else if (qc.data[g].GateSpecifiers[0] == "cx") {
			qiskit_py += "qc.cx(" + qc.data[g].GateSpecifiers[1] + "," + qc.data[g].GateSpecifiers[2] + ")\n";
		}
		else if (qc.data[g].GateSpecifiers[0] == "m") {
			qiskit_py += "qc.measure(" + qc.data[g].GateSpecifiers[1] + "," + qc.data[g].GateSpecifiers[2] + ")\n";
		}
	}

	return qiskit_py;

}
MicroQiskitSimulator::MicroQiskitSimulator()
{
	//void GetCircuitKet(TArray<FString> InputArrayOfCommaSeparatedGateValues) {
	//	//FCString::Mid('d');
	//}
}

MicroQiskitSimulator::~MicroQiskitSimulator()
{
}
