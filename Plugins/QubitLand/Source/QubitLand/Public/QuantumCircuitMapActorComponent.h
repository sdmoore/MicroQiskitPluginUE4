// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiMapIntegerActorComponent.h"
#include "QuantumLandBlueprintFxnLibrary.h"
#include "QuantumCircuitMapActorComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUBITLAND_API UQuantumCircuitMapActorComponent : public UMultiMapIntegerActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void InitializationOfQuantumCircuitMapsProcessed(
			UPARAM() int32 InputOperatorCount,
			UPARAM() int32 InputQubitCount,
			UPARAM() TMap<FIntVector, FVector2D> InputOperatorMatricesComplexNumbers,
			UPARAM() TMap<FIntVector, FVector2D> InputTransitionMatricesComplexNumbers,
			UPARAM() TMap<FIntPoint, FVector2D> InputInitialKetsComplexNumbers,
			UPARAM() float InputToleranceLevel);
	TMap<FIntVector, FVector2D> GetAllFromOperators(
		UPARAM(ref) TArray<FIntVector>& InputArray);
	TMap<FIntVector, FVector2D> GetAllFromTransitions(
		UPARAM(ref) TArray<FIntVector>& InputArray);
	TMap<FIntPoint, FVector2D> GetAllFromInitialKets(
		UPARAM(ref) TArray<FIntPoint>& InputArray);
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<int32, float> MapNormalizationTransitions;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<int32, float> MapNormalizationInitialKets;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<int32, int32> MapOperationsDenominatorPowerOfTwo;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<int32, int32> MapTransitionsDenominatorPowerOfTwo;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<int32, int32> MapInitialKetsDenominatorPowerOfTwo;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FVector2D> MapOperationsComplexNumbers;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FVector2D> MapTransitionsComplexNumbers;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntPoint, FVector2D> MapInitialKetComplexNumbers;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FQuantumDyadicComplexRadical> MapOperationsDyadic;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FQuantumDyadicComplexRadical> MapTransitionsDyadic;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntPoint, FQuantumDyadicComplexRadical> MapInitialKetsDyadic;
	FString GetStringDyadicDisplay(FQuantumDyadicComplexRadical& RefDyadicInput);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetIntVectorMapDyadicDisplay(
			UPARAM() FString NameDyadicMap,
			UPARAM(ref) TMap < FIntVector, FQuantumDyadicComplexRadical>& DyadicMapInput,
			TArray<FString>& OutputStringList);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetIntPointMapDyadicDisplay(
			UPARAM() FString NameDyadicMap,
			UPARAM(ref) TMap < FIntPoint, FQuantumDyadicComplexRadical>& DyadicMapInput,
			TArray<FString>& OutputStringList);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetIntVectorMapComplexDisplay(
			UPARAM() FString NameDyadicMap,
			UPARAM(ref) TMap < FIntVector, FVector2D>& ComplexMapInput,
			TArray<FString>& OutputStringList);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetIntPointMapComplexDisplay(
			UPARAM() FString NameDyadicMap,
			UPARAM(ref) TMap < FIntPoint, FVector2D>& ComplexMapInput,
			TArray<FString>& OutputStringList);
	UFUNCTION(BlueprintCallable, Category = "Quantum Circuit Topology")
		void FxnGetAllMapsDisplay(
			TArray<FString>& OutputStringList);
};
