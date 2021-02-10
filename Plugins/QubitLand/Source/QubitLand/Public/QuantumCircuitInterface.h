//This program is free software : you can redistribute itand /or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.If not, see < https://www.gnu.org/licenses/>.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuantumGateType.h"
#include "QuantumCircuitInterface.generated.h"
//UENUM(BlueprintType)
//enum class EQuantumGateType : uint8;
// This class does not need to be modified.
//enum class EQuantumGateType : uint8;
UINTERFACE(MinimalAPI)
class UQuantumCircuitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QUBITLAND_API IQuantumCircuitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Returns operator matrix directly by a const/read-only TMap reference
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
		TMap< FIntPoint, FVector2D > FxnGetRefMatrixOperatorAtIndex(int32 InputIndex);
	// Returns operator matrix contributions directly by a const/read-only TMap reference
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
		TMap< FIntPoint, FVector2D > FxnGetRefMatrixOperatorAppliedAtIndex(int32 InputIndex);
	// Returns ket vector directly by a const/read-only TMap reference
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
		TMap< int32, FVector2D > FxnGetRefInitialKetAtIndex(int32 InputIndex);

	//// Returns positive index value if successful, and "-1" if unsuccessful
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
		int32 FxnAddQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier);
	//virtual int32 AddQuantumCircuitGate_Implementation(FQuantumGateSpecifier InputQuantumGateSpecifier) override;

	// Returns positive index value if successful, and "-1" if unsuccessful
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
		int32 FxnInsertQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition);

	// Completely empties gate array
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
		int32 FxnResetQuantumCircuit();

	// Completely empties gate array
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
		int32 FxnInitializeQuantumCircuit(const TArray<FQuantumGateSpecifier>& InputGateSpecifierList);

	//// Clears all gates and builds circuit based on an input array of gate specifiers
	//// NOTE: Right now default behavior is to use the minimum number of qubits possible
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//	int32 InterfaceInitializeQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList);
	//virtual int32 InterfaceInitializeQuantumCircuit_Implementation(TArray<FQuantumGateSpecifier> InputGateSpecifierList)  { return 0; };

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent) int32 AddGate();
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent) FString QiskitOutput();
	//virtual FString QiskitOutput();
	//virtual FString OpenQASMOutput();
	//virtual uint8 GetQubitCount();
	//virtual FVector2D GetFromToStateCircuit(int32 FromIndex, int32 ToIndex);
	//virtual TMap<FIntPoint, FVector2D> GetFromToStateCircuit(int32 FromIndex, int32 ToIndex);
	//virtual TMap<FIntPoint,FVector2D> GetFromToStateCircuitElement(int32 CircuitElementIndex);
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent) FString OpenQASMOutput();
};
