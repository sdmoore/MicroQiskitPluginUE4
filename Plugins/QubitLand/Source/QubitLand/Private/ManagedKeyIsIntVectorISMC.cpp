// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagedKeyIsIntVectorISMC.h"


UManagedKeyIsIntVectorISMC::UManagedKeyIsIntVectorISMC() {};
UManagedKeyIsIntVectorISMC::~UManagedKeyIsIntVectorISMC() {};
void UManagedKeyIsIntVectorISMC::GetFirstLastIndexForKey(
	FIntVector InputKey,
	int32& RefFirstIndex,
	int32& RefLastIndex,
	bool& SuccessFlag) {
	SuccessFlag = false;
	RefFirstIndex = 0;
	RefLastIndex = 0;
	if (CurrentMapKeyToSize.Contains(InputKey)
		&& CurrentOrderArrayKey.Contains(InputKey)) {
		int32 TargetKeyArrayIndex = CurrentOrderArrayKey.Find(InputKey);
		for (int32 KeyArrayIndex = 0; KeyArrayIndex < TargetKeyArrayIndex; KeyArrayIndex++) {
			RefFirstIndex += CurrentMapKeyToSize[CurrentOrderArrayKey[KeyArrayIndex]];
			if (KeyArrayIndex == TargetKeyArrayIndex) {
				RefFirstIndex += CurrentMapKeyToSize[CurrentOrderArrayKey[KeyArrayIndex]];
			}
		}
		RefLastIndex = RefFirstIndex + CurrentMapKeyToSize[InputKey] - 1;
		if (this->GetInstanceCount() > RefLastIndex && RefLastIndex > RefFirstIndex) {
			SuccessFlag = true;
		}
		else {
			SuccessFlag = false;
		}
	}
	else {
		SuccessFlag = false;
	}
}
//void UManagedKeyIsIntVectorISMC::AddValuesForGivenKey(
//	FIntVector InputKey, 
//	TArray< FTransform >& InputTransformArray,
//	bool SuccessFlag) {
//	int32 StartIndex, FinishIndex;
//	TArray< FTransform > LocalTranformArray;
//	if (GetFirstLastIndexForKey(InputKey, StartIndex, FinishIndex)) {
//		if (CurrentOrderArrayKey.Remove(InputKey) == 1) {
//			for (int32 CurrentIndex = StartIndex; CurrentIndex <= FinishIndex; CurrentIndex++) {
//				FTransform LocalTransform;
//				GetInstanceTransform(CurrentIndex, LocalTransform);
//				LocalTranformArray.Add(LocalTransform);
//			}
//			for (int32 CurrentIndex = StartIndex; CurrentIndex <= FinishIndex; CurrentIndex++) {
//				RemoveInstance(StartIndex);
//			}
//			LocalTranformArray.Append(InputTransformArray);
//			//for (int32 CurrentIndex = 0; CurrentIndex < InputTransformArray.Num(); CurrentIndex++) {
//			//	LocalTranformArray.Add(InputTransformArray[CurrentIndex]);
//			//}
//			for (auto& iter : LocalTranformArray) {
//				AddInstance(iter);
//				CurrentTransformArray.Add(iter);
//			}
//			CurrentOrderArrayKey.Add(InputKey);
//			CurrentMapKeyToSize.Emplace(InputKey, LocalTranformArray.Num());
//			SuccessFlag = true;
//		}
//		else {
//			SuccessFlag = false;
//		}
//	}
//	else {
//		for (auto& iter : LocalTranformArray) {
//			AddInstance(iter);
//			CurrentTransformArray.Add(iter);
//		}
//		CurrentOrderArrayKey.Add(InputKey);
//		CurrentMapKeyToSize.Emplace(InputKey, InputTransformArray.Num());
//		SuccessFlag = true;
//	}
//	return;
//}
void UManagedKeyIsIntVectorISMC::RemoveKey(
	FIntVector InputKey,
	bool& SuccessFlag) {
	int32 StartIndex, FinishIndex;
	bool ValidKey = false;
	GetFirstLastIndexForKey(InputKey, StartIndex, FinishIndex, ValidKey);
	if (ValidKey) {
		CurrentOrderArrayKey.Remove(InputKey);
		CurrentMapKeyToSize.Remove(InputKey);
		for (int32 CurrentIndex = FinishIndex; CurrentIndex >= StartIndex; CurrentIndex--) {
			RemoveInstance(CurrentIndex);
		}
		SuccessFlag = true;
	}
	else {
		SuccessFlag = false;
	}
}
void UManagedKeyIsIntVectorISMC::ClearAllKeys(
	bool& SuccessFlag) {
	CurrentOrderArrayKey.Empty();
	CurrentMapKeyToSize.Empty();
	this->ClearInstances();
	SuccessFlag = true;
}
void UManagedKeyIsIntVectorISMC::UpdateKeyWithArray(
	FIntVector InputKey,
	TArray< FTransform >& InputTransformArray,
	bool& SuccessFlag) {
	int32 StartIndex, FinishIndex;
	bool ValidKey = false;
	GetFirstLastIndexForKey(InputKey, StartIndex, FinishIndex, ValidKey);
	if (ValidKey) {
		if (InputTransformArray.Num() == (FinishIndex - StartIndex)) {
			for (int32 LocalIndex = 0; LocalIndex + LocalIndex < (FinishIndex - StartIndex); LocalIndex++) {
				UpdateInstanceTransform(StartIndex + LocalIndex, InputTransformArray[LocalIndex]);
			}
			SuccessFlag = true;
		}
		else {
			for (int32 CurrentIndex = FinishIndex; CurrentIndex >= StartIndex; CurrentIndex--) {
				RemoveInstance(CurrentIndex);
			}
			CurrentOrderArrayKey.Remove(InputKey);
			CurrentOrderArrayKey.Add(InputKey);
			CurrentMapKeyToSize.Add(InputKey, InputTransformArray.Num());
			for (int32 CurrentLocalIndex = 0; CurrentLocalIndex < InputTransformArray.Num(); CurrentLocalIndex++) {
				this->AddInstance(InputTransformArray[CurrentLocalIndex]);
			}
			SuccessFlag = true;
		}
	}
	else {
		CurrentOrderArrayKey.Add(InputKey);
		CurrentMapKeyToSize.Add(InputKey, InputTransformArray.Num());
		for (int32 CurrentLocalIndex = 0; CurrentLocalIndex < InputTransformArray.Num(); CurrentLocalIndex++) {
			this->AddInstance(InputTransformArray[CurrentLocalIndex]);
		}
		SuccessFlag = true;
	}
}

//void UManagedKeyIsIntVectorISMC::AuditInternalData(bool SuccessFlag) {
//	int32 LocalSum = 0;
//	bool ErrorContainingFlag = false;
//	for (auto& iter : CurrentMapKeyToSize) {
//		LocalSum += CurrentMapKeyToSize[iter.Key];
//		if (!(CurrentOrderArrayKey.Contains(iter.Key))) {
//			ErrorContainingFlag = true;
//		}
//	}
//	if (CurrentMapKeyToSize.Num() != CurrentOrderArrayKey.Num()) SuccessFlag = false;
//	else if (ErrorContainingFlag) SuccessFlag = false;
//	else if (LocalSum != CurrentTransformArray.Num()) SuccessFlag = false;
//	else SuccessFlag = true;
//	return;
//}
//


//bool UManagedKeyIsIntVectorISMC::UpdateKeyWithSameSizeArray(
//	FIntVector InputKey,
//	TArray< FTransform >& InputTransformArray) {
//	if(GetFirstLastIndexForKey(InputKey, StartIndex, FinishIndex))
//}
//bool UManagedKeyIsIntVectorISMC::UpdateKeyWithDifferentSizeArray(
//	FIntVector InputKey,
//	TArray< FTransform >& InputTransformArray) {
//
//}
UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
void UManagedKeyIsIntVectorISMC::GetRatioTransformsForSingleKey(
	FIntVector InputKey,
	int32 InputTick,
	int32 InputRatio,
	bool& SuccessFlag,
	TArray< FTransform >& OutputTransformArray,
	FVector InputScaling) {
	int32 StartIndex, FinishIndex;
	bool ValidKey = false;
	GetFirstLastIndexForKey(InputKey, StartIndex, FinishIndex, ValidKey);
	int32 LocalOffset = InputTick % InputRatio;
	if (ValidKey && LocalOffset >= 0 && LocalOffset < InputRatio) {
		for (int32 CurrentIndex = StartIndex + LocalOffset; CurrentIndex <= FinishIndex; CurrentIndex += InputRatio) {
			FTransform LocalTransform;
			this->GetInstanceTransform(CurrentIndex, LocalTransform);
			FVector FinalScaling = LocalTransform.GetScale3D() * InputScaling;
			LocalTransform.SetScale3D(FinalScaling);
			OutputTransformArray.Add(LocalTransform);
		}
		SuccessFlag = true;
	}
	else {
		SuccessFlag = false;
	}

}
UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
void UManagedKeyIsIntVectorISMC::GetRatioTransformsForAllKeys(
	int32 InputTick,
	int32 InputRatio,
	bool& SuccessFlag,
	TArray< FTransform >& OutputTransformArray,
	FVector InputScaling) {
	TArray<FIntVector> LocalKeyArray;
	CurrentMapKeyToSize.GetKeys(LocalKeyArray);
	int32 LocalOffset = InputTick % InputRatio;
	if (LocalOffset >= 0 && LocalOffset < InputRatio) {
		for (auto& iterKey : LocalKeyArray) {
			int32 StartIndex, FinishIndex;
			bool ValidKey = false;
			GetFirstLastIndexForKey(iterKey, StartIndex, FinishIndex, ValidKey);
			if (ValidKey) {
				for (int32 CurrentIndex = StartIndex + LocalOffset; CurrentIndex <= FinishIndex; CurrentIndex += InputRatio) {
					FTransform LocalTransform;
					this->GetInstanceTransform(CurrentIndex, LocalTransform);
					FVector FinalScaling = LocalTransform.GetScale3D() * InputScaling;
					LocalTransform.SetScale3D(FinalScaling);
					OutputTransformArray.Add(LocalTransform);
				}
			}
		}
		SuccessFlag = true;
	}
	else {
		SuccessFlag = false;
	}
}