//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Containers/Map.h"
//#include "UObject/NoExportTypes.h"
//#include "MultiMapIntegerObject.generated.h"
//
///**
// * 
// */
//UCLASS()
//class QUBITLAND_API UMultiMapIntegerObject : public UObject
//{
//	GENERATED_BODY()
//	// Sets default values for this component's properties
//public:
//	UMultiMapIntegerObject();
//	TMultiMap<int32, FIntVector> IndexToOperations;
//	TMultiMap<int32, FIntVector> IndexToTransitions;
//	TMultiMap<int32, FIntPoint> IndexToInitialKets;
//	TMultiMap<int32, FIntPoint> IndexToFinalKets;
//
//	TMultiMap<FIntPoint, int32> InitialKetToIndex;
//	TMultiMap<FIntPoint, FIntPoint> InitialKetToFinalKets;
//	TMultiMap<FIntPoint, FIntVector> InitialKetToOperators;
//	TMultiMap<FIntPoint, FIntVector> InitialKetToTransitions;
//
//	TMultiMap<FIntPoint, FIntPoint> FinalKetToInitialKets;
//	TMultiMap<FIntPoint, FIntVector> FinalKetToOperators;
//	TMultiMap<FIntPoint, FIntVector> FinalKetToTransitions;
//	TMultiMap<FIntPoint, int32> FinalKetToIndex;
//
//	TMultiMap<FIntVector, int32> OperationToIndex;
//	TMultiMap<FIntVector, FIntVector> OperationToTransitions;
//	TMultiMap<FIntVector, FIntPoint> OperationToInitialKets;
//	TMultiMap<FIntVector, FIntPoint> OperationToFinalKets;
//
//	TMultiMap<FIntVector, int32> TransitionToIndex;
//	TMultiMap<FIntVector, FIntVector> TransitionToOperations;
//	TMultiMap<FIntVector, FIntPoint> TransitionToInitialKets;
//	TMultiMap<FIntVector, FIntPoint> TransitionToFinalKets;
//	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntVector> OperatorMatrices;
//	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntVector> TransitionMatrices;
//	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TArray<FIntPoint> InitialKets;
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnIndexToOperations(
//			UPARAM() int32 Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnIndexToTransitions(
//			UPARAM() int32 Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnIndexToInitialKets(
//			UPARAM() int32 Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnIndexToFinalKets(
//			UPARAM() int32 Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnInitialKetToIndex(
//			UPARAM() FIntPoint Input,
//			TArray<int32> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnInitialKetToFinalKets(
//			UPARAM() FIntPoint Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnInitialKetToOperators(
//			UPARAM() FIntPoint Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnInitialKetToTransitions(
//			UPARAM() FIntPoint Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnFinalKetToInitialKets(
//			UPARAM() FIntPoint Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnFinalKetToOperators(
//			UPARAM() FIntPoint Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnFinalKetToTransitions(
//			UPARAM() FIntPoint Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnFinalKetToIndex(
//			UPARAM() FIntPoint Input,
//			TArray<int32> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnOperationToIndex(
//			UPARAM() FIntVector Input,
//			TArray<int32> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnOperationToTransitions(
//			UPARAM() FIntVector Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnOperationToInitialKets(
//			UPARAM() FIntVector Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnOperationToFinalKets(
//			UPARAM() FIntVector Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnTransitionToIndex(
//			UPARAM() FIntVector Input,
//			TArray<int32> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnTransitionToOperations(
//			UPARAM() FIntVector Input,
//			TArray<FIntVector> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnTransitionToInitialKets(
//			UPARAM() FIntVector Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void FxnTransitionToFinalKets(
//			UPARAM() FIntVector Input,
//			TArray<FIntPoint> Output);
//	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
//		void InitializationOfMapToMaps(
//			UPARAM(ref) TArray<FIntVector>& InputOperatorMatrices,
//			UPARAM(ref) TArray<FIntVector>& InputTransitionMatrices,
//			UPARAM(ref) TArray<FIntPoint>& InputInitialKets);
//};
