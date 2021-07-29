// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuantumGateType.h"
#include "QuantumLandBlueprintFxnLibrary.generated.h"


/**
 * 
 */
UCLASS()
class QUBITLAND_API UQuantumLandBlueprintFxnLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FQuantumDyadicComplexRadical GetDyadicFromComplex(
		FVector2D InputComplex,
		int32 InputPowerOfTwo,
		float ToleranceLevel);
	static FIntVector GetDyadicCodedFromDyadic(
		FQuantumDyadicComplexRadical InputDyadic);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void InitializeQuantumOperatorWithSpecifier(
			UPARAM(ref) FQuantumGateSpecifier& InputRefQuantumGateSpecifier,
			TMap<FIntPoint, FVector2D>& OutputTMapMatrixKetSpace);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void FxnGetDyadicCodedFromDyadic(
			UPARAM(ref) FQuantumDyadicComplexRadical& InputQuantumDyadicComplexRadical,
			FIntVector& OutputCodedIntVector);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void FxnGetDyadicFromComplex(
			UPARAM() FVector2D InputComplex,
			UPARAM() int32 InputPowerOfTwo,
			UPARAM() float ToleranceLevel,
			FQuantumDyadicComplexRadical& OutputQuantumDyadicComplexRadical);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void InitializeQuantumOperator(
			UPARAM() EQuantumGateType InputQuantumGateType,
			UPARAM() uint8 InputQubitCount,
			UPARAM(ref) TArray<uint8>& InputControlQubitArray,
			UPARAM(ref) TArray<uint8>& InputTargetQubitArray,
			//UPARAM(ref) TMap<FIntPoint, FVector2D>& InputRefTMapMatrixKetSpace);
			TMap<FIntPoint, FVector2D>& OutputTMapMatrixKetSpace);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void MultiplyOperatorWithOperatorToOperator(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& MatrixLHS,
			UPARAM(ref) TMap<FIntPoint, FVector2D>& MatrixRHS,
			TMap<FIntPoint, FVector2D>& MatrixOutput);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void MultiplyOperatorWithKetToKet(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& MatrixLHS,
			UPARAM(ref) TMap<int32, FVector2D>& KetRHS,
			TMap<int32, FVector2D>& KetResult);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void MultiplyOperatorWithKetToOperatorKet(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& MatrixLHS,
			UPARAM(ref) TMap<int32, FVector2D>& KetRHS,
			TMap<FIntPoint, FVector2D>& MatrixResult,
			TMap<int32, FVector2D>& KetResult);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetTransitionsFromToSubStates(
			UPARAM(ref) TArray<FIntVector>& InputTransitions,
			UPARAM(ref) TMap<int32, int32>& DimensionalityOfOperation,
			UPARAM(ref) TMap<FIntVector, FIntPoint>& FromToSubStateMap,
			UPARAM(ref) TMap<int32, bool>& OperationErrorFlag,
			UPARAM(ref) TMap<FIntVector, bool>& TransitionErrorFlag);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetSingleTransitionFromToSubStates(
			UPARAM() FIntVector InputTransition,
			UPARAM(ref) TArray<FIntVector>& InputTransitions,
			UPARAM(ref) TMap<int32, int32>& DimensionalityOfOperation,
			UPARAM(ref) TMap<FIntVector, FIntPoint>& FromToSubStateMap,
			UPARAM(ref) TMap<int32, bool>& OperationErrorFlag,
			UPARAM(ref) TMap<FIntVector, bool>& TransitionErrorFlag);
	//UFUNCTION(BlueprintCallable, Category = "Analytics")
	//	static bool StartSession();
	UFUNCTION(BlueprintCallable, Category = "Quantum Computin Libraryg")
		static void GetTranstionPatterns(
			UPARAM() TArray<FIntVector>& InputTransitions,
			TMap<int32, int32>& FromToConstantDimensionalityOfOperation,
			TMap<int32, int32>& FromToMaxDimensionalityOfOperation,
			TMap<FIntPoint, int32>& FromToStateMapCount,
			TMap<FIntPoint, int32>& FromToStateMapSingle,
			TMap<FIntPoint, FIntPoint>& FromToStateMapDouble,
			TMap<int32, int32>& ToFromConstantDimensionalityOfOperation,
			TMap<int32, int32>& ToFromMaxDimensionalityOfOperation,
			TMap<FIntPoint, int32>& ToFromStateMapCount,
			TMap<FIntPoint, int32>& ToFromStateMapSingle,
			TMap<FIntPoint, FIntPoint>& ToFromStateMapDouble,
			//TMap<FIntVector, bool>& FromToSubStateMap,
			TMap<int32, bool>& OperationErrorFlag,
			TMap<FIntVector, bool>& TransitionErrorFlag);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void ReturnNormalsPerOperation(
			UPARAM(ref) TMap<FIntVector, FVector2D>& TransitionMatrices,
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InitialKets,
			TMap<int32, float>& MaxSizeOutput,
			TMap<int32, float>& MaxSizeKetOutput,
			TMap<int32, float>& MaxSizeTransitionOutput);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void CombineIntPointMapToIntVectorMapComplexValues(
			UPARAM(ref) TMap<FIntVector, FVector2D>& RefTargetMap,
			UPARAM() TMap<FIntPoint, FVector2D>& InputAppendMap,
			UPARAM() int32 InputFirstCoord,
			TMap<FIntVector, FVector2D>& CoordinateCollisions);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void CombineIntMapToIntPointMapComplexValues(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& RefTargetMap,
			UPARAM() TMap<int32, FVector2D>& InputAppendMap,
			UPARAM() int32 InputFirstCoord,
			TMap<FIntPoint, FVector2D>& CoordinateCollisions);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetAllTransitionOperationKet(
			UPARAM(ref) TArray<FQuantumGateSpecifier>& GateArray,
			UPARAM(ref) TMap<int32, FVector2D>& StartingKet,
			TMap<FIntVector, FVector2D>& OperationsMatrices,
			TMap<FIntVector, FVector2D>& TransitionsMatrices,
			TMap<FIntPoint, FVector2D>& InitialKets);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetAllTransitionOperationKetFlagged(
			UPARAM(ref) TArray<FQuantumGateSpecifier>& GateArray,
			UPARAM(ref) TMap<int32, FVector2D>& StartingKet,
			UPARAM() int32 InputQubitCount,
			TMap<FIntVector, FVector2D>& OperationsMatrices,
			TMap<FIntVector, FVector2D>& TransitionsMatrices,
			TMap<FIntPoint, FVector2D>& InitialKets,
			bool& SuccessFlag);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetTransitionPhaseBlocksTransformArray(
			UPARAM() float TargetSizeSubBlocks,
			UPARAM() float WidthSubBlocks,
			UPARAM() float BaseRadius,
			UPARAM() float TransitionRadiusFraction,
			UPARAM() float AngleStartDegrees,
			UPARAM() float AngleEndDegrees,
			UPARAM() float SpokeProportionStart,
			UPARAM() float SpokeProportionEnd,
			UPARAM() FVector StartPosition,
			UPARAM() FVector EndPosition,
			UPARAM() FVector DimensionsOfStaticRectangularMesh,
			UPARAM() FVector TowardsZeroDegreesNormalizedDirection,
			UPARAM() FVector FlattenedOriginPosition,
			UPARAM() int32 SubBlockHighlightMultiplier,
			TArray<FTransform>& TransformBlockArray,
			TArray<int32>& SubBlockHighlightOffsets);
			//TArray<FTransform>& TransformBlockArrayFlattened);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetTransitionFlattenedTransformArray(
			UPARAM() int32 NumberOfBlocks,
			UPARAM() float LengthSizeSubBlocks,
			UPARAM() float WidthSubBlocks,
			UPARAM() float BaseRadius,
			UPARAM() float TransitionRadiusFraction,
			UPARAM() float AngleStartDegrees,
			UPARAM() float AngleEndDegrees,
			UPARAM() FVector FlattenedOriginPosition,
			UPARAM() FVector DimensionsOfStaticRectangularMesh,
			UPARAM() FVector DirectionOfZeroDegrees,
			UPARAM() FVector AxisOfRotation,
			TArray<FTransform>& TransformBlockArrayFlattened);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetFlattenedTransformArrayPlaneZY(
			UPARAM() int32 NumberOfBlocks,
			UPARAM() float LengthSizeSubBlocks,
			UPARAM() float WidthSubBlocks,
			UPARAM() float BaseRadius,
			UPARAM() float TransitionRadiusFraction,
			UPARAM() float AngleStartDegrees,
			UPARAM() float AngleEndDegrees,
			UPARAM() FVector FlattenedOriginPosition,
			UPARAM() FVector DimensionsOfStaticRectangularMesh,
			//UPARAM() FVector DirectionOfZeroDegrees,
			//UPARAM() FVector AxisOfRotation,
			TArray<FTransform>& TransformBlockArrayFlattened);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetFlattenedFromStartRadiusTransformArrayPlaneZY(
			UPARAM() int32 NumberOfBlocks,
			UPARAM() float LengthSizeSubBlocks,
			UPARAM() float WidthSubBlocks,
			UPARAM() float BaseRadius,
			UPARAM() float TransitionRadiusFraction,
			UPARAM() float AngleStartDegrees,
			UPARAM() float AngleEndDegrees,
			UPARAM() float SpokeProportionStart,
			UPARAM() float SpokeProportionEnd,
			UPARAM() FVector FlattenedOriginPosition,
			UPARAM() FVector DimensionsOfStaticRectangularMesh,
			//UPARAM() FVector DirectionOfZeroDegrees,
			//UPARAM() FVector AxisOfRotation,
			TArray<FTransform>& TransformBlockArrayFlattened);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
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
			UPARAM() FVector DimensionsOfStaticRectangularMesh,
			UPARAM() FVector TowardsViewerNormalizedDirection,
			UPARAM() int32 SubBlockHighlightMultiplier,
			TArray<FTransform>& TransformBlockArray,
			TArray<int32>& SubBlockHighlightOffsets);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetRectangularTransformPointToPointFromZ(
			UPARAM() FVector StartPosition,
			UPARAM() FVector EndPosition,
			UPARAM() FVector DimensionsOfStaticRectangularMesh,
			UPARAM() float ThicknessX,
			UPARAM() float ThicknessY,
			UPARAM() FVector DirectionTowardsAxisY,
			FTransform& TransformOfRectangle);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetPathOfIntVectorMapToVector2D(
			UPARAM(ref) TMap<FIntVector, FVector2D>& TransitionToKetMap,
			UPARAM() bool StackingPositionsFlag,
			TMap<FIntVector, FVector2D>& OutputStartPoints,
			TMap<FIntVector, FVector2D>& OutputStopPoints);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetPathOfIntPointMapToVector2D(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& KetToKetMap,
			UPARAM() bool StackingPositionsFlag,
			TMap<FIntPoint, FVector2D>& OutputStartPoints,
			TMap<FIntPoint, FVector2D>& OutputStopPoints);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetMagnitudePositivePhaseInDegrees(
			UPARAM() FVector2D InputVector2D,
			float& OutputMagnitude,
			float& OutputPhase);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetCubeTransformToDialFacingY(
			UPARAM() FVector StartLocation,
			UPARAM() float DepthBounds,
			UPARAM() float Thickness,
			UPARAM() float Magnitude,
			UPARAM() float AngleFromPlusX,
			UPARAM() FVector SizeOfSM,
			FTransform& TransformOfCube);

	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
	//	static void GetCameraFromDirectionAndPoints(
	//		UPARAM() FVector StartLocation,
	//		UPARAM() float DepthBounds,
	//		UPARAM() float Thickness,
	//		UPARAM() float Magnitude,
	//		UPARAM() float AngleFromPlusX,
	//		UPARAM() FVector SizeOfSM,
	//		FTransform& TransformOfCube);

	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
	//	static void GetRectangularTransformPointToPointFacingFromZY(
	//		UPARAM() FVector StartPosition,
	//		UPARAM() FVector EndPosition,
	//		UPARAM() FVector DimensionsOfStaticRectangularMesh,
	//		UPARAM() float ThicknessX,
	//		UPARAM() float ThicknessY,
	//		UPARAM() FVector DirectionTowardsAxisY,
	//		FTransform& TransformOfRectangle);
	//static FTransform InternalGetRectangularTransformPointToPointFromZ(
	//	UPARAM() FVector StartPosition,
	//	UPARAM() FVector EndPosition,
	//	UPARAM() FVector DimensionsOfStaticRectangularMesh,
	//	UPARAM() FVector OffsetCenterStaticRectangularMesh,
	//	UPARAM() float ThicknessX,
	//	UPARAM() float ThicknessY,
	//	UPARAM() FVector DirectionTowardsAxisY,
	//	FTransform& TransformOfRectangle);
	
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
	//	static void InitializeQuantumOperatorGeneric(
	//		UPARAM() EQuantumGateType InputQuantumGateType,
	//		UPARAM() uint8 InputQubitCount,
	//		UPARAM(ref) TArray<uint8>& InputControlQubitArray,
	//		UPARAM(ref) TArray<uint8>& InputTargetQubitArray,
	//		//UPARAM(ref) TMap<FIntPoint, FVector2D>& InputRefTMapMatrixKetSpace);
	//		TMap<FIntPoint, FVector2D>& OutputTMapMatrixKetSpace);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetCylindricalTransformPointToPointFromZ(
			UPARAM() FVector StartPosition,
			UPARAM() FVector EndPosition,
			UPARAM() FVector DimensionsOfStaticCylindricalMesh,
			UPARAM() float InputRadius,
			UPARAM() FVector DirectionTowardsAxisY,
			FTransform& TransformOfCylinder);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetSubsetMapIntVector(
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputMap,
			UPARAM(ref) TArray<FIntVector>& InputArray,
			TMap<FIntVector, FVector2D>& OutputMap,
			TArray<FIntVector>& RejectedArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetSubsetMapIntPoint(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputMap,
			UPARAM(ref) TArray<FIntPoint>& InputArray,
			TMap<FIntPoint, FVector2D>& OutputMap,
			TArray<FIntPoint>& RejectedArray);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void FxnGetValidDivisor(
			UPARAM(ref) TArray<FVector2D>& InputArray,
			UPARAM(ref) int32 MaximumToCheck,
			UPARAM(ref) float ToleranceLevel,
			bool& FoundValidDivisor,
			int32& OutputExponentialLevel);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
	//	static void GetSumFromIntVectorMapToVector2D(
	//		UPARAM(ref) TMap<FIntVector, FVector2D>& InputMap,
	//		FVector2D& SumValue);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
	//	static void GetSumFromIntPointMapToVector2D(
	//		UPARAM(ref) TMap<FIntPoint, FVector2D>& InputMap,
	//		FVector2D& SumValue);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetMaxMagFromIntVectorMapToVector2D(
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputMap,
			float& MaxMagnitude);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetMaxMagFromIntPointMapToVector2D(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputMap,
			float& MaxMagnitude);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetNormalizedIntVectorMapToVector2D(
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputMap,
			TMap<FIntVector, FVector2D>& OutputMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetNormalizedIntPointMapToVector2D(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputMap,
			TMap<FIntPoint, FVector2D>& OutputMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetNormalizedToValueIntVectorMapToVector2D(
			UPARAM() float InputMax,
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputMap,
			TMap<FIntVector, FVector2D>& OutputMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetNormalizedToValueIntPointMapToVector2D(
			UPARAM() float InputMax,
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputMap,
			TMap<FIntPoint, FVector2D>& OutputMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetNormalizedToKetsTransitions(
			UPARAM() bool LockNormalization,
			UPARAM() bool NormalizeIntVector,
			UPARAM() bool NormalizeIntPoint,
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputIntVectorMap,
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputIntPointMap,
			TMap<FIntVector, FVector2D>& OutputIntVectorMap,
			TMap<FIntPoint, FVector2D>& OutputIntPointMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetNormalizedSingleKetToTransitions(
			UPARAM() bool NormalizePathFlag,
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputIntVectorMap,
			TMap<FIntVector, FVector2D>& OutputIntVectorMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetMasterNormalizeIndexMaps(
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputIntVectorMap,
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputIntPointMap,
			//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
			//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
			bool& PositiveValueFlag,
			float& OutputMaxValue);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void GetRunningSumValues(
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputMap,
			UPARAM() bool& SuccessFlag,
			TMap<FIntVector, FTwoVectors>& OutputMap);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void FxnGetIntVectorDyadicMapFromIntVectorComplex(
			UPARAM(ref) TMap<FIntVector, FVector2D>& InputMapIntVectorToComplex,
			UPARAM(ref) float ToleranceLevel,
			UPARAM(ref) int32 InputPowerOfTwo,
			TMap<FIntVector, FQuantumDyadicComplexRadical>& OutputMapIntVectorToDyadic,
			bool& SuccessFlag);
	UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
		static void FxnGetIntPointDyadicMapFromIntPointComplex(
			UPARAM(ref) TMap<FIntPoint, FVector2D>& InputMapIntVectorToComplex,
			UPARAM(ref) float ToleranceLevel,
			UPARAM(ref) int32 InputPowerOfTwo,
			TMap<FIntPoint, FQuantumDyadicComplexRadical>& OutputMapIntVectorToDyadic,
			bool& SuccessFlag);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Computing Library")
	//	static void NewFunction(
	//		UPARAM(ref) TMap<FIntVector, FVector2D>& InputIntVectorMap,
	//		UPARAM(ref) TMap<FIntPoint, FVector2D>& InputIntPointMap,
	//		//TMap<FIntVector, FVector2D>& OutputIntVectorMap,
	//		//TMap<FIntPoint, FVector2D>& OutputIntPointMap,
	//		bool& PositiveValueFlag,
	//		float& OutputMaxValue);
	// /////////////////////////////////// ///////////////////////////////////
	// /////////////////////////////////// ///////////////////////////////////
	// /////////////////////////////////// ///////////////////////////////////
	// BEGIN STUFF THAT NEEDS IMPLEMENTING ///////////////////////////////////
	// /////////////////////////////////// ///////////////////////////////////
	// /////////////////////////////////// ///////////////////////////////////
	// /////////////////////////////////// ///////////////////////////////////

};
