// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineBaseTypes.h"
#include "FxnLibFURL.generated.h"

/**
 * 
 */
UCLASS()
class QUBITLAND_API UFxnLibFURL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing")
		static void TestLibFxn(
			//UPARAM(ref) FQuantumGateSpecifier& InputRefFQuantumGateSpecifier,
			//UPARAM(ref) TMap<FIntPoint, FVector2D>& InputRefTMapMatrixKetSpace);
			TMap<FIntPoint, FVector2D>& OutputTMapMatrixKetSpace);

};
