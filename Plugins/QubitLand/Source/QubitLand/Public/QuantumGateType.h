// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "QuantumGateType.generated.h"

UENUM(BlueprintType)
enum class EQuantumGateType : uint8
{
	Identity,
	Hadamard,
	X,
	Y,
	Z,
	T,
	TDagger,
	S,
	SDagger,
	CX,
	CustomUnitary,
	SWAP,
	CSWAP,
	CCX,
	MCT,
	Measurement,
	Invalid,
};
UENUM(BlueprintType)
enum class EMaterialInterface : uint8
{
	Yellow,
	Teal,
	Magenta,
	Black,
	White,
	ScanLines,
	Blue,
	Green,
	Gray,
};
UENUM(BlueprintType)
enum class EPhaseShiftLevel : uint8
{
	NoShift, // 0 or 0*Pi
	Z180, // 180 or Pi
	S90, // 90 or Pi/2
	SDagger270, // 270 or 3*Pi/2
	T45, // 45 or Pi/4
	TDagger315, // 315 or 7*Pi/8
	NonStandardShift, // Shift outside Clifford+T basis
};
UENUM(BlueprintType)
enum class EActualISMC : uint8
{
	YellowCube,
	YellowArrowFacingYTowardsPivotX,
	TealCube,
	TealCylinderZ,
	TealTubeZ,
	MagentaCube,
	MagentaCylinderZ,
	BlackCube,
	BlackCylinderZ,
	BlackSplitter,
	BlueCylinderZ,
	BlueTextZero,
	GreenCylinderZ,
	GreenTextOne,
	WhiteArrowFacingYTowardsPivotX,
	ScanLinesCylinderRadialSurfaceZ,
	GreyCube,
};
UENUM(BlueprintType)
enum class EMeshISMC : uint8
{
	CylinderZ,
	TubeZ,
	CylinderRadialSurfaceZ,
	Cube,
	ArrowFacingYTowardsPivotX,
	Splitter,
	ZeroText,
	OneText,
};
UENUM(BlueprintType)
enum class EKetDisplayISMC : uint8
{
	MainDisplayBox,
	CylinderMainStateMagnitude,
	CylinderMainStateEdge,
	CylinderMainStateInner,
	FinalKetStateArrow,
	FinalKetDirection,
	//FinalKetPhaseArrowDial,
	//SurroundingDisplayBox,
};
UENUM(BlueprintType)
enum class EQuantumCircuitPiece : uint8
{
	OperationCoord,
	TransitionCoord,
	InitialKetCoord,
	FinalKetCoord,
	OperationRowTo,
	OperationColumnFrom,
	TransitionRowTo,
	TransitionColumnFrom,
	OperationIndex,
	EntireStateOperationDisplay,
	EntireCircuitDisplay,
};
UENUM(BlueprintType)
enum class ETransitionISMC : uint8
{
	WaveSpokesForTransitionsStartToTurn,
	WaveSpokesForTransitionsTurnToStop,
	WaveSpokesForTransitionsOutward,
	WaveSpokesForTransitionsFlattened,
	CoreCylindersStartToTurn,
	CoreCylindersTurnToStop,
	CoreCylindersOutward,
	WaveSplittersSubstate,
	BrightPiecesOfFInalSubstateDirection,
	BoundingCylindersStartToTurn,
	BoundingCylindersTurnToStop,
	BoundingCylindersOutward,
	DiscSubstateBackground,
	DiscSubstateEdge,
	DiscSubstateCenter,
	KetSubstateArrow,
	KetSubstateAddedArrow,
	TipSpokesForTransitionsStartToTurn,
	TipSpokesForTransitionsTurnToStop,
	TipSpokesForTransitionsOutward,
	TipSpokesForTransitionsFlattened,
};
UENUM(BlueprintType)
enum class EQubitSplitISMC : uint8
{
	QubitLines,
	QubitSplitLabel,
	QubitSplitTunnelParent,
	QubitSplitTunnelParentZeroFalse,
	QubitSplitTunnelParentOneTrue,
	QubitSplitOpKetLabelBox,
	QubitSplitOpKetQubitLabelZeroFalse,
	QubitSplitOpKetQubitLabelOneTrue,
};


USTRUCT(BlueprintType)
struct FQuantumDyadicComplexRadical
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 NumeratorReal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool RationalReal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 NumeratorImaginary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool RationalImaginary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 PowerOfTwoDenominator;
};

USTRUCT(BlueprintType)
struct FQuantumDisplayParam
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int SubBlockMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool NormalizeKets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool NormalizeTransitions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ReverseKetOrderFlag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector Spacing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector Padding;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector SubBlockSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SubBlockLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SubBlockThickness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MainDiameterAsFractionOfKetZSubStateSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float InnerRadiusAsFractionOfMainRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float FillProportionPhaseWaveXOfSpacingX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float FillProportionMainStateBoundsXOfMainPlusSubBoundsX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector MainStateProportionOfBounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SubstateProportionOfBoundsZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float FillProportionCylinderMainStateRadiusOfSmallestBoxDimension;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SpokeTipsProportionStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SpokeTipsProportionStop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ProportionalSubstateCenterDisc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ProportionalMainStateCenterDisc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetSubstateBackgroundAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetSubstateEdgeAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetSubstateCentralDiscAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetSubstateSpokesAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetSubstateArrowAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetMainStateEdgeAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetMainStateCentralDiscAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetMainStateAddedArrowsAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetMainStateFinalArrowAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetMainStatePhaseOnlyArrowAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetMainStateMagnitudeAxisY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ThicknessSubstateDisc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ThicknessSubstateArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ThicknessMainStateAddedArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ThicknessMainStateFinalArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DepthCylinderQubitSplitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DiameterCylinderQubitSplitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DiameterCylinderQubitSplitBeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SubBlockSpokeDepth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SubBlockTipDepth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SpacingTextZeroOneX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetTextZeroOneY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OffsetPhaseTipsFromSpokes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AdditionalDiameterToWaveSplitter;
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Parameters")
	//	static void GetPositionStartSubstate(
	//		UPARAM() FIntVector InputTransition, 
	//		FVector OutputPositionStart);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Parameters")
	//	static void GetPositionTurnSubstate(
	//		UPARAM() FIntVector InputTransition,
	//		FVector OutputPositionStart);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Parameters")
	//	static void GetPositionEndSubstate(
	//		UPARAM() FIntVector InputTransition,
	//		FVector OutputPositionStart);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Parameters")
	//	static void GetPositionOutwardsBackSubstate(
	//		UPARAM() FIntVector InputTransition,
	//		FVector OutputPositionStart);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Parameters")
	//	static void GetPositionOutwardsFrontSubstate(
	//		UPARAM() FIntVector InputTransition,
	//		FVector OutputPositionStart);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Parameters")
	//	static void GetSubstateRadius(
	//		UPARAM() float InputOperationIndex,
	//		float OutputRadius);
	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Parameters")
	//	static void GetDimensionsMainStateBox(
	//		UPARAM() int32 InputOperationIndex,
	//		float OutputPositionStart);
};
USTRUCT(BlueprintType)
struct FQuantumDisplayDerived
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionTurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionStop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionOutwardsBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionOutwardsFront;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionSplitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, FVector> MapPositionKetInitialMainState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, FVector> MapPositionKetInitialMainState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector SizeKetsMainSubOperationBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector SizeMainStateBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap < int32, FVector> MapBoundsSubstate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< int32, float> MapIndexToBaseRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, float> MapMainStateMagnitudesFinalized;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, float> MapMainStatePhasesFinalized;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, float> MapSubstateMagnitudesFinalized;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, float> MapSubstateMainPortionMagnitudesFinalized;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, float> MapToSubstateAngleStarting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, float> MapToSubstateAngleFinal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< int32, float> MapToSubstateMaximumMagnitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< int32, float> MapToMainStateMaximumMagnitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FTwoVectors> MapToSubstateAddedTwoVectors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, FVector> MapToQubitSplitPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, float> MapToSubstateMagnitudes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, float> MapToSubstateAngles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, float> MapToMainKetStateMagnitudes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, float> MapToMainKetStateAngles;
};
USTRUCT(BlueprintType)
struct FQuantumKetDisplay
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool NonZeroKet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform MainBoxTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform EdgeCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform InnerCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform MagnitudeCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform FinalKetStateArrowTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform FinalKetDirectionTransform;
	//FQuantumKetDisplayBox();

};
USTRUCT(BlueprintType)
struct FQuantumQubitSplitDisplay
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<int32, FTransform> QubitLines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FTransform> QubitSplitLabelTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FTransform> QubitSplitTunnelParentTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FTransform> QubitSplitTunnelZeroFalseParentTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FTransform> QubitSplitTunnelOneTrueParentTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FTransform> OpKetLabelBoxTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntVector, FTransform> OpKetQubitLabelZeroOneTransforms;
};
USTRUCT(BlueprintType)
struct FQuantumMeshAndDetailsISMC
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UStaticMesh* StaticMeshOfISMC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<UMaterialInterface*> MaterialMain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<UMaterialInterface*> MaterialGlow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<UMaterialInterface*> MaterialMovingHighlight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector MeshSizeVector;
	//FQuantumKetDisplayBox();
};
USTRUCT(BlueprintType)
struct FQuantumTransitionDisplay
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> StartToTurnPhaseBarsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> StartToTurnPhaseTipsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform StartToTurnInnerCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform StartToTurnBoundingCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> TurnToStopPhaseBarsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> TurnToStopPhaseTipsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform TurnToStopInnerCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform TurnToStopBoundingCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> OutwardsPhaseBarsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> OutwardsPhaseTipsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform OutwardsInnerCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform OutwardsBoundingCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> FlattenedPhaseBarsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> FlattenedPhaseTipsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform SplitterTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform EdgeCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform BackgroundCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform InnerCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform KetSubstateFinalArrowTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform KetSubstateAddedArrowTransform;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> DirectionAddedArrowsTransforms;
};
USTRUCT(BlueprintType)
struct FQuantumTransitionDisplaySimplified
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> StartToTurnTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> TurnToStopTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> OutwardsTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> FlattenedTransforms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform EdgeCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform BackgroundCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform InnerCylinderTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> DirectionAddedArrowsTransforms;
};
//USTRUCT(BlueprintType)
//struct FQuantumKetDisplay
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntVector, FQuantumTransitionDisplay> DisplayTransitionMap;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FQuantumKetDisplay> DisplayKetMap;
//
//};

USTRUCT(BlueprintType)
struct FQuantumGateSpecifier
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EQuantumGateType EnumGateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 QubitCount;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 ControlQubit;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 TargetQubit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<uint8> ControlQubitArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<uint8> TargetQubitArray;
	FQuantumGateSpecifier();
	int32 InitializeQuantumGate(EQuantumGateType InputGateType, uint8 InputQubitCount, TArray<uint8> InputControlQubitArray, TArray<uint8> InputTargetQubitArray);
	//	: EnumGateType{ InputGateType }, QubitCount{ InputQubitCount }, ControlQubitArray{ InputControlQubitArray }, TargetQubitArray{ InputTargetQubitArray }
	//{
	//	for (auto& iter : ControlQubitArray) {
	//		if (iter >= QubitCount) {
	//			EnumGateType = EQuantumGateType::Invalid;
	//		}
	//	}
	//	for (auto& iter : TargetQubitArray) {
	//		if (iter >= QubitCount) {
	//			EnumGateType = EQuantumGateType::Invalid;
	//		}
	//	}
	//}
	uint8 GetMinimumQubitsGateSpecifier();
	//{
	//	if (ControlQubitArray.Max() > TargetQubitArray.Max()) {
	//		LocalValue = ControlQubitArray[0];
	//	}
	//	uint8 LocalValue;
	//	if (EnumGateType == EQuantumGateType::CX) {
	//		if (ControlQubitArray[0] > TargetQubitArray[0]) {
	//			LocalValue = ControlQubit + 1;
	//		}
	//		else {
	//			LocalValue = TargetQubit + 1;
	//		}
	//	}
	//	else if (EnumGateType == EQuantumGateType::CustomUnitary || EnumGateType == EQuantumGateType::Identity) {
	//		LocalValue = 0;
	//	}
	//	else {
	//		LocalValue = TargetQubitArray[0] + 1;
	//	}
	//	return LocalValue;
	//}
};

//
//USTRUCT(BlueprintType)
//struct FQuantumGateImplemented : public FQuantumGateSpecifier
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FVector2D> MatrixFromTo;
//	FQuantumGateImplemented();
//	int32 InitializeGateImplemented(EQuantumGateType InputGateType, uint8 InputQubitCount, TArray<uint8> InputControlQubitArray, TArray<uint8> InputTargetQubitArray);
//	//	: EnumGateType{ InputGateType }, QubitCount{ InputQubitCount }, ControlQubitArray{ InputControlQubitArray }, TargetQubitArray{ InputTargetQubitArray }
//	//{
//	//	for (auto& iter : ControlQubitArray) {
//	//		if (iter >= QubitCount) {
//	//			EnumGateType = EQuantumGateType::Invalid;
//	//		}
//	//	}
//	//	for (auto& iter : TargetQubitArray) {
//	//		if (iter >= QubitCount) {
//	//			EnumGateType = EQuantumGateType::Invalid;
//	//		}
//	//	}
//	//}
//	uint8 GetMinimumQubitsGateSpecifier();
//	//{
//	//	if (ControlQubitArray.Max() > TargetQubitArray.Max()) {
//	//		LocalValue = ControlQubitArray[0];
//	//	}
//	//	uint8 LocalValue;
//	//	if (EnumGateType == EQuantumGateType::CX) {
//	//		if (ControlQubitArray[0] > TargetQubitArray[0]) {
//	//			LocalValue = ControlQubit + 1;
//	//		}
//	//		else {
//	//			LocalValue = TargetQubit + 1;
//	//		}
//	//	}
//	//	else if (EnumGateType == EQuantumGateType::CustomUnitary || EnumGateType == EQuantumGateType::Identity) {
//	//		LocalValue = 0;
//	//	}
//	//	else {
//	//		LocalValue = TargetQubitArray[0] + 1;
//	//	}
//	//	return LocalValue;
//	//}
//};
//USTRUCT(BlueprintType)
//struct FQuantumDisplayManagerISMC
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> NormalMaterialMap;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> GlowMaterialMap;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> HighlightMaterialMap;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, UStaticMesh*> MapStaticMesh;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, FVector> MapSizeMesh;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, FRotator> MapRotatorMeshZY;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EKetDisplayISMC, EActualISMC> DisplyKetToActualISMC;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<ETransitionISMC, EActualISMC> DisplyTransitionToActualISMC;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EQubitSplitISMC, EActualISMC> DisplyQubitSplitToActualISMC;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntVector, FQuantumTransitionDisplay> MapIntVectorTransitionDisplay;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FQuantumKetDisplay> MapIntPointKetDisplay;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumQubitSplitDisplay QubitSplitDisplay;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumDisplayParam QubitDisplayDerived;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumDisplayDerived QubitDisplayParam;
//
//	//FQuantumKetDisplayBox();
//};
