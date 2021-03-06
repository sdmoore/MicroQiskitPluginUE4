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
#include "Math/UnrealMathUtility.h"
#include "UObject/NoExportTypes.h"
#include "QuantumGateType.h"
#include "QuantumCircuitInterface.h"
#include "QuantumCircuit.generated.h"

USTRUCT(BlueprintType)
struct FQuantumKet
{
	GENERATED_BODY()
public:
	//const static TMap<int32, FVector2D> DefaultQuantumKetAllZero;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<int32, FVector2D> TMapKetSpace;
	FQuantumKet();
	FQuantumKet(TMap<int32, FVector2D>& InputTMapKetSpace);
	uint8 GetMinimumQubitsKet();
};

USTRUCT(BlueprintType)
struct FQuantumOperator
{
	GENERATED_BODY()
public:
	uint8 GetMinimumQubitsOperator();
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FQuantumGateSpecifier QuantumGateSpecifier;
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
	//static FQuantumKet DefaultQuantumKetInitial;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap<FIntPoint, FVector2D> TMapMatrixAppliedToKetSpace;
	//FQuantumKet& RefQuantumKetInitial;
	//TWeakPtr<FQuantumKet> WeakPtrQuantumKetInitial;
	//TSharedPtr<FQuantumKet> FinalQuantumKet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FQuantumKet FinalQuantumKet;
	FQuantumOperatorApplied();
	//FQuantumOperatorApplied(TSharedPtr<FQuantumKet> InputPtrQuantumKetInitial, FQuantumGateSpecifier InputQuantumGateSpecifier, uint8 InputQubitCount);
	FQuantumOperatorApplied(FQuantumKet& InputRefQuantumKetInitial, FQuantumGateSpecifier InputQuantumGateSpecifier, uint8 InputQubitCount);
	//void UpdateForNewKet(float InputErrorMargin);
	//void UpdateForNewKet(TSharedPtr<FQuantumKet> InputPtrQuantumKetInitial, float InputErrorMargin);
	void UpdateForNewKet(FQuantumKet& InputRefQuantumKetInitial, float InputErrorMargin);
	uint8 GetMinimumQubitsOperatorApplied();
};
UCLASS(BlueprintType)
class QUBITLAND_API UQuantumCircuit : public UObject, public IQuantumCircuitInterface
{
	GENERATED_BODY()
public:
	//TSharedPtr<FQuantumKet> InitialQuantumKet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FQuantumKet InitialQuantumCircuitKet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) uint8 QubitCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int32 HilbertSpaceDim = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< FQuantumOperatorApplied > CurrentGates;
	//TMap< FIntPoint, FVector2D > OutputSet; // OperatorsOutput();
	UQuantumCircuit();
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") TArray<FString> GetIndex(int32 InputIndex);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing") FString FxnGetFStringComplexNumber(FVector2D InputVector2D);
	/**
	 * BEGIN INTERFACE FUNCTIONS
	 * FOR QUANTUM CIRCUIT
	 * THAT USE BLUEPRINTNATIVEEVENT
	 */
	//// Returns operator matrix directly by a const/read-only TMap reference
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//	void FxnGetRefMatrixOperatorAtIndex(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput);
	//virtual void FxnGetRefMatrixOperatorAtIndex(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput) override;
	//// Returns operator matrix contributions directly by a const/read-only TMap reference
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//	void FxnGetRefMatrixOperatorAppliedAtIndex(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput);
	//virtual void FxnGetRefMatrixOperatorAppliedAtIndex(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput) override;
	//// Returns ket vector directly by a const/read-only TMap reference
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//	void FxnGetRefInitialKetAtIndex(int32 InputIndex, const TMap< int32, FVector2D >& RefOutput);
	//virtual void FxnGetRefInitialKetAtIndex(int32 InputIndex, const TMap< int32, FVector2D >& RefOutput) override;


	virtual int32 FxnAddQuantumCircuitGate_Implementation(FQuantumGateSpecifier InputQuantumGateSpecifier) override;
	virtual int32 FxnInsertQuantumCircuitGate_Implementation(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition) override;
	virtual int32 FxnResetQuantumCircuit_Implementation() override;
	virtual int32 FxnInitializeQuantumCircuit_Implementation(const TArray<FQuantumGateSpecifier>& InputGateSpecifierList) override;
	virtual TMap< FIntPoint, FVector2D > FxnGetRefMatrixOperatorAtIndex_Implementation(int32 InputIndex) override;
	virtual TMap< FIntPoint, FVector2D > FxnGetRefMatrixOperatorAppliedAtIndex_Implementation(int32 InputIndex) override;
	virtual TMap< int32, FVector2D > FxnGetRefInitialKetAtIndex_Implementation(int32 InputIndex) override;

	// Returns positive index value if successful, and "-1" if unsuccessful
	int32 AddQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier);
	
	// Returns positive index value if successful, and "-1" if unsuccessful
	int32 InsertQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition) ;

	// Completely empties gate array
	int32 ResetQuantumCircuit();

	//// Clears all gates and builds circuit based on an input array of gate specifiers
	int32 InitializeQuantumCircuit(const TArray<FQuantumGateSpecifier>& InputGateSpecifierList) ;





	///////**
	////// * BEGIN INTERFACE FUNCTIONS
	////// * FOR QUANTUM CIRCUIT
	////// * THAT USE BLUEPRINTNATIVEEVENT
	////// */
	////// //// Returns operator matrix directly by a const/read-only TMap reference
	////// //UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	////// //	void FxnGetRefMatrixOperatorAtIndex(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput);
	////// //virtual void FxnGetRefMatrixOperatorAtIndex_Implementation(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput) override;
	////// //// Returns operator matrix contributions directly by a const/read-only TMap reference
	////// //UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	////// //	void FxnGetRefMatrixOperatorAppliedAtIndex(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput);
	////// //virtual void FxnGetRefMatrixOperatorAppliedAtIndex_Implementation(int32 InputIndex, const TMap< FIntPoint, FVector2D >& RefOutput) override;
	////// //// Returns ket vector directly by a const/read-only TMap reference
	////// //UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	////// //	void FxnGetRefInitialKetAtIndex(int32 InputIndex, const TMap< int32, FVector2D >& RefOutput);
	////// //virtual void FxnGetRefInitialKetAtIndex_Implementation(int32 InputIndex, const TMap< int32, FVector2D >& RefOutput) override;
	//////
	////// // Returns positive index value if successful, and "-1" if unsuccessful
	////// //UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//////int32 AddQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier);
	//////virtual int32 AddQuantumCircuitGate_Implementation(FQuantumGateSpecifier InputQuantumGateSpecifier) override;
	//////
	//////// Returns positive index value if successful, and "-1" if unsuccessful
	//////UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//////	int32 InsertQuantumCircuitGate(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition);
	//////virtual int32 InsertQuantumCircuitGate_Implementation(FQuantumGateSpecifier InputQuantumGateSpecifier, int32 InputGatePosition);
	//////
	//////// Completely empties gate array
	//////UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//////	void ResetQuantumCircuit();
	//////virtual void ResetQuantumCircuit_Implementation();
	//////
	//////// Clears all gates and builds circuit based on an input array of gate specifiers
	//////// NOTE: Right now default behavior is to use the minimum number of qubits possible
	//////UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quantum Computing")
	//////	void InitializeQuantumCircuit(TArray<FQuantumGateSpecifier> InputGateSpecifierList);
	//////virtual void InitializeQuantumCircuit_Implementation(TArray<FQuantumGateSpecifier> InputGateSpecifierList);

};
