// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "ManagedKeyIsIntVectorISMC.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUBITLAND_API UManagedKeyIsIntVectorISMC : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()
public:
	UManagedKeyIsIntVectorISMC();
	~UManagedKeyIsIntVectorISMC();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TMap< FIntVector, int32 > CurrentMapKeyToSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray< FIntVector > CurrentOrderArrayKey;
	UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
		void GetFirstLastIndexForKey(
			UPARAM() FIntVector InputKey,
			int32& RefInputFirstIndex,
			int32& RefInputLastIndex,
			bool& SuccessFlag);
	UManagedKeyIsIntVectorISMC(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{
		// Initialize CDO properties here.
	}
	UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
		void RemoveKey(
			UPARAM() FIntVector InputKey,
			bool& SuccessFlag);
	UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
		void ClearAllKeys(
			bool& SuccessFlag);
	UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
		void UpdateKeyWithArray(
			UPARAM() FIntVector InputKey,
			UPARAM(ref) TArray< FTransform >& InputTransformArray,
			bool& SuccessFlag);
	UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
		void GetRatioTransformsForSingleKey(
			UPARAM() FIntVector InputKey,
			UPARAM() int32 InputTick,
			UPARAM() int32 InputRatio,
			bool& SuccessFlag,
			TArray< FTransform >& OutputTransformArray,
			UPARAM() FVector InputScaling = FVector(1.0, 1.0, 1.0));
	UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
		void GetRatioTransformsForAllKeys(
			UPARAM() int32 InputTick,
			UPARAM() int32 InputRatio,
			bool& SuccessFlag,
			TArray< FTransform >& OutputTransformArray,
			UPARAM() FVector InputScaling = FVector(1.0, 1.0, 1.0));
	//UFUNCTION(BlueprintCallable, Category = "Custom Managed Instanced Static Mesh")
	//	void AuditInternalData(bool SuccessFlag);
};
