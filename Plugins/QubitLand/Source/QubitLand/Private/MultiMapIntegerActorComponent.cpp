// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiMapIntegerActorComponent.h"

// Sets default values for this component's properties
UMultiMapIntegerActorComponent::UMultiMapIntegerActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMultiMapIntegerActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMultiMapIntegerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMultiMapIntegerActorComponent::FxnIndexToOperations(
	int32 Input,
	TArray< FIntVector>& Output) {
	//IndexToOperations;
	IndexToOperations.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnIndexToTransitions(
	int32 Input,
	TArray< FIntVector>& Output) {
	//IndexToTransitions;
	IndexToTransitions.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnIndexToInitialKets(
	int32 Input,
	TArray< FIntPoint>& Output) {
	IndexToInitialKets.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnIndexToFinalKets(
	int32 Input,
	TArray< FIntPoint>& Output) {
	IndexToFinalKets.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnInitialKetToIndex(
	FIntPoint Input,
	TArray< int32>& Output) {
	InitialKetToIndex.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnInitialKetToFinalKets(
	FIntPoint Input,
	TArray< FIntPoint>& Output) {
	InitialKetToFinalKets.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnInitialKetToOperators(
	FIntPoint Input,
	TArray< FIntVector>& Output) {
	InitialKetToOperators.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnInitialKetToTransitions(
	FIntPoint Input,
	TArray< FIntVector>& Output) {
	InitialKetToTransitions.MultiFind(Input, Output);
}


void UMultiMapIntegerActorComponent::FxnFinalKetToInitialKets(
	FIntPoint Input,
	TArray< FIntPoint>& Output) {
	FinalKetToInitialKets.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnFinalKetToOperators(
	FIntPoint Input,
	TArray< FIntVector>& Output) {
	FinalKetToOperators.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnFinalKetToTransitions(
	FIntPoint Input,
	TArray< FIntVector>& Output) {
	FinalKetToTransitions.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnFinalKetToIndex(
	FIntPoint Input,
	TArray< int32>& Output) {
	FinalKetToIndex.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnOperationToIndex(
	FIntVector Input,
	TArray< int32>& Output) {
	OperationToIndex.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnOperationToTransitions(
	FIntVector Input,
	TArray< FIntVector>& Output) {
	OperationToTransitions.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnOperationToInitialKets(
	FIntVector Input,
	TArray< FIntPoint>& Output) {
	OperationToInitialKets.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnOperationToFinalKets(
	FIntVector Input,
	TArray< FIntPoint>& Output) {
	OperationToFinalKets.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnTransitionToIndex(
	FIntVector Input,
	TArray< int32>& Output) {
	TransitionToIndex.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnTransitionToOperations(
	FIntVector Input,
	TArray< FIntVector>& Output) {
	TransitionToOperations.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnTransitionToInitialKets(
	FIntVector Input,
	TArray< FIntPoint>& Output) {
	TransitionToInitialKets.MultiFind(Input, Output);
}

void UMultiMapIntegerActorComponent::FxnTransitionToFinalKets(
	FIntVector Input,
	TArray< FIntPoint>& Output) {
	TransitionToFinalKets.MultiFind(Input, Output);
}
void UMultiMapIntegerActorComponent::FxnDestinationInitialKetToOperators(
	FIntPoint Input,
	TArray<FIntVector>& Output) {
	DestinationInitialKetToOperators.MultiFind(Input, Output);
}
void UMultiMapIntegerActorComponent::FxnDestinationInitialKetToTransitions(
	FIntPoint Input,
	TArray<FIntVector>& Output) {
	DestinationInitialKetToTransitions.MultiFind(Input, Output);
}
void UMultiMapIntegerActorComponent::InitializationOfMapToMaps(
	int32 InputOperatorCount,
	int32 InputQubitCount,
	TArray<FIntVector>& InputOperatorMatrices,
	TArray<FIntVector>& InputTransitionMatrices,
	TArray<FIntPoint>& InputInitialKets) {
	QubitCount = InputQubitCount;
	OperatorCount = InputOperatorCount;
	uint32 TestOne = 1;
	KetStateCount = (TestOne << QubitCount);

	OperatorMatrices = InputOperatorMatrices;
	TransitionMatrices = InputTransitionMatrices;
	InitialKets = InputInitialKets;

	for (auto& iter : TransitionMatrices) {
		if (InitialKets.Contains(
			FIntPoint(iter.X + 1, iter.Z))) {
			FinalKets.Add(FIntPoint(iter.X, iter.Z));
		}
	}
	MapFullKetSpace.Empty();

	IndexToSubstateCount.Empty();
	OperatorTargetSubstate.Empty();
	OperatorSourceSubstate.Empty();
	TransitionSourceSubstate.Empty();
	TransitionTargetSubstate.Empty();

	IndexToOperations.Empty();
	IndexToTransitions.Empty();
	IndexToInitialKets.Empty();
	IndexToFinalKets.Empty();

	InitialKetToIndex.Empty();
	InitialKetToFinalKets.Empty();
	InitialKetToOperators.Empty();
	InitialKetToTransitions.Empty();

	FinalKetToInitialKets.Empty();
	FinalKetToOperators.Empty();
	FinalKetToTransitions.Empty();
	FinalKetToIndex.Empty();

	OperationToIndex.Empty();
	OperationToTransitions.Empty();
	OperationToInitialKets.Empty();
	OperationToFinalKets.Empty();

	TransitionToIndex.Empty();
	TransitionToOperations.Empty();
	TransitionToInitialKets.Empty();
	TransitionToFinalKets.Empty();

	DestinationInitialKetToOperators.Empty();
	DestinationInitialKetToTransitions.Empty();

	QubitSplitAddressToLocationIntVector.Empty();
	QubitSplitToQubitSplitBase.Empty();
	for (int32 CurrentOpIndex = 0; CurrentOpIndex <= OperatorCount; CurrentOpIndex++) {
		for (int32 CurrentKetFromIndex = 0; CurrentKetFromIndex < KetStateCount; CurrentKetFromIndex++) {
			MapFullKetSpace.Add(FIntPoint(CurrentOpIndex, CurrentKetFromIndex));
		}
	}
	for (int32 CurrentLocalIndex = 0; CurrentLocalIndex < KetStateCount; CurrentLocalIndex++) {
		QubitSplitAddressToLocationIntVector.Add(
			FIntPoint(-1, CurrentLocalIndex),
			FIntVector(-1, CurrentLocalIndex, CurrentLocalIndex));
	}
	TMap<int32, int32> MapPowerOfTwo;
	MapPowerOfTwo.Empty();
	int32 CurrentValueIntPowerOfTwo = 1;
	for (int32 tempint = 0; tempint < 16; tempint++) {
		MapPowerOfTwo.Add(tempint, CurrentValueIntPowerOfTwo);
		CurrentValueIntPowerOfTwo *= 2;
	}
	for (int32 CurrentQubitIndex = 0; CurrentQubitIndex <= QubitCount; CurrentQubitIndex++) {
		int32 CurrentSplitCount = MapPowerOfTwo[CurrentQubitIndex + 1];
		int32 TempDisplace = (QubitCount - (CurrentQubitIndex + 1));
		if (TempDisplace >= 0) {
			int32 CurrentCountTo = MapPowerOfTwo[QubitCount - (CurrentQubitIndex + 1)];
			for (int32 CurrentSplitIndex = 0; CurrentSplitIndex < FMath::Min(CurrentCountTo,KetStateCount); CurrentSplitIndex++) {
				FIntPoint FirstCoord = FIntPoint(CurrentQubitIndex - 1, 2 * CurrentSplitIndex);
				FIntPoint SecondCoord = FIntPoint(CurrentQubitIndex - 1, 2 * CurrentSplitIndex + 1);
				QubitSplitAddressToLocationIntVector.Add(
					FIntPoint(CurrentQubitIndex,
						CurrentSplitIndex),
					FIntVector(CurrentQubitIndex,
						CurrentSplitIndex * CurrentSplitCount,
						(CurrentSplitIndex + 1) * CurrentSplitCount - 1));
				QubitSplitToQubitSplitBase.Add(FirstCoord, FIntPoint(CurrentQubitIndex, CurrentSplitIndex));
				QubitSplitToQubitSplitBase.Add(SecondCoord, FIntPoint(CurrentQubitIndex, CurrentSplitIndex));
				QubitSplitToQubitSplitBaseZeroFalse.Add(FirstCoord, FIntPoint(CurrentQubitIndex, CurrentSplitIndex));
				QubitSplitToQubitSplitBaseOneTrue.Add(SecondCoord, FIntPoint(CurrentQubitIndex, CurrentSplitIndex));
				//FIntPoint FirstCoord = FIntPoint(CurrentQubitIndex - 1, CurrentKetIndex * 2);
				//FIntPoint SecondCoord = FIntPoint(CurrentQubitIndex - 1, CurrentKetIndex * 2 + 1);
				//if (CurrentQubitIndex == -1) {
				//	QubitSplitAddressToLocationIntVector.Add(
				//		FIntPoint(CurrentQubitIndex, CurrentKetIndex), 
				//		FIntVector(CurrentQubitIndex, CurrentKetIndex, CurrentKetIndex));
				//}
				//else if (QubitSplitAddressToLocationIntVector.Contains(FirstCoord) 
				//	&& QubitSplitAddressToLocationIntVector.Contains(SecondCoord)) {
				//	FIntPoint FirstCoord = FIntPoint(CurrentQubitIndex - 1, CurrentSplitIndex);
				//	FIntPoint SecondCoord = FIntPoint(CurrentQubitIndex - 1, CurrentSplitIndex + 1);
				//	QubitSplitAddressToLocationIntVector.Add(
				//		FIntPoint(CurrentQubitIndex, CurrentKetIndex),
				//		FIntVector(CurrentQubitIndex,
				//			CurrentSplitIndex * CurrentSplitCount,
				//			(CurrentSplitIndex + 1) * CurrentSplitCount - 1));
				//	QubitSplitToQubitSplitBase.Add(FirstCoord, FIntPoint(CurrentQubitIndex, CurrentKetIndex));
				//	QubitSplitToQubitSplitBase.Add(SecondCoord, FIntPoint(CurrentQubitIndex, CurrentKetIndex));
				//}
			}
		}
		
	}
	//KetToQubitSplits.Empty();
	//QubitSplitToQubitSplitsChildren.Empty();
	//QubitSplitToQubitSplitBase.Empty();
	//QubitToQubitSplits.Empty();
	

	for (auto iter : OperatorMatrices) {
		FIntVector LocalIter = iter;
		FIntVector LocalOp = iter;
		//int32 LocalIndex = LocalIter.X;
		const int32 LocalIndex = LocalIter.X;
		FIntPoint LocalInitialKet = FIntPoint(iter.X, iter.Y);
		FIntPoint LocalFinalKet = FIntPoint(iter.X, iter.Z);
		FIntPoint LocalNextInitialKet = FIntPoint(iter.X + 1, iter.Z);
		bool ValidInitialKet = InitialKets.Contains(LocalInitialKet);
		bool ValidFinalKet = FinalKets.Contains(LocalInitialKet);
		bool ValidTransition = TransitionMatrices.Contains(iter);
		IndexToOperations.AddUnique(
			/* TPair<int32, FIntVector> (*/LocalIndex, LocalOp);
		if (ValidTransition) {
			IndexToTransitions.AddUnique(
				/* TPair<int32, FIntVector> (*/LocalIndex, LocalOp);
		}
		if (ValidInitialKet) {
			IndexToInitialKets.AddUnique(
				/* TPair<int32, FIntPoint> (*/LocalIndex, LocalInitialKet);
		}
		if (ValidFinalKet) {
			IndexToFinalKets.AddUnique(
				/* TPair<int32, FIntPoint> (*/LocalIndex, LocalFinalKet);
		}
		if (ValidInitialKet) {
			InitialKetToIndex.AddUnique(
				/* TPair<FIntPoint, int32> (*/LocalInitialKet, LocalIndex);
		}
		if (ValidInitialKet && ValidFinalKet) {
			InitialKetToFinalKets.AddUnique(
				/* TPair<FIntPoint, FIntPoint> (*/LocalInitialKet, LocalFinalKet);
		}
		if (ValidInitialKet) {
			InitialKetToOperators.AddUnique(
				/* TPair<FIntPoint, FIntVector> (*/LocalInitialKet, LocalOp);
		}
		if (ValidInitialKet && ValidTransition) {
			InitialKetToTransitions.AddUnique(
				/* TPair<FIntPoint, FIntVector> (*/LocalInitialKet, LocalOp);
		}


		if (ValidFinalKet) {
			FinalKetToIndex.AddUnique(
				/* TPair<FIntPoint, int32> (*/LocalFinalKet, LocalIndex);
		}
		if (ValidFinalKet && ValidInitialKet) {
			/* TPair<FIntPoint, FIntPoint> */FinalKetToInitialKets.AddUnique(LocalFinalKet, LocalInitialKet);
		}
		if (ValidFinalKet) {
			FinalKetToOperators.AddUnique(
				/* TPair<FIntPoint, FIntVector> (*/LocalFinalKet, LocalOp);
		}
		if (ValidFinalKet && ValidTransition) {
			FinalKetToTransitions.AddUnique(
				/* TPair<FIntPoint, FIntVector> (*/LocalFinalKet, LocalOp);
		}

		OperationToIndex.AddUnique(
			/* TPair<FIntVector, int32> (*/LocalOp, LocalIndex);
		if (ValidInitialKet) {
			OperationToInitialKets.AddUnique(
				/* TPair<FIntVector, FIntPoint> (*/LocalOp, LocalInitialKet);
		}
		if (ValidFinalKet) {
			OperationToFinalKets.AddUnique(
				/* TPair<FIntVector, FIntPoint> (*/LocalOp, LocalFinalKet);
		}
		if (ValidTransition) {
			OperationToTransitions.AddUnique(
				/* TPair<FIntVector, FIntVector> (*/LocalOp, LocalOp);
		}

		if (ValidTransition) {
			TransitionToIndex.AddUnique(
				/* TPair<FIntVector, int32> (*/LocalOp, LocalIndex);
		}
		if (ValidTransition && ValidInitialKet) {
			TransitionToInitialKets.AddUnique(
				/* TPair<FIntVector, FIntPoint> (*/LocalOp, LocalInitialKet);
		}
		if (ValidTransition && ValidFinalKet) {
			TransitionToFinalKets.AddUnique(
				/* TPair<FIntVector, FIntPoint> (*/LocalOp, LocalFinalKet);
		}
		if (ValidTransition) {
			TransitionToOperations.AddUnique(
				/* TPair<FIntVector, FIntVector> (*/LocalOp, LocalOp);
		}
		DestinationInitialKetToOperators.AddUnique(
			/* TPair<int32, FIntVector> (*/LocalNextInitialKet, LocalOp);
		if (ValidTransition) {
			DestinationInitialKetToTransitions.AddUnique(
				/* TPair<int32, FIntVector> (*/LocalNextInitialKet, LocalOp);
		}
	}
	//TMap<FIntPoint, int32> KetAddressCountMap;
	//for (int32 IntegerIndex0 = 0; IntegerIndex0 < OperatorCount; IntegerIndex0++) {
	//	for (int32 IntegerIndex1 = 0; IntegerIndex1 < KetStateCount; IntegerIndex1++) {
	//		KetAddressCountMap.Add(FIntPoint(IntegerIndex0, IntegerIndex1), 0);
	//	}
	//}
	TArray<int32> LocalOperatorToStateCountArray;
	TArray<FIntVector> CurrentOpArray;
	for (int32 IntegerIndex0 = 0; IntegerIndex0 < OperatorCount; IntegerIndex0++) {
		LocalOperatorToStateCountArray.Empty();
		for (int32 IntegerIndex1 = 0; IntegerIndex1 < KetStateCount; IntegerIndex1++) {
			CurrentOpArray.Empty();
			FinalKetToOperators.MultiFind(FIntPoint(IntegerIndex0, IntegerIndex1), CurrentOpArray);
			TArray<int32> StartStateArray;
			for (auto& iterOp : CurrentOpArray) {
				StartStateArray.Add(iterOp.Y);
			}
			StartStateArray.Sort();
			int32 SubstateCountTo = 0;
			for (auto& iterStartState : StartStateArray) {
				TransitionTargetSubstate.Add(
					FIntVector(IntegerIndex0, iterStartState, IntegerIndex1), SubstateCountTo);
				SubstateCountTo += 1;
			}
			LocalOperatorToStateCountArray.Add(SubstateCountTo);
			CurrentOpArray.Empty();
			InitialKetToOperators.MultiFind(FIntPoint(IntegerIndex0, IntegerIndex1), CurrentOpArray);
			TArray<int32> EndStateArray;
			for (auto& iterOp : CurrentOpArray) {
				EndStateArray.Add(iterOp.Z);
			}
			EndStateArray.Sort();
			int32 SubstateCountFrom = 0;
			for (auto& iterEndState : EndStateArray) {
				TransitionSourceSubstate.Add(
					FIntVector(IntegerIndex0, iterEndState, IntegerIndex1), SubstateCountFrom);
				SubstateCountFrom += 1;
			}
			LocalOperatorToStateCountArray.Add(SubstateCountFrom);
		}
		IndexToSubstateCount.Add(IntegerIndex0, FMath::Max(LocalOperatorToStateCountArray));
	}
	//for (int32 OpIndex = 0; OpIndex < OperatorCount; OpIndex++) {
	//	if (IndexToSubstateCount[OpIndex] == 2) {
	//		TArray<FIntPoint> CurrentInitialKetArray;
	//		FxnIndexToInitialKets(OpIndex, CurrentInitialKetArray);
	//		TArray<FIntPoint> CurrentInitialKetArray;
	//		FxnInitialKetToFinalKets(OpIndex, CurrentInitialKetArray);
	//		for (auto& iterInitialKet : CurrentInitialKetArray) {
	//			TArray<FIntPoint> CurrentFinalKetArray;
	//			InitialKetToFinalKets.MultiFind(
	//				iterInitialKet, CurrentFinalKetArray);
	//			if (CurrentFinalKetArray.Num() == 2) {
	//				int32 ValueKetBase = iterInitialKet.Y;
	//				int32 OtherKetBase;
	//				// Branch equal is upper 11 and decrease is 01
	//				if (iterInitialKet.Y == CurrentFinalKetArray[0].Y &&
	//					iterInitialKet.Y > CurrentFinalKetArray[1].Y) {
	//					OperatorSourceSubstate.Add(
	//						FIntVector(OpIndex, iterInitialKet.Y, CurrentFinalKetArray[0].Y), 0);
	//					OperatorTargetSubstate.Add(
	//						FIntVector(OpIndex, iterInitialKet.Y, CurrentFinalKetArray[0].Y), 0);
	//				}
	//				// Branch equal is lower 00 and increase is 10
	//				else if (iterInitialKet.Y == CurrentFinalKetArray[0].Y &&
	//					iterInitialKet.Y < CurrentFinalKetArray[1].Y) {
	//					OtherKetBase = CurrentFinalKetArray[1].Y;
	//				}
	//				// Branch equal is upper 11 and decrease is 01
	//				else if (iterInitialKet.Y == CurrentFinalKetArray[0].Y &&
	//					iterInitialKet.Y > CurrentFinalKetArray[1].Y) {
	//					OtherKetBase = CurrentFinalKetArray[0].Y;
	//				}
	//				else if (iterInitialKet.Y == CurrentFinalKetArray[0].Y &&
	//					iterInitialKet.Y < CurrentFinalKetArray[1].Y) {
	//					OtherKetBase = CurrentFinalKetArray[0].Y;
	//				}
	//				int32 LowerKet = FMath::Min(ValueKetBase, OtherKetBase);
	//				int32 HigherKet = FMath::Max(ValueKetBase, OtherKetBase);
	//				FIntVector Bar00 = FIntVector(OpIndex, LowerKet, LowerKet);
	//				OperatorSourceSubstate.Add(Bar00, 0);
	//				OperatorTargetSubstate.Add(Bar00, 0);
	//				FIntVector Bar01 = FIntVector(OpIndex, LowerKet, HigherKet);
	//				OperatorSourceSubstate.Add(Bar01, 0);
	//				OperatorTargetSubstate.Add(Bar01, 1);
	//				FIntVector Bar10 = FIntVector(OpIndex, HigherKet, LowerKet);
	//				OperatorSourceSubstate.Add(Bar10, 1);
	//				OperatorTargetSubstate.Add(Bar10, 0);
	//				FIntVector Bar11 = FIntVector(OpIndex, HigherKet, HigherKet);
	//				OperatorSourceSubstate.Add(Bar11, 1);
	//				OperatorTargetSubstate.Add(Bar11, 1);
	//			}
	//		}
	//	}
	//	OperatorFromToStateSubstateMap;
	//}
	for (int32 OpIndex = 0; OpIndex < OperatorCount; OpIndex++) {
		if (IndexToSubstateCount[OpIndex] == 2) {
			TArray<FIntVector> CurrentOperationArray;
			FxnIndexToOperations(OpIndex, CurrentOperationArray);
			for (auto& iterOp : CurrentOperationArray) {
				if (iterOp.Y != iterOp.Z) {
					// Branch equal is upper 11 and decrease is 01
					if (iterOp.Y > iterOp.Z) {
						OperatorSourceSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Y), 1);
						OperatorTargetSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Y), 1);
						OperatorSourceSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Z), 0);
						OperatorTargetSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Z), 1);
					}
					// Branch equal is lower 00 and increase is 10
					else if (iterOp.Y < iterOp.Z) {
						OperatorSourceSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Y), 0);
						OperatorTargetSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Y), 0);
						OperatorSourceSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Z), 1);
						OperatorTargetSubstate.Add(
							FIntVector(OpIndex, iterOp.Y, iterOp.Z), 0);
					}
				}
			}
		}
		else if(IndexToSubstateCount[OpIndex] == 1) {
			TArray<FIntVector> CurrentOperationArray;
			FxnIndexToOperations(OpIndex, CurrentOperationArray);
			for (auto& iterOp : CurrentOperationArray) {
				OperatorSourceSubstate.Add(
					FIntVector(OpIndex, iterOp.Y, iterOp.Z), 0);
				OperatorTargetSubstate.Add(
					FIntVector(OpIndex, iterOp.Y, iterOp.Z), 0);
			}
		}
	}
	//for (auto& iterKetAddress : KetAddressCountMap) {
	//	TArray<FIntVector> CurrentInitialKetArray;
	//	IndexToInitialKets.MultiFind(iterKetAddress.Key, CurrentInitialKetArray);
	//}
	//for (auto& iterIndex : IndexToInitialKets) {
	//	TArray<FIntVector> CurrentInitialKetArray;
	//	IndexToInitialKets.MultiFind(iterIndex.Key, CurrentInitialKetArray);
	//	TMap<FIntPoint, int32> KetAddressCountMap;
	//	for (int IntegerIndex = 0; IntegerIndex < KetStateCount; IntegerIndex++) {
	//		KetAddressCountMap.Add(FIntPoint(iterIndex, IntegerIndex), 0);
	//	}
	//	for (auto& iterInitialKet : CurrentInitialKetArray) {
	//		if()
	//	}

	//}
	//for (auto& iterIndex : IndexToFinalKets) {
	//	TArray<FIntPoint> CurrentFinalKets;
	//	IndexToFinalKets.MultiFind(iterIndex.Key, CurrentFinalKets);
	//	TMap<FIntPoint, int32> KetAddressCountMap;
	//	for (int IntegerIndex = 0; IntegerIndex < KetStateCount; IntegerIndex++) {
	//		KetAddressCountMap.Add(FIntPoint(iterIndex, IntegerIndex), 0);
	//	}
	//	TArray<int32> ArrayOfCounts;
	//	KetAddressCountMap.GenerateValueArray(ArrayOfCounts);
	//	int32 LocalMaxSubstateCount = FMath::Max(ArrayOfCounts);
	//	IndexToSubstateCount.Add(iterIndex, LocalMaxSubstateCount);
	//	TMap<FIntPoint,int32
	//	for (auto& iterFinalKets : CurrentFinalKets) {
	//		
	//	}
	//	for (auto& iterFinalKets : CurrentFinalKets) {
	//		
	//	}
	//	LocalFinalKet = FIntPoint LocalFinalKet = FIntPoint(iter.X, iter.Z);
	//	
	//}
}
void UMultiMapIntegerActorComponent::GetRangeOperationStateFromInitial(
	TArray<FIntPoint>& InputIntPointArray,
	//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
	//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
	FIntPoint& OperationIndexRange,
	FIntPoint& KetStateRange) {
	TArray<int32> Operations;
	TArray<int32> States;
	for (auto& iter : InputIntPointArray) {
		Operations.Add(iter.X);
		Operations.Add(iter.Y);
	}
	OperationIndexRange = FIntPoint(FMath::Min(Operations), FMath::Max(Operations));
	OperationIndexRange = FIntPoint(FMath::Min(Operations), FMath::Max(Operations));
	KetStateRange = FIntPoint(FMath::Min(States), FMath::Max(States));
	KetStateRange = FIntPoint(FMath::Min(States), FMath::Max(States));
}
void UMultiMapIntegerActorComponent::GetRangeOperationStateFromFinal(
	TArray<FIntPoint>& InputIntPointArray,
	//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
	//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
	FIntPoint& OperationIndexRange,
	FIntPoint& KetStateRange) {
	TArray<int32> Operations;
	TArray<int32> States;
	for (auto& iter : InputIntPointArray) {
		Operations.Add(iter.X + 1);
		Operations.Add(iter.Y);
	}
	OperationIndexRange = FIntPoint(FMath::Min(Operations), FMath::Max(Operations));
	OperationIndexRange = FIntPoint(FMath::Min(Operations), FMath::Max(Operations));
	KetStateRange = FIntPoint(FMath::Min(States), FMath::Max(States));
	KetStateRange = FIntPoint(FMath::Min(States), FMath::Max(States));
}
void UMultiMapIntegerActorComponent::GetRangeOperationStateFromTransition(
	TArray<FIntVector>& InputIntVectorArray,
	//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
	//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
	FIntPoint& OperationIndexRange,
	FIntPoint& KetStateRange) {
	TArray<int32> Operations;
	TArray<int32> States;
	for (auto& iter : InputIntVectorArray) {
		Operations.Add(iter.X);
		Operations.Add(iter.X + 1);
		States.Add(iter.Y);
		States.Add(iter.Z);
	}
	OperationIndexRange = FIntPoint(FMath::Min(Operations), FMath::Max(Operations));
	OperationIndexRange = FIntPoint(FMath::Min(Operations), FMath::Max(Operations));
	KetStateRange = FIntPoint(FMath::Min(States), FMath::Max(States));
	KetStateRange = FIntPoint(FMath::Min(States), FMath::Max(States));
}
void UMultiMapIntegerActorComponent::InitializationOfMapToMapsPlusComplexNumbers(
	int32 InputOperatorCount,
	int32 InputQubitCount,
	TArray<FIntVector>& InputOperatorMatrices,
	TArray<FIntVector>& InputTransitionMatrices,
	TArray<FIntPoint>& InputInitialKets,
	TMap<FIntVector, FVector2D>& InputOperatorMatricesComplexNumbers,
	TMap<FIntVector, FVector2D>& InputTransitionMatricesComplexNumbers,
	TMap<FIntPoint, FVector2D>& InputInitialKetsComplexNumbers) {
	//MapOperationsComplexNumbers = InputOperatorMatricesComplexNumbers;
	//MapTransitionsComplexNumbers = InputTransitionMatricesComplexNumbers;
	//MapInitialKetComplexNumbers = InputInitialKetsComplexNumbers;
	InitializationOfMapToMaps(InputOperatorCount, InputQubitCount,
		InputOperatorMatrices, InputTransitionMatrices, InputInitialKets);
}
void UMultiMapIntegerActorComponent::FxnGetAllForOpKetFromKetTo(
	TArray <int32>& InputOpArray,
	TArray <int32>& InputKetFromArray,
	TArray <int32>& InputKetToArray,
	TArray<FIntVector>& OutputArray) {
	TArray <int32> LocalOpArray;
	TArray <int32> LocalKetFromArray;
	TArray <int32> LocalKetToArray;
	if (InputOpArray.Num() == 0) {
		for (int32 CurrentOpIndex = 0; CurrentOpIndex <= OperatorCount; CurrentOpIndex++) {
			LocalOpArray.Add(CurrentOpIndex);
		}
	}
	else LocalOpArray = InputOpArray;
	if (InputKetFromArray.Num() == 0) {
		for (int32 CurrentKetFromIndex = 0; CurrentKetFromIndex <= KetStateCount; CurrentKetFromIndex++) {
			LocalKetFromArray.Add(CurrentKetFromIndex);
		}
	}
	else LocalKetFromArray = InputKetFromArray;
	if (InputKetFromArray.Num() == 0) {
		for (int32 CurrentKetToIndex = 0; CurrentKetToIndex <= KetStateCount; CurrentKetToIndex++) {
			LocalKetToArray.Add(CurrentKetToIndex);
		}
	}
	else LocalKetToArray = InputKetToArray;
	OutputArray.Empty();
	for (auto& iterOp : LocalOpArray) {
		for (auto& iterKetFrom : LocalKetFromArray) {
			for (auto& iterKetTo : LocalKetToArray) {
				OutputArray.Add(FIntVector(iterOp, iterKetFrom, iterKetTo));
			}
		}
	}
}
void UMultiMapIntegerActorComponent::FxnGetAllForOpKet(
	TArray <int32>& InputOpArray,
	TArray <int32>& InputKetArray,
	TArray<FIntPoint>& OutputArray) {
	TArray <int32> LocalOpArray;
	TArray <int32> LocalKetArray;
	if (InputOpArray.Num() == 0) {
		for (int32 CurrentOpIndex = 0; CurrentOpIndex <= OperatorCount; CurrentOpIndex++) {
			LocalOpArray.Add(CurrentOpIndex);
		}
	}
	else LocalOpArray = InputOpArray;
	if (InputKetArray.Num() == 0) {
		for (int32 CurrentKetIndex = 0; CurrentKetIndex <= KetStateCount; CurrentKetIndex++) {
			LocalKetArray.Add(CurrentKetIndex);
		}
	}
	else LocalKetArray = InputKetArray;
	OutputArray.Empty();
	for (auto& iterOp : LocalOpArray) {
		for (auto& iterKet : LocalKetArray) {
			OutputArray.Add(FIntPoint(iterOp, iterKet));
		}
	}
}
void UMultiMapIntegerActorComponent::FxnGetAllForOpKetQubit(
	TArray <int32>& InputOpArray,
	TArray <int32>& InputKetArray,
	TArray <int32>& InputQubitArray,
	TArray<FIntVector>& OutputArray) {
	TArray <int32> LocalOpArray;
	TArray <int32> LocalKetArray;
	TArray <int32> LocalQubitArray;
	if (InputOpArray.Num() == 0) {
		for (int32 CurrentOpIndex = 0; CurrentOpIndex <= OperatorCount; CurrentOpIndex++) {
			LocalOpArray.Add(CurrentOpIndex);
		}
	}
	else LocalOpArray = InputOpArray;
	if (InputKetArray.Num() == 0) {
		for (int32 CurrentKetIndex = 0; CurrentKetIndex <= KetStateCount; CurrentKetIndex++) {
			LocalKetArray.Add(CurrentKetIndex);
		}
	}
	else LocalKetArray = InputKetArray;
	if (InputQubitArray.Num() == 0) {
		for (int32 CurrentQubitIndex = 0; CurrentQubitIndex <= KetStateCount; CurrentQubitIndex++) {
			LocalQubitArray.Add(CurrentQubitIndex);
		}
	}
	else LocalQubitArray = InputQubitArray;
	OutputArray.Empty();
	for (auto& iterOp : LocalOpArray) {
		for (auto& iterKet : LocalKetArray) {
			for (auto& iterQubit : LocalQubitArray) {
				OutputArray.Add(FIntVector(iterOp, iterKet, iterQubit));
			}
		}
	}
}