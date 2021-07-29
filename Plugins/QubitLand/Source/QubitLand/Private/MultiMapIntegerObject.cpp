//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "MultiMapIntegerObject.h"
//
//
// void UMultiMapIntegerObject::FxnIndexToOperations(
//	UPARAM() int32 Input,
//	TArray< FIntVector> Output) {
//	IndexToOperations;
//}
//
// void UMultiMapIntegerObject::FxnIndexToTransitions(
//	UPARAM() int32 Input,
//	TArray< FIntVector> Output) {
//	IndexToTransitions;
//}
//
// void UMultiMapIntegerObject::FxnIndexToInitialKets(
//	UPARAM() int32 Input,
//	TArray< FIntPoint> Output) {
//	IndexToInitialKets.MultiFind(Input,Output);
//}
//
// void UMultiMapIntegerObject::FxnIndexToFinalKets(
//	UPARAM() int32 Input,
//	TArray< FIntPoint> Output) {
//	IndexToFinalKets.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnInitialKetToIndex(
//	UPARAM() FIntPoint Input,
//	TArray< int32> Output) {
//	InitialKetToIndex.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnInitialKetToFinalKets(
//	UPARAM() FIntPoint Input,
//	TArray< FIntPoint> Output) {
//	InitialKetToFinalKets.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnInitialKetToOperators(
//	UPARAM() FIntPoint Input,
//	TArray< FIntVector> Output) {
//	InitialKetToOperators.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnInitialKetToTransitions(
//	UPARAM() FIntPoint Input,
//	TArray< FIntVector> Output) {
//	InitialKetToTransitions.MultiFind(Input, Output);
//}
//
//
// void UMultiMapIntegerObject::FxnFinalKetToInitialKets(
//	UPARAM() FIntPoint Input,
//	TArray< FIntPoint> Output) {
//	FinalKetToInitialKets.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnFinalKetToOperators(
//	UPARAM() FIntPoint Input,
//	TArray< FIntVector> Output) {
//	FinalKetToOperators.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnFinalKetToTransitions(
//	UPARAM() FIntPoint Input,
//	TArray< FIntVector> Output) {
//	FinalKetToTransitions.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnFinalKetToIndex(
//	UPARAM() FIntPoint Input,
//	TArray< int32> Output) {
//	FinalKetToIndex.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnOperationToIndex(
//	UPARAM() FIntVector Input,
//	TArray< int32> Output) {
//	OperationToIndex.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnOperationToTransitions(
//	UPARAM() FIntVector Input,
//	TArray< FIntVector> Output) {
//	OperationToTransitions.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnOperationToInitialKets(
//	UPARAM() FIntVector Input,
//	TArray< FIntPoint> Output) {
//	OperationToInitialKets.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnOperationToFinalKets(
//	UPARAM() FIntVector Input,
//	TArray< FIntPoint> Output) {
//	OperationToFinalKets.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnTransitionToIndex(
//	UPARAM() FIntVector Input,
//	TArray< int32> Output) {
//	TransitionToIndex.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnTransitionToOperations(
//	UPARAM() FIntVector Input,
//	TArray< FIntVector> Output) {
//	TransitionToOperations.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnTransitionToInitialKets(
//	UPARAM() FIntVector Input,
//	TArray< FIntPoint> Output) {
//	TransitionToInitialKets.MultiFind(Input, Output);
//}
//
// void UMultiMapIntegerObject::FxnTransitionToFinalKets(
//	UPARAM() FIntVector Input,
//	TArray< FIntPoint> Output) {
//	TransitionToFinalKets.MultiFind(Input, Output);
//}
//
//void InitializationOfMapToMaps(
//	UPARAM(ref) TArray<FIntVector>& InputOperatorMatrices,
//	UPARAM(ref) TArray<FIntVector>& InputTransitionMatrices,
//	UPARAM(ref) TArray<FIntPoint>& InputInitialKets) {
//	OperatorMatrices = InputOperatorMatrices;
//	TransitionMatrices = InputTransitionMatrices;
//	TArray<FIntPoint> InitialKets = InputInitialKets;
//	TArray<FIntPoint> FinalKets;
//	for (auto& iter : TransitionMatrices) {
//		if (InitialKets.Contains(
//			FIntPoint(iter.X + 1, iter.Z))) {
//			FinalKets.Add(FIntPoint(iter.X, iter.Z));
//		}
//	}
//	for (auto& iter : OperatorMatrices) {
//		if (InitialKets.Contains(
//			FIntPoint(iter.X + 1, iter.Z))) {
//			FinalKets.Add(FIntPoint(iter.X, iter.Z));
//		}
//	}
//
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
//
//	for (auto iter : OperatorMatrices) {
//		FIntVector LocalIter = iter;
//		FIntVector LocalOp = iter.X
//		int32 LocalIndex = LocalIter.X;
//		FIntPoint LocalInitialKet = FIntPoint(iter.X, iter.Y);
//		FIntPoint LocalFinalKet = FIntPoint(iter.X, iter.Z);
//		bool ValidInitialKet = InitialKets.Contains(LocalInitialKet);
//		bool ValidFinalKet = FinalKets.Contains(LocalInitialKet);
//		bool ValidTransition = TransitionMatrices.Contains(iter);
//
//		IndexToOperations.Add(LocalIndex, LocalOp);
//		if (ValidTransition) {
//			IndexToTransitions.Add(LocalIndex, LocalOp);
//		}
//		if (ValidInitialKet) {
//			OperationToInitialKets.Add(LocalIndex, LocalInitialKet);
//		}
//		if (ValidFinalKet) {
//			OperationToFinalKets.Add(LocalIndex, LocalFinalKet);
//		}
//
//		//TMultiMap<FIntPoint, int32> InitialKetToIndex;
//		//TMultiMap<FIntPoint, FIntPoint> InitialKetToFinalKets;
//		//TMultiMap<FIntPoint, FIntVector> InitialKetToOperators;
//		//TMultiMap<FIntPoint, FIntVector> InitialKetToTransitions;
//
//		if (ValidInitialKet) {
//			InitialKetToIndex.Add(LocalInitialKet, LocalIndex);
//		}
//		if (ValidInitialKet && ValidFinalKet) {
//			InitialKetToFinalKets.Add(LocalInitialKet, LocalFinalKet);
//		}
//		if (ValidInitialKet) {
//			InitialKetToOperators.Add(LocalInitialKet, LocalOp);
//		}
//		if (ValidInitialKet && ValidTransition) {
//			InitialKetToTransitions.Add(LocalInitialKet, LocalOp);
//		}
//
//
//		if (ValidFinalKet) {
//			FinalKetToIndex.Add(LocalFinalKet, LocalIndex);
//		}
//		if (ValidFinalKet && ValidInitialKet) {
//			FinalKetToInitialKets.Add(LocalFinalKet, LocalInitialKet);
//		}
//		if (ValidFinalKet) {
//			FinalKetToOperators.Add(LocalFinalKet, LocalOp);
//		}
//		if (ValidFinalKet && ValidTransition) {
//			FinalKetToTransitions.Add(LocalFinalKet, LocalOp);
//		}
//
//		OperationToIndex.Add(LocalOp, LocalIndex);
//		if (ValidInitialKet) {
//			OperationToInitialKets.Add(LocalOp, LocalInitialKet);
//		}
//		if (ValidFinalKet) {
//			OperationToFinalKets.Add(LocalOp, LocalFinalKet);
//		}
//		if (ValidTransition) {
//			OperationToTransitions.Add(LocalOp, LocalOp);
//		}
//
//		if (ValidTransition) {
//			TransitionToIndex.Add(LocalOp, LocalOp);
//		}
//		if (ValidTransition && ValidInitialKet) {
//			TransitionToInitialKets.Add(LocalOp, LocalInitialKet);
//		}
//		if (ValidTransition && ValidFinalKet) {
//			TransitionToFinalKets.Add(LocalOp, LocalFinalKet);
//		}
//		if (ValidTransition) {
//			TransitionToOperations.Add(LocalOp, LocalOp);
//		}
//	}
//}