// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/NoExportTypes.h"
#include "QuantumGateType.h"

#include "QuantumCIrcuitDisplayObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType) //ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUBITLAND_API UQuantumCIrcuitDisplayObject : public UObject
{
	GENERATED_BODY()
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntVector, FQuantumKetSubstateDisplay> DisplayTransitionMap;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FQuantumKetMainStateDisplay> DisplayKetMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> NormalMaterialMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> GlowMaterialMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> HighlightMaterialMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, UStaticMesh*> MapStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, FVector> MapSizeMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, FRotator> MapRotatorMeshZY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EKetDisplayISMC, EActualISMC> DisplayKetToActualISMC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<ETransitionISMC, EActualISMC> DisplayTransitionToActualISMC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EQubitSplitISMC, EActualISMC> DisplayQubitSplitToActualISMC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntVector, FQuantumTransitionDisplay> MapIntVectorTransitionDisplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FQuantumKetDisplay> MapIntPointKetDisplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumQubitSplitDisplay QubitSplitDisplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumDisplayParam QubitDisplayDerived;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumDisplayDerived QubitDisplayParam;
};
