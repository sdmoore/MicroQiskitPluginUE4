// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuantumLandBlueprintFxnLibrary.h"
#include "MultiMapIntegerActorComponent.h"
#include "QuantumGateType.h"
#include "QCDisplayBlueprintFxnLibrary.generated.h"

/**
 * 
 */

UCLASS()
class QUBITLAND_API UQCDisplayBlueprintFxnLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetQuantumDisplayBasicCoord(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
			UPARAM() FIntVector OperationQubitInitialKet,
			FVector& OutputVector);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetQuantumDisplaySubstate(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
			UPARAM() FIntVector OperationQubitInitialKet,
			UPARAM() int32 SubstateValue,
			UPARAM() float SubstateBoundsZ,
			FVector& OutputVector);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetQuantumDisplayDerived(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputOperationMap,
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputTransitionMap,
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputInitialKetMap,
			UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
			FQuantumDisplayDerived& OutputQuantumDisplayDerived);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetQuantumDisplaySubstateOffsetZ(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
			UPARAM() int32 OperationIndex,
			UPARAM() int32 SubstateValue,
			UPARAM() float SubstateBoundsZ,
			float& OutputOffset);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void InitializeQuantumKetMainStateDisplay(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InParam, //InputDisplayParam,
			UPARAM(ref) FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
			UPARAM() int32 OperationIndex,
			UPARAM() int32 KetState,
			bool& SuccessFlag,
			FQuantumKetDisplay& OutKetDisplay);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void InitializeQuantumTransitionSubstateDisplay(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InParam, //InputDisplayParam,
			UPARAM(ref) FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
			UPARAM() int32 OperationIndex,
			UPARAM() int32 KetStateFrom,
			UPARAM() int32 KetStateTo,
			bool& SuccessFlag,
			FQuantumTransitionDisplay& OutSubstateDisplay);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void InitializeQuantumTransitionSubstateDisplaySimplified(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InParam, //InputDisplayParam,
			UPARAM(ref) FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
			UPARAM() int32 OperationIndex,
			UPARAM() int32 KetStateFrom,
			UPARAM() int32 KetStateTo,
			bool& SuccessFlag,
			FQuantumTransitionDisplaySimplified& OutSubstateDisplay);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void DisplayQuantumDerived(
			UPARAM(ref) FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
			TArray<FString>& OutputStringArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void DisplayQuantumDisplayKet(
			UPARAM(ref) FQuantumKetDisplay& InKet, //InputQuantumDisplayDerived,
			TArray<FString>& OutputStringArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void InitializeQubitSplitDisplay(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InParam, //InputDisplayParam,
			UPARAM(ref) FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
			FQuantumQubitSplitDisplay& OutQubitSplitDisplay);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetRectangleTransformDirectionZ(
			UPARAM() FVector StartPosition,
			UPARAM() FVector EndPosition,
			UPARAM() float LengthX,
			UPARAM() float DepthY,
			UPARAM() FVector DirectionTowardsAxisY,
			FTransform& OutputTransform);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetTransitionBlocksTransformArray(
			UPARAM() float TargetSizeSubBlocks,
			UPARAM() float WidthSubBlocks,
			UPARAM() float BaseRadius,
			UPARAM() float TransitionRadiusFraction,
			UPARAM() float RadiusFinalFractionStart,
			UPARAM() float AngleStartDegrees,
			UPARAM() float AngleEndDegrees,
			UPARAM() FVector StartPosition,
			UPARAM() FVector EndPosition,
			UPARAM() FVector TowardsZeroDegrees,
			UPARAM() FVector EvolutionDirection,
			UPARAM() bool FixedAtEndPositionFlag,
			UPARAM() int32 SubBlockHighlightMultiplier,
			TArray<FTransform>& TransformBlockArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetTransitionPhaseBlocksFromStartRadiusTransformArray(
			UPARAM() float TargetSizeSubBlocks,
			UPARAM() float WidthSubBlocks,
			UPARAM() float BaseRadius,
			UPARAM() float TransitionRadiusFraction,
			UPARAM() float RadiusFinalFractionStart,
			UPARAM() float AngleStartDegrees,
			UPARAM() float AngleEndDegrees,
			UPARAM() FVector StartPosition,
			UPARAM() FVector EndPosition,
			UPARAM() FVector TowardsZeroDegrees,
			UPARAM() FVector EvolutionDirection,
			UPARAM() bool FixedAtEndPositionFlag,
			UPARAM() int32 SubBlockHighlightMultiplier,
			TArray<FTransform>& TransformBlockArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetTransitionPhaseBlocksFromStartRadiusTransformSingle(
			UPARAM() float WidthSubBlocks,
			UPARAM() float BaseRadius,
			UPARAM() float TransitionRadiusFraction,
			UPARAM() float RadiusFinalFractionStart,
			UPARAM() float AngleStartEndDegrees,
			UPARAM() FVector StartPosition,
			UPARAM() FVector EndPosition,
			UPARAM() FVector TowardsZeroDegrees,
			UPARAM() bool ReflectedFlag,
			FTransform& TransformSingle);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void AddTransformsTransition(
			UPARAM(ref) TMap< ETransitionISMC, FVector>& MapSizesISMC,
			UPARAM(ref) FQuantumTransitionDisplay& SubstateDisplayToAdd,
			UPARAM(ref) TMap < ETransitionISMC, UInstancedStaticMeshComponent*>& MapISMC);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void AddTransformsKetState(
			UPARAM(ref) TMap< EKetDisplayISMC, FVector>& MapSizesISMC,
			UPARAM(ref) FQuantumKetDisplay& MainStateDisplayToAdd,
			UPARAM(ref) TMap <EKetDisplayISMC, UInstancedStaticMeshComponent*>& MapKetsISMC);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetTransformsKetState(
			UPARAM(ref) TMap< EKetDisplayISMC, FVector>& MapSizesISMC,
			UPARAM(ref) FQuantumKetDisplay& MainStateDisplayToAdd,
			TMap <FIntPoint, FTransform>& MapKetsTransforms);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
	//	static void GetQuantumDisplayBranchCoordMap(
	//		UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
	//		UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
	//		TMap<FIntPoint, FVector>& OutputBranchingCoord);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void AddTransformsQubitSplit(
			UPARAM(ref) TMap< EQubitSplitISMC, FVector>& MapSizesISMC,
			UPARAM(ref) FQuantumQubitSplitDisplay& InQubitSplitDisplay,
			UPARAM(ref) TMap <EQubitSplitISMC, UInstancedStaticMeshComponent*> MapQubitSplitISMC);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void GetQuantumDisplayBasicOperationKetBounds(
			UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
			UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
			UPARAM(ref) FIntPoint& OperationRange,
			UPARAM(ref) FIntPoint& InitialKetRange,
			FTwoVectors& OutputVectorsMinMax);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void SetMeshesToISMC(
			//UPARAM(ref) TMap< EKetDisplayISMC, EActualISMC>& MapKetActualISMC,
			//UPARAM(ref) TMap< ETransitionISMC, EActualISMC>& MapTransitionActualISMC,
			//UPARAM(ref) TMap< EQubitSplitISMC, EActualISMC>& MapQubitSplitActualISMC,
			UPARAM(ref) TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualToISMC,
			UPARAM(ref) TMap< EActualISMC, EMeshISMC>& MapActualToMesh,
			UPARAM(ref) TMap< EMeshISMC, UStaticMesh*>& MapMeshToMeshObject);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void SetAllTransforms(
			UPARAM(ref) TMap< FIntVector, FQuantumTransitionDisplay>& MapSubstateDisplayISMC,
			UPARAM(ref) TMap< FIntPoint, FQuantumKetDisplay>& MapKetDisplayISMC,
			UPARAM(ref) FQuantumQubitSplitDisplay& MapQubitSplitDisplayISMC,
			UPARAM(ref) TMap< ETransitionISMC, EActualISMC>& MapTransitionActualISMC,
			UPARAM(ref) TMap< EKetDisplayISMC, EActualISMC>& MapKetActualISMC,
			UPARAM(ref) TMap< EQubitSplitISMC, EActualISMC>& MapQubitSplitActualISMC,
			UPARAM(ref) TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualObjectISMC,
			UPARAM(ref) TMap< EActualISMC, FVector>& MapActualSizeOfMeshISMC);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void SetSpecificTransforms(
			UPARAM(ref) TMap< FIntVector, FQuantumTransitionDisplay>& MapSubstateDisplayISMC,
			UPARAM(ref) TMap< FIntPoint, FQuantumKetDisplay>& MapKetDisplayISMC,
			UPARAM(ref) FQuantumQubitSplitDisplay& MapQubitSplitDisplayISMC,
			UPARAM(ref) TMap< ETransitionISMC, EActualISMC>& MapTransitionActualISMC,
			UPARAM(ref) TMap< EKetDisplayISMC, EActualISMC>& MapKetActualISMC,
			UPARAM(ref) TMap< EQubitSplitISMC, EActualISMC>& MapQubitSplitActualISMC,
			UPARAM(ref) TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualObjectISMC,
			UPARAM(ref) TMap< EActualISMC, FVector>& MapActualSizeOfMeshISMC,
			//UPARAM(ref) TSet< ETransitionISMC>& SubsetTransitionTargetedArray,
			//UPARAM(ref) TSet< EKetDisplayISMC>& SubsetKetDisplayTargetedArray,
			//UPARAM(ref) TSet< EQubitSplitISMC>& SubsetQubitSplitTargetedArray,
			UPARAM(ref) TArray<int32>& QubitListArray,
			UPARAM(ref) TArray<FIntPoint>& QubitSplitCoordArray,
			UPARAM(ref) TArray<FIntPoint>& OpKetCoordArray,
			UPARAM(ref) TArray<FIntVector>& OpKetQubitCoordArray,
			UPARAM(ref) TArray<FIntVector>& LabelOpKetFromKetToCoordArray,
			UPARAM() float InputGrowthFactor);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void SetMaterialInterfacesToISMC(
			//UPARAM(ref) TMap< EKetDisplayISMC, EActualISMC>& MapKetActualISMC,
			//UPARAM(ref) TMap< ETransitionISMC, EActualISMC>& MapTransitionActualISMC,
			//UPARAM(ref) TMap< EQubitSplitISMC, EActualISMC>& MapQubitSplitActualISMC,
			UPARAM(ref) TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualToISMC,
			UPARAM(ref) TMap< EActualISMC, EMaterialInterface>& MapActualToMaterialInterface,
			UPARAM(ref) TMap< EMaterialInterface, UMaterialInterface*>& MapMaterialInterfaceToMaterialInterfaceObject);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
	//	static void GetQuantumDisplayKetsTransitions(
	//		UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
	//		UPARAM(ref) TMap<FIntVector, FVector2D>& InputTransitionMap,
	//		UPARAM(ref) TMap<FIntPoint, FVector2D>& InputInitialKetMap,
	//		UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
	//		UPARAM(ref) FQuantumDisplayDerived& InputDisplayDerived,
	//		TMap<FIntVector, FQuantumTransitionDisplay> OutputDisplayTransitionMap,
	//		TMap<FIntPoint, FQuantumKetDisplay> OutputDisplayKetMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void DisplayQuantumTransition(
			UPARAM(ref) FQuantumTransitionDisplay& InTransition, //InputQuantumDisplayDerived,
			TArray<FString>& OutputStringArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
		static void AddSpecificTransformsQubitSplit(
			UPARAM(ref) TMap< EQubitSplitISMC, FVector>& MapSizesISMC,
			UPARAM(ref) FQuantumQubitSplitDisplay& InQubitSplitDisplay,
			UPARAM(ref) TMap <EQubitSplitISMC, UInstancedStaticMeshComponent*> MapQubitSplitISMC,
			UPARAM(ref) TArray<FIntVector>& OpKetQubitLabelArray,
			UPARAM(ref) TArray<FIntPoint>& TunnelQubitSplitCoordArray,
			UPARAM(ref) TArray<int32>& QubitLineArray);
};
float GetPositiveAtanTo360(FVector2D InputComplexValue);
