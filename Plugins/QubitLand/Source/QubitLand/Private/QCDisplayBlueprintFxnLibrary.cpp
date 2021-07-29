// Fill out your copyright notice in the Description page of Project Settings.


#include "QCDisplayBlueprintFxnLibrary.h"
void UQCDisplayBlueprintFxnLibrary::GetQuantumDisplayBasicCoord(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InputDisplayParam,
	FIntVector OperationQubitInitialKet,
	FVector& OutputVector) {
	FIntVector TempIntVector =
		FIntVector(OperationQubitInitialKet.X,
			OperationQubitInitialKet.Y,
			InputMMIAC->KetStateCount - OperationQubitInitialKet.Z - 1);
	if (InputDisplayParam.ReverseKetOrderFlag) {
		FVector VectorVersionCoord =
			FVector(TempIntVector);
		OutputVector = InputDisplayParam.Spacing * VectorVersionCoord + InputDisplayParam.Padding;
	}
	else {
		FVector VectorVersionCoord = FVector(OperationQubitInitialKet);
		OutputVector = InputDisplayParam.Spacing * VectorVersionCoord + InputDisplayParam.Padding;
	}
	if (OperationQubitInitialKet.X == -1) {
		OutputVector.X = 0.0;
	}
	if (OperationQubitInitialKet.Y == -1) {
		OutputVector.Y = 0.0;
	}
	if (OperationQubitInitialKet.Z == -1) {
		OutputVector.Z = 0.0;
	}
}
void UQCDisplayBlueprintFxnLibrary::GetQuantumDisplayBasicOperationKetBounds(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InputDisplayParam,
	FIntPoint& OperationRange,
	FIntPoint& InitialKetRange,
	FTwoVectors& OutputVectorsMinMax) {
	float MinValueX, MaxValueX, MinValueZ, MaxValueZ;
	MinValueX =
		InputDisplayParam.Spacing.X * OperationRange.X + InputDisplayParam.Padding.X
		- 0.5 * InputDisplayParam.Spacing.X 
		* InputDisplayParam.FillProportionMainStateBoundsXOfMainPlusSubBoundsX
		* (1.0 - InputDisplayParam.FillProportionPhaseWaveXOfSpacingX);
	MaxValueX =
		InputDisplayParam.Spacing.X * OperationRange.Y + InputDisplayParam.Padding.X
		+ 0.5 * InputDisplayParam.Spacing.X 
		* InputDisplayParam.FillProportionMainStateBoundsXOfMainPlusSubBoundsX
		* (1.0 - InputDisplayParam.FillProportionPhaseWaveXOfSpacingX);
	if (InputDisplayParam.ReverseKetOrderFlag) {
		MinValueZ =
			InputDisplayParam.Spacing.Z * InitialKetRange.X + InputDisplayParam.Padding.Z
			- 0.5 * InputDisplayParam.Spacing.Z;
		MaxValueZ =
			InputDisplayParam.Spacing.Z * InitialKetRange.Y + InputDisplayParam.Padding.Z
			+ 0.5 * InputDisplayParam.Spacing.Z;
	}
	else {
		MinValueZ =
			InputDisplayParam.Spacing.Z * InitialKetRange.Y + InputDisplayParam.Padding.Z
			- 0.5 * InputDisplayParam.Spacing.Z;
		MaxValueZ =
			InputDisplayParam.Spacing.Z * InitialKetRange.X + InputDisplayParam.Padding.Z
			+ 0.5 * InputDisplayParam.Spacing.Z;
	}
	OutputVectorsMinMax = FTwoVectors(
		FVector(MinValueX, 0.0, MinValueZ), 
		FVector(MaxValueX, 0.0, MaxValueZ));
}
void UQCDisplayBlueprintFxnLibrary::GetQuantumDisplaySubstate(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InputDisplayParam,
	FIntVector OperationQubitInitialKet,
	int32 SubstateValue,
	float SubstateBoundsZ,
	FVector& OutputVector) {
	int32 SubstateCount = InputMMIAC->IndexToSubstateCount[OperationQubitInitialKet.X];
	float CentralPoint = (SubstateCount - 1.0)/2.0;
	FVector VectorOffsetSubstate = FVector(0.0, 0.0, ((1.0 * SubstateValue) - CentralPoint) * SubstateBoundsZ);
	if (InputDisplayParam.ReverseKetOrderFlag) {
		FIntVector TempIntVector = FIntVector(0, 0, InputMMIAC->KetStateCount - 1) - OperationQubitInitialKet;
		FVector VectorVersionCoord = FVector(TempIntVector);
		OutputVector = InputDisplayParam.Spacing * VectorVersionCoord + InputDisplayParam.Padding - VectorOffsetSubstate;
	}
	else {
		FVector VectorVersionCoord = FVector(OperationQubitInitialKet);
		OutputVector = InputDisplayParam.Spacing * VectorVersionCoord + InputDisplayParam.Padding + VectorOffsetSubstate;
	}
}
void UQCDisplayBlueprintFxnLibrary::GetQuantumDisplaySubstateOffsetZ(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InputDisplayParam,
	int32 OperationIndex,
	int32 SubstateValue,
	float SubstateBoundsZ,
	float& OutputOffset) {
	int32 SubstateCount = InputMMIAC->IndexToSubstateCount[OperationIndex];
	float CentralPoint = (SubstateCount - 1.0) / 2.0;
	if (InputDisplayParam.ReverseKetOrderFlag) {
		OutputOffset = - ((1.0 * SubstateValue) - CentralPoint) * SubstateBoundsZ;
	}
	else {
		OutputOffset = ((1.0 * SubstateValue) - CentralPoint) * SubstateBoundsZ;
	}
}
void UQCDisplayBlueprintFxnLibrary::DisplayQuantumTransition(
	FQuantumTransitionDisplay& InTransition, //InputQuantumDisplayDerived,
	TArray<FString>& OutputStringArray) {
	OutputStringArray.Add("StartToTurnPhaseBarsTransforms");
	for (auto& iter : InTransition.StartToTurnPhaseBarsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("StartToTurnPhaseTipsTransforms");
	for (auto& iter : InTransition.StartToTurnPhaseTipsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("StartToTurnInnerCylinderTransform->" + InTransition.StartToTurnInnerCylinderTransform.ToString());
	OutputStringArray.Add("StartToTurnBoundingCylinderTransform->" + InTransition.StartToTurnBoundingCylinderTransform.ToString());
	OutputStringArray.Add("TurnToStopPhaseBarsTransforms");
	for (auto& iter : InTransition.TurnToStopPhaseBarsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("TurnToStopPhaseTipsTransforms");
	for (auto& iter : InTransition.TurnToStopPhaseTipsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("TurnToStopInnerCylinderTransform->" + InTransition.TurnToStopInnerCylinderTransform.ToString());
	OutputStringArray.Add("TurnToStopBoundingCylinderTransform->" + InTransition.TurnToStopBoundingCylinderTransform.ToString());
	OutputStringArray.Add("OutwardsPhaseBarsTransforms");
	for (auto& iter : InTransition.OutwardsPhaseBarsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("OutwardsPhaseTipsTransforms");
	for (auto& iter : InTransition.OutwardsPhaseTipsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("OutwardsInnerCylinderTransform->" + InTransition.OutwardsInnerCylinderTransform.ToString());
	OutputStringArray.Add("OutwardsBoundingCylinderTransform->" + InTransition.OutwardsBoundingCylinderTransform.ToString());
	OutputStringArray.Add("FlattenedPhaseBarsTransforms");
	for (auto& iter : InTransition.FlattenedPhaseBarsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("FlattenedPhaseTipsTransforms");
	for (auto& iter : InTransition.FlattenedPhaseTipsTransforms)
		OutputStringArray.Add(iter.ToString());
	OutputStringArray.Add("SplitterTransform->" + InTransition.SplitterTransform.ToString());
	OutputStringArray.Add("EdgeCylinderTransform->" + InTransition.EdgeCylinderTransform.ToString());
	OutputStringArray.Add("BackgroundCylinderTransform->" + InTransition.BackgroundCylinderTransform.ToString());
	OutputStringArray.Add("InnerCylinderTransform->" + InTransition.InnerCylinderTransform.ToString());
	OutputStringArray.Add("KetSubstateFinalArrowTransform->" + InTransition.KetSubstateFinalArrowTransform.ToString());
	OutputStringArray.Add("KetSubstateAddedArrowTransform->" + InTransition.KetSubstateAddedArrowTransform.ToString());
	OutputStringArray.Add("DirectionAddedArrowsTransforms");
	//for (auto& iter : InTransition.DirectionAddedArrowsTransforms)
	//	OutputStringArray.Add(iter.ToString());
}
void UQCDisplayBlueprintFxnLibrary::DisplayQuantumDerived(
	FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
	TArray<FString>& OutputStringArray) {
	OutputStringArray.Add(FString("MapPositionStart"));
	for (auto& iter : InDerive.MapPositionStart) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("MapPositionTurn"));
	for (auto& iter : InDerive.MapPositionTurn) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("MapPositionStop"));
	for (auto& iter : InDerive.MapPositionStop) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("MapPositionOutwardsBack"));
	for (auto& iter : InDerive.MapPositionOutwardsBack) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("MapPositionOutwardsFront"));
	for (auto& iter : InDerive.MapPositionOutwardsFront) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("MapPositionSplitter"));
	for (auto& iter : InDerive.MapPositionSplitter) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("MapPositionKetInitialMainState"));
	for (auto& iter : InDerive.MapPositionKetInitialMainState) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("SizeMainStateBox"));
	OutputStringArray.Add(InDerive.SizeMainStateBox.ToString());
	OutputStringArray.Add(FString("MapBoundsSubstate"));
	for (auto& iter : InDerive.MapBoundsSubstate) {
		OutputStringArray.Add(FString::FromInt(iter.Key) + FString("->") + iter.Value.ToString());
	}
	OutputStringArray.Add(FString("MapIndexToBaseRadius"));
	for (auto& iter : InDerive.MapIndexToBaseRadius) {
		OutputStringArray.Add(FString::FromInt(iter.Key) + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToMainKetStateMagnitudes"));
	for (auto& iter : InDerive.MapToMainKetStateMagnitudes) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToMainKetStateAngles"));
	for (auto& iter : InDerive.MapToMainKetStateAngles) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToSubstateMagnitudes"));
	for (auto& iter : InDerive.MapToSubstateMagnitudes) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToSubstateAngles"));
	for (auto& iter : InDerive.MapToSubstateAngles) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapMainStateMagnitudesFinalized"));
	for (auto& iter : InDerive.MapMainStateMagnitudesFinalized) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapMainStatePhasesFinalized"));
	for (auto& iter : InDerive.MapMainStatePhasesFinalized) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapSubstateMagnitudesFinalized"));
	for (auto& iter : InDerive.MapSubstateMagnitudesFinalized) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapSubstateMainPortionMagnitudesFinalized"));
	for (auto& iter : InDerive.MapSubstateMainPortionMagnitudesFinalized) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToSubstateAngleStarting"));
	for (auto& iter : InDerive.MapToSubstateAngleStarting) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToSubstateAngleFinal"));
	for (auto& iter : InDerive.MapToSubstateAngleFinal) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToSubstateMaximumMagnitude"));
	for (auto& iter : InDerive.MapToSubstateMaximumMagnitude) {
		OutputStringArray.Add(FString::FromInt(iter.Key) + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToMainStateMaximumMagnitude"));
	for (auto& iter : InDerive.MapToMainStateMaximumMagnitude) {
		OutputStringArray.Add(FString::FromInt(iter.Key) + FString("->") + FString::SanitizeFloat(iter.Value));
	}
	OutputStringArray.Add(FString("MapToSubstateAddedTwoVectors"));
	for (auto& iter : InDerive.MapToSubstateAddedTwoVectors) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.v1.ToString() + iter.Value.v2.ToString());
	}
	OutputStringArray.Add(FString("MapToQubitSplitPoint"));
	for (auto& iter : InDerive.MapToQubitSplitPoint) {
		OutputStringArray.Add(iter.Key.ToString() + FString("->") + iter.Value.ToString());
	}
}
void UQCDisplayBlueprintFxnLibrary::DisplayQuantumDisplayKet(
	FQuantumKetDisplay& InKet, //InputQuantumDisplayDerived,
	TArray<FString>& OutputStringArray) {
	InKet.NonZeroKet ? OutputStringArray.Add("NonZeroKet" + FString("->") + "True") : OutputStringArray.Add("NonZeroKet" + FString("->") + "False");
	OutputStringArray.Add(FString("MainBoxTransform") + FString("->") + InKet.MainBoxTransform.ToString());
	OutputStringArray.Add(FString("EdgeCylinderTransform") + FString("->") + InKet.EdgeCylinderTransform.ToString());
	OutputStringArray.Add(FString("InnerCylinderTransform") + FString("->") + InKet.InnerCylinderTransform.ToString());
	OutputStringArray.Add(FString("MagnitudeCylinderTransform") + FString("->") + InKet.MagnitudeCylinderTransform.ToString());
	OutputStringArray.Add(FString("FinalKetStateArrowTransform") + FString("->") + InKet.FinalKetStateArrowTransform.ToString());
	OutputStringArray.Add(FString("FinalKetDirectionTransform") + FString("->") + InKet.FinalKetDirectionTransform.ToString());
}
float GetPositiveAtanTo360(FVector2D InputComplexValue) {
	float DegreesAtan2Value = FMath::RadiansToDegrees(FMath::Atan2(InputComplexValue.Y, InputComplexValue.X));
	float DegreesPositive;
	if (DegreesAtan2Value < 0.0) {
		DegreesPositive = DegreesAtan2Value + 360.0;
	}
	else {
		DegreesPositive = DegreesAtan2Value;
	}
	return DegreesPositive;
}
void UQCDisplayBlueprintFxnLibrary::GetQuantumDisplayDerived(
	UMultiMapIntegerActorComponent* InputMMIAC,
	TMap<FIntVector, FVector2D>& InputOperationMap,
	TMap<FIntVector, FVector2D>& InputTransitionMap,
	TMap<FIntPoint, FVector2D>& InputInitialKetMap,
	FQuantumDisplayParam& InputDisplayParam,
	FQuantumDisplayDerived& OutputQuantumDisplayDerived){
	OutputQuantumDisplayDerived.MapToSubstateMagnitudes.Empty();
	OutputQuantumDisplayDerived.MapToSubstateAngles.Empty();
	OutputQuantumDisplayDerived.MapToMainKetStateMagnitudes.Empty();
	OutputQuantumDisplayDerived.MapToMainKetStateAngles.Empty();
	for (int32 Index = 0; Index <= InputMMIAC->OperatorCount; Index++) {
		OutputQuantumDisplayDerived.MapToSubstateMaximumMagnitude.Add(Index, 0.0); //0.1 / InputMMIAC->KetStateCount;
		OutputQuantumDisplayDerived.MapToMainStateMaximumMagnitude.Add(Index, 0.0); //0.1 / InputMMIAC->KetStateCount;
		
	}
	for (auto& iter : InputTransitionMap) {
		if (OutputQuantumDisplayDerived.MapToSubstateMaximumMagnitude[iter.Key.X] < iter.Value.Size())
			OutputQuantumDisplayDerived.MapToSubstateMaximumMagnitude[iter.Key.X] = iter.Value.Size();
		OutputQuantumDisplayDerived.MapToSubstateMagnitudes.Add(iter.Key, iter.Value.Size());
		OutputQuantumDisplayDerived.MapToSubstateAngles.Add(iter.Key, GetPositiveAtanTo360(iter.Value));
	}
	for (auto& iter : InputInitialKetMap) {
		if (OutputQuantumDisplayDerived.MapToMainStateMaximumMagnitude[iter.Key.X] < iter.Value.Size())
			OutputQuantumDisplayDerived.MapToMainStateMaximumMagnitude[iter.Key.X] = iter.Value.Size();
		OutputQuantumDisplayDerived.MapToMainKetStateMagnitudes.Add(iter.Key, iter.Value.Size());
		OutputQuantumDisplayDerived.MapToMainKetStateAngles.Add(iter.Key, GetPositiveAtanTo360(iter.Value));
	}

	//for (int32 PreLocalOp = 0; PreLocalOp <= InputMMIAC->OperatorCount; PreLocalOp++) {
	//	int32 = 
	//}
	for (int32 PreLocalOp = 0; PreLocalOp <= InputMMIAC->OperatorCount; PreLocalOp++) {
		for (int32 PreLocalKetFrom = 0; PreLocalKetFrom < InputMMIAC->KetStateCount; PreLocalKetFrom++) {
			FIntPoint PreLocalOpIndexFromKet = FIntPoint(PreLocalOp, PreLocalKetFrom);
			if (InputInitialKetMap.Contains(PreLocalOpIndexFromKet)) {
				float LocalKetMainStateMagnitude;
				if (InputDisplayParam.NormalizeKets) {
					LocalKetMainStateMagnitude =
						InputInitialKetMap[PreLocalOpIndexFromKet].Size() / OutputQuantumDisplayDerived.MapToMainStateMaximumMagnitude[PreLocalOp];
				}
				else {
					LocalKetMainStateMagnitude =
						InputInitialKetMap[PreLocalOpIndexFromKet].Size();
				}
				OutputQuantumDisplayDerived.MapMainStateMagnitudesFinalized.Add(
					PreLocalOpIndexFromKet,
					LocalKetMainStateMagnitude);
				float KetMainDegreesPositive = GetPositiveAtanTo360(InputInitialKetMap[PreLocalOpIndexFromKet]);
				OutputQuantumDisplayDerived.MapMainStatePhasesFinalized.Add(
					PreLocalOpIndexFromKet,
					KetMainDegreesPositive);
			}
			if (PreLocalOp < InputMMIAC->OperatorCount) {
				for (int32 PreLocalKetTo = 0; PreLocalKetTo < InputMMIAC->KetStateCount; PreLocalKetTo++) {
					FIntVector PreLocalOpIndexFromKetToKet = FIntVector(PreLocalOp, PreLocalKetFrom, PreLocalKetTo);
					if (InputInitialKetMap.Contains(PreLocalOpIndexFromKet) && InputTransitionMap.Contains(PreLocalOpIndexFromKetToKet)) {
						float StartDegreesPositive = GetPositiveAtanTo360(InputInitialKetMap[PreLocalOpIndexFromKet]);
						OutputQuantumDisplayDerived.MapToSubstateAngleStarting.Add(PreLocalOpIndexFromKetToKet, StartDegreesPositive);
						float TempStopDegreesPositive = GetPositiveAtanTo360(InputTransitionMap[PreLocalOpIndexFromKetToKet]);
						float StopDegreesPositive;
						if (TempStopDegreesPositive < StartDegreesPositive) {
							StopDegreesPositive = TempStopDegreesPositive + 360.0;
						}
						else {
							StopDegreesPositive = TempStopDegreesPositive;
						}
						OutputQuantumDisplayDerived.MapToSubstateAngleFinal.Add(PreLocalOpIndexFromKetToKet, StopDegreesPositive);
						float LocalTransitionMagnitude;
						if (InputDisplayParam.NormalizeTransitions) {
							LocalTransitionMagnitude =
								InputTransitionMap[PreLocalOpIndexFromKetToKet].Size() / OutputQuantumDisplayDerived.MapToSubstateMaximumMagnitude[PreLocalOp];
						}
						else {
							LocalTransitionMagnitude =
								InputTransitionMap[PreLocalOpIndexFromKetToKet].Size();
						}
						OutputQuantumDisplayDerived.MapSubstateMagnitudesFinalized.Add(
							PreLocalOpIndexFromKetToKet,
							LocalTransitionMagnitude);
						float LocalKetSubstateMagnitude;
						if (InputDisplayParam.NormalizeKets) {
							LocalKetSubstateMagnitude =
								InputTransitionMap[PreLocalOpIndexFromKetToKet].Size() / OutputQuantumDisplayDerived.MapToMainStateMaximumMagnitude[PreLocalOp];
						}
						else {
							LocalKetSubstateMagnitude =
								InputInitialKetMap[PreLocalOpIndexFromKet].Size();
						}
						OutputQuantumDisplayDerived.MapSubstateMainPortionMagnitudesFinalized.Add(
							PreLocalOpIndexFromKetToKet,
							LocalKetSubstateMagnitude);
					}
				}
			}
		}
	}
	TArray<FIntVector> LocalIntVectorArray;
	TArray<float> LocalFloatIntVectorArray;
	TArray<FIntPoint> LocalIntPointArray;
	TArray<float> LocalFloatIntPointArray;
	float ProportionSubstateX =
		(1.0 - InputDisplayParam.FillProportionPhaseWaveXOfSpacingX)
		* (1.0 - InputDisplayParam.FillProportionMainStateBoundsXOfMainPlusSubBoundsX);
	float ProportionMainStateX =
		(1.0 - InputDisplayParam.FillProportionPhaseWaveXOfSpacingX)
		* InputDisplayParam.FillProportionMainStateBoundsXOfMainPlusSubBoundsX;
	float BoundsWaveX = InputDisplayParam.FillProportionPhaseWaveXOfSpacingX * InputDisplayParam.Spacing.X;
	float BoundsSubstateX = ProportionSubstateX * InputDisplayParam.Spacing.X;
	float BoundsMainStateX = ProportionMainStateX * InputDisplayParam.Spacing.X;
	OutputQuantumDisplayDerived.SizeMainStateBox =
		InputDisplayParam.MainStateProportionOfBounds
		* FVector(InputDisplayParam.Spacing.X * ProportionMainStateX, 
			InputDisplayParam.Spacing.Y, InputDisplayParam.Spacing.Z);
	for (int32 OpIndex = 0; OpIndex <= InputMMIAC->OperatorCount; OpIndex++) {
		if (OpIndex < InputMMIAC->OperatorCount) {
			float SubstateBoundsX =
				InputDisplayParam.Spacing.X * (1.0 - InputDisplayParam.FillProportionPhaseWaveXOfSpacingX) * (1.0 - InputDisplayParam.FillProportionMainStateBoundsXOfMainPlusSubBoundsX);
			float TempNaught0 = OutputQuantumDisplayDerived.SizeMainStateBox.Z * InputDisplayParam.SubstateProportionOfBoundsZ;
			//int32 CurrentSubstateCount = InputMMIAC->IndexToSubstateCount[OpIndex];
			float TempNaught1 = (1.0 / (1.0 * InputMMIAC->IndexToSubstateCount[OpIndex]));
			float SubstateBoundsZ =
				(OutputQuantumDisplayDerived.SizeMainStateBox.Z *
					InputDisplayParam.SubstateProportionOfBoundsZ *
					TempNaught1);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< int32, float> MapIndexToBaseRadius;
			OutputQuantumDisplayDerived.MapIndexToBaseRadius.Add(
				OpIndex, 0.5 * SubstateBoundsZ * InputDisplayParam.MainDiameterAsFractionOfKetZSubStateSize);
			OutputQuantumDisplayDerived.MapBoundsSubstate.Add(
				OpIndex, FVector(SubstateBoundsX, InputDisplayParam.Spacing.Y, SubstateBoundsZ));
		}
		for (int32 FromKet = 0; FromKet < InputMMIAC->KetStateCount; FromKet++) {
			FIntPoint LocalOpIndexFromKet = FIntPoint(OpIndex, FromKet);
			FVector LocalInitialKetPositionVector;
			GetQuantumDisplayBasicCoord(
				InputMMIAC, InputDisplayParam, 
				FIntVector(OpIndex, -1, FromKet), 
				LocalInitialKetPositionVector);
			TArray<FIntVector> LocalTransitionArraySum;
			//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntPoint, FVector> MapPositionKetInitialMainState;
			OutputQuantumDisplayDerived.MapPositionKetInitialMainState.Add(
				FIntPoint(OpIndex, FromKet), LocalInitialKetPositionVector);
			for (int32 ToKet = 0; ToKet <= InputMMIAC->KetStateCount; ToKet++) {
				FIntVector LocalOpIndexFromKetToKet = FIntVector(OpIndex, FromKet, ToKet);
				if (InputTransitionMap.Contains(LocalOpIndexFromKetToKet) && 
					InputMMIAC->OperatorSourceSubstate.Contains(LocalOpIndexFromKetToKet) &&
					InputMMIAC->OperatorTargetSubstate.Contains(LocalOpIndexFromKetToKet)) {
					FVector LocalFinalKetPositionVector;
					int32 SourceSubstate = InputMMIAC->OperatorSourceSubstate[LocalOpIndexFromKetToKet];
					int32 TargetSubstate = InputMMIAC->OperatorTargetSubstate[LocalOpIndexFromKetToKet];
					GetQuantumDisplayBasicCoord(
						InputMMIAC, InputDisplayParam, 
						FIntVector(OpIndex + 1, -1, LocalOpIndexFromKetToKet.Z),
						LocalFinalKetPositionVector);
					float SourceSubstateOffsetZ;
					GetQuantumDisplaySubstateOffsetZ(
						InputMMIAC, InputDisplayParam, OpIndex, SourceSubstate, 
						OutputQuantumDisplayDerived.MapBoundsSubstate[OpIndex].Z, 
						SourceSubstateOffsetZ);
					FVector SourceSubstateOffsetVector = FVector(0.0, 0.0, SourceSubstateOffsetZ);
					float TargetSubstateOffsetZ;
					GetQuantumDisplaySubstateOffsetZ(
						InputMMIAC, InputDisplayParam, OpIndex, TargetSubstate, 
						OutputQuantumDisplayDerived.MapBoundsSubstate[OpIndex].Z, 
						TargetSubstateOffsetZ);
					FVector TargetSubstateOffsetVector = FVector(0.0, 0.0, TargetSubstateOffsetZ);
					//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionStart;
					FVector LocalPositionWaveStart =
						LocalInitialKetPositionVector 
						+ 0.5 * FVector(BoundsMainStateX, 0.0, 0.0)
						+ SourceSubstateOffsetVector;
					OutputQuantumDisplayDerived.MapPositionStart.Add(
						LocalOpIndexFromKetToKet, LocalPositionWaveStart);
					//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionTurn;
					FVector LocalPositionWaveTurn =
						LocalFinalKetPositionVector
						- 0.5 * FVector(BoundsMainStateX, 0.0, 0.0)
						- FVector(BoundsSubstateX, 0.0, 0.0)
						+ TargetSubstateOffsetVector;
					OutputQuantumDisplayDerived.MapPositionTurn.Add(
						LocalOpIndexFromKetToKet, LocalPositionWaveTurn);
					//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionStop;
					FVector LocalPositionWaveStop =
						LocalFinalKetPositionVector
						- 0.5 * FVector(BoundsMainStateX, 0.0, 0.0)
						+ TargetSubstateOffsetVector;
					OutputQuantumDisplayDerived.MapPositionStop.Add(
						LocalOpIndexFromKetToKet, LocalPositionWaveStop);

					FVector LocalCentralPoint = (LocalPositionWaveTurn + LocalPositionWaveStop) / 2.0;
					float OffsetY = (LocalPositionWaveStop - LocalPositionWaveTurn).Size() / 2.0;
					//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionOutwardsBack;
					FVector LocalPositionWaveOutwardBack =
						LocalCentralPoint - FVector(0.0, OffsetY, 0.0);
					OutputQuantumDisplayDerived.MapPositionOutwardsBack.Add(
						LocalOpIndexFromKetToKet, LocalPositionWaveOutwardBack);
					//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionOutwardsFront;
					FVector LocalPositionWaveOutwardFront =
						LocalCentralPoint + FVector(0.0, OffsetY, 0.0);
					OutputQuantumDisplayDerived.MapPositionOutwardsFront.Add(
						LocalOpIndexFromKetToKet, LocalPositionWaveOutwardFront);
					//UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap< FIntVector, FVector> MapPositionSplitter;
					OutputQuantumDisplayDerived.MapPositionSplitter.Add(
						LocalOpIndexFromKetToKet, LocalCentralPoint);
				}

			}
			//// Determine Values for added partial arrows of main state
			LocalTransitionArraySum.Empty();
			InputMMIAC->FxnDestinationInitialKetToTransitions(LocalOpIndexFromKet, LocalTransitionArraySum);
			if (LocalTransitionArraySum.Num() != 0) {
				if (InputInitialKetMap.Contains(LocalOpIndexFromKet)) {
					FVector CurrentVectorPiece = FVector(0.0, 0.0, 0.0);
					FVector CurrentVectorSum = FVector(0.0, 0.0, 0.0);
					FVector PreviousVectorSum = FVector(0.0, 0.0, 0.0);
					for (auto& iterSumTransitions : LocalTransitionArraySum) {
						float CurrentMag = OutputQuantumDisplayDerived.MapSubstateMainPortionMagnitudesFinalized[iterSumTransitions];
						float CurrentAngle = OutputQuantumDisplayDerived.MapToSubstateAngleFinal[iterSumTransitions];
						CurrentVectorPiece =
							FVector(CurrentMag*FMath::Cos(FMath::RadiansToDegrees(CurrentAngle)),
							CurrentMag*FMath::Sin(FMath::RadiansToDegrees(CurrentAngle)), 0.0);
						PreviousVectorSum = CurrentVectorSum;
						CurrentVectorSum = PreviousVectorSum + CurrentVectorPiece;
						OutputQuantumDisplayDerived.MapToSubstateAddedTwoVectors.Add(
							iterSumTransitions, FTwoVectors(PreviousVectorSum, CurrentVectorSum));
					}
				}
				else {
					for (auto& iterSumTransitions : LocalTransitionArraySum) {
						float CurrentMag = OutputQuantumDisplayDerived.MapSubstateMainPortionMagnitudesFinalized[iterSumTransitions];
						float CurrentAngle = OutputQuantumDisplayDerived.MapToSubstateAngleFinal[iterSumTransitions];
						OutputQuantumDisplayDerived.MapToSubstateAddedTwoVectors.Add(
							iterSumTransitions, FTwoVectors(
								FVector(0.0, 0.0, 0.0), 
								FVector(CurrentMag* FMath::Cos(FMath::RadiansToDegrees(CurrentAngle)),
									CurrentMag * FMath::Sin(FMath::RadiansToDegrees(CurrentAngle)), 0.0)));
					}
				}
			}
		}
	}
	OutputQuantumDisplayDerived.MapToQubitSplitPoint.Empty();
	for (auto& iter : InputMMIAC->QubitSplitAddressToLocationIntVector) {
		FVector FirstValue, SecondValue;
		GetQuantumDisplayBasicCoord(
			InputMMIAC, InputDisplayParam,
			FIntVector(-1, iter.Value.X, iter.Value.Y),
			FirstValue);
		GetQuantumDisplayBasicCoord(
			InputMMIAC, InputDisplayParam,
			FIntVector(-1, iter.Value.X, iter.Value.Z),
			SecondValue);
		FVector LocalOutputLocation = ((FirstValue + SecondValue) / 2.0);
		OutputQuantumDisplayDerived.MapToQubitSplitPoint.Add(iter.Key, LocalOutputLocation);
	}
}
void UQCDisplayBlueprintFxnLibrary::InitializeQuantumKetMainStateDisplay(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InParam, //InputDisplayParam,
	FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
	int32 OperationIndex,
	int32 KetState,
	bool& SuccessFlag,
	FQuantumKetDisplay& OutKetDisplay) {
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform MainBoxTransform;
	FIntPoint LocalOpKet = FIntPoint(OperationIndex, KetState);
	FRotator RotatorZero = FRotator::FRotator(0.0, 0.0, 0.0);
	FVector LocalLocation = InDerive.MapPositionKetInitialMainState[LocalOpKet];
	float SizeOfMainStateCylinderGroup =
		InParam.FillProportionCylinderMainStateRadiusOfSmallestBoxDimension
		* FMath::Min(InDerive.SizeMainStateBox.X, InDerive.SizeMainStateBox.Z);
	FVector LocalSizeVector = FVector(SizeOfMainStateCylinderGroup, InDerive.SizeMainStateBox.Y, SizeOfMainStateCylinderGroup);
	OutKetDisplay.MainBoxTransform = FTransform(RotatorZero, LocalLocation, InDerive.SizeMainStateBox);

	FVector OffsetToSurface = FVector(0.0, 0.5 * InDerive.SizeMainStateBox.Y, 0.0);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform EdgeCylinderTransform;
	GetRectangleTransformDirectionZ(
		LocalLocation - OffsetToSurface + FVector(0.0, InParam.OffsetMainStateEdgeAxisY, 0.0),
		LocalLocation + OffsetToSurface + FVector(0.0, InParam.OffsetMainStateEdgeAxisY, 0.0),
		SizeOfMainStateCylinderGroup, SizeOfMainStateCylinderGroup,
		FVector(0.0, 1.0, 0.0), OutKetDisplay.EdgeCylinderTransform);
	//FVector EdgeAdjustedLocation =
	//	LocalLocation + FVector(0.0, InParam.OffsetMainStateEdgeAxisY, 0.0);
	//OutKetDisplay.EdgeCylinderTransform = FTransform(
	//	RotatorZero, EdgeAdjustedLocation, LocalSizeVector);
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform InnerCylinderTransform;
	GetRectangleTransformDirectionZ(
		LocalLocation - OffsetToSurface + FVector(0.0, InParam.OffsetMainStateCentralDiscAxisY, 0.0),
		LocalLocation + OffsetToSurface + FVector(0.0, InParam.OffsetMainStateCentralDiscAxisY, 0.0),
		LocalSizeVector.X * InParam.ProportionalMainStateCenterDisc,
		LocalSizeVector.Z * InParam.ProportionalMainStateCenterDisc,
		FVector(0.0, 1.0, 0.0), OutKetDisplay.InnerCylinderTransform);
	if (InDerive.MapPositionKetInitialMainState.Contains(LocalOpKet)) {
		SuccessFlag = true;
		
		//FVector CenterAdjustedLocation =
		//	LocalLocation + FVector(0.0, InParam.OffsetMainStateCentralDiscAxisY, 0.0);
		//FVector CenterAdjustedSize = FVector(
		//	LocalSizeVector.X * InParam.ProportionalMainStateCenterDisc,
		//	LocalSizeVector.Y,
		//	LocalSizeVector.Z * InParam.ProportionalMainStateCenterDisc);
		//OutKetDisplay.InnerCylinderTransform = FTransform(
		//	RotatorZero, CenterAdjustedLocation, CenterAdjustedSize);
		if (InDerive.MapToMainKetStateMagnitudes.Contains(LocalOpKet) &&
			InDerive.MapMainStatePhasesFinalized.Contains(LocalOpKet)) {
			OutKetDisplay.NonZeroKet = true;
			//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform MagnitudeCylinderTransform;
			GetRectangleTransformDirectionZ(
				LocalLocation - OffsetToSurface + FVector(0.0, InParam.OffsetMainStateMagnitudeAxisY, 0.0),
				LocalLocation + OffsetToSurface + FVector(0.0, InParam.OffsetMainStateMagnitudeAxisY, 0.0),
				LocalSizeVector.X * InDerive.MapToMainKetStateMagnitudes[LocalOpKet],
				LocalSizeVector.Z * InDerive.MapToMainKetStateMagnitudes[LocalOpKet],
				FVector(0.0, 1.0, 0.0), OutKetDisplay.MagnitudeCylinderTransform);
			////FVector MagnitudeAdjustedLocation =
			////	LocalLocation + FVector(0.0, InParam.OffsetMainStateMagnitudeAxisY, 0.0);
			////FVector MagnitudeAdjustedSize = FVector(
			////	LocalSizeVector.X * InDerive.MapMainStateMagnitudesFinalized[LocalOpKet],
			////	LocalSizeVector.Y,
			////	LocalSizeVector.Z * InDerive.MapMainStateMagnitudesFinalized[LocalOpKet]);
			////OutKetDisplay.MagnitudeCylinderTransform = FTransform(
			////	RotatorZero, MagnitudeAdjustedLocation, MagnitudeAdjustedSize);
			////UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform FinalKetStateArrowTransform;
			//FVector FinalKetMainArrowAdjustedLocation =
			//	LocalLocation + FVector(0.0, InParam.OffsetMainStateFinalArrowAxisY, 0.0);
			//FVector DirectionFinalArrowAdjustedSize = FVector(
			//	InParam.ThicknessMainStateFinalArrow,
			//	LocalSizeVector.Y,
			//	LocalSizeVector.Z * InDerive.MapMainStateMagnitudesFinalized[LocalOpKet]);
			//OutKetDisplay.FinalKetStateArrowTransform = FTransform(
			//	FRotator(0.0, InDerive.MapMainStatePhasesFinalized[LocalOpKet] - 90.0, 0.0),
			//	FinalKetMainArrowAdjustedLocation, DirectionFinalArrowAdjustedSize);
			////UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform FinalKetDirectionTransform;
			FVector DirectionPhaseArrowAdjustedLocation =
				LocalLocation + FVector(0.0, InParam.OffsetMainStatePhaseOnlyArrowAxisY, 0.0);
			FVector DirectionPhaseArrowAdjustedSize = FVector(
				LocalSizeVector.X, // * InDerive.MapMainStateMagnitudesFinalized[LocalOpKet],
				LocalSizeVector.Y, // * InDerive.MapMainStateMagnitudesFinalized[LocalOpKet],
				LocalSizeVector.Z); // * InDerive.MapMainStateMagnitudesFinalized[LocalOpKet]);
			OutKetDisplay.FinalKetDirectionTransform = FTransform(
				FRotator(0.0, InDerive.MapMainStatePhasesFinalized[LocalOpKet] - 90.0, 0.0),
				DirectionPhaseArrowAdjustedLocation, DirectionPhaseArrowAdjustedSize);
			////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////// ARROW NEW ATTEMPT///////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////
			FVector LocalTargetKetLocation = InDerive.MapPositionKetInitialMainState[LocalOpKet];
			//float SizeOfMainStateCylinderGroup =
			//	InParam.FillProportionCylinderMainStateRadiusOfSmallestBoxDimension
			//	* FMath::Min(InDerive.SizeMainStateBox.X, InDerive.SizeMainStateBox.Z);
			FVector LocalKetFinalArrowSizeVector =
				FVector(SizeOfMainStateCylinderGroup, InDerive.SizeMainStateBox.Y, SizeOfMainStateCylinderGroup);
			FVector AdjustedKetFinalArrowLocation =
				LocalTargetKetLocation
				+ FVector(0.0, InParam.OffsetMainStateFinalArrowAxisY, 0.0);
			//- FVector(0.0, 0.5 * LocalKetFinalArrowSizeVector.Y, 0.0);
			FVector AdjustedKetFinalArrowLocationStart =
				AdjustedKetFinalArrowLocation;
			FVector AdjustedKetFinalArrowLocationStop =
				AdjustedKetFinalArrowLocation
				+ InDerive.MapMainStateMagnitudesFinalized[LocalOpKet] * FVector(
					0.5 * SizeOfMainStateCylinderGroup * FMath::Cos(FMath::DegreesToRadians(
						InDerive.MapMainStatePhasesFinalized[LocalOpKet])), 0.0,
					0.5 * SizeOfMainStateCylinderGroup*FMath::Sin(FMath::DegreesToRadians(
						InDerive.MapMainStatePhasesFinalized[LocalOpKet])));
			FVector AdjustedKetFinalArrowLocationDelta =
				AdjustedKetFinalArrowLocationStop - AdjustedKetFinalArrowLocationStart;
			GetRectangleTransformDirectionZ(
				AdjustedKetFinalArrowLocationStart - AdjustedKetFinalArrowLocationDelta,
				AdjustedKetFinalArrowLocation + AdjustedKetFinalArrowLocationDelta,
				InParam.ThicknessMainStateFinalArrow,
				LocalKetFinalArrowSizeVector.Y,
				FVector(0.0,1.0,0.0), OutKetDisplay.FinalKetStateArrowTransform);
		}
		else {
			OutKetDisplay.NonZeroKet = false;
			OutKetDisplay.FinalKetStateArrowTransform =
				FTransform(RotatorZero, FVector(0.0, 0.0, 0.0), FVector(1.0, 1.0, 1.0));
			OutKetDisplay.FinalKetDirectionTransform =
				FTransform(RotatorZero, FVector(0.0, 0.0, 0.0), FVector(1.0, 1.0, 1.0));
			OutKetDisplay.MagnitudeCylinderTransform =
				FTransform(RotatorZero, FVector(0.0, 0.0, 0.0), FVector(1.0, 1.0, 1.0));
		}
	}
	else SuccessFlag = false;
}
void UQCDisplayBlueprintFxnLibrary::InitializeQuantumTransitionSubstateDisplay(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InParam, //InputDisplayParam,
	FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
	int32 OperationIndex,
	int32 KetStateFrom,
	int32 KetStateTo,
	bool& SuccessFlag,
	FQuantumTransitionDisplay& OutSubstateDisplay) {
	FIntPoint LocalOpKetTo = FIntPoint(OperationIndex, KetStateFrom);
	FIntPoint LocalOpKetFrom = FIntPoint(OperationIndex, KetStateTo);
	FIntVector LocalTransition = FIntVector(OperationIndex, KetStateFrom, KetStateTo);
	if (InDerive.MapPositionStart.Contains(LocalTransition) &&
		InDerive.MapPositionTurn.Contains(LocalTransition) &&
		InDerive.MapPositionStop.Contains(LocalTransition) &&
		InDerive.MapPositionOutwardsBack.Contains(LocalTransition) &&
		InDerive.MapPositionOutwardsFront.Contains(LocalTransition) &&
		InDerive.MapIndexToBaseRadius.Contains(OperationIndex) &&
		InDerive.MapSubstateMagnitudesFinalized.Contains(LocalTransition) &&
		InDerive.MapToSubstateAngleStarting.Contains(LocalTransition) &&
		InDerive.MapToSubstateAngleFinal.Contains(LocalTransition)) {
		SuccessFlag = true;
		FVector DirectionAxisY = FVector::FVector(0.0, 1.0, 0.0);
		FRotator RotatorZero = FRotator::FRotator(0.0, 0.0, 0.0);
		FVector StartLocation = InDerive.MapPositionStart[LocalTransition];
		FVector TurnLocation = InDerive.MapPositionTurn[LocalTransition];
		FVector StopLocation = InDerive.MapPositionStop[LocalTransition];
		FVector OutwardsBackLocation = InDerive.MapPositionOutwardsBack[LocalTransition];
		FVector OutwardsFrontLocation = InDerive.MapPositionOutwardsFront[LocalTransition];
		float OuterRadius = InDerive.MapIndexToBaseRadius[OperationIndex];
		float OuterDiameter = 2.0 * OuterRadius;
		float InnerRadius = OuterRadius * InParam.InnerRadiusAsFractionOfMainRadius;
		float InnerDiameter = 2.0 * InnerRadius;
		float SpokeRadius = OuterRadius * InDerive.MapSubstateMagnitudesFinalized[LocalTransition];
		OutSubstateDisplay.SplitterTransform = FTransform(
			FRotator(0.0, 0.0, 0.0),
			((TurnLocation + StopLocation)/2.0),
			FVector(OuterDiameter + InParam.AdditionalDiameterToWaveSplitter,
				OuterDiameter + InParam.AdditionalDiameterToWaveSplitter,
				OuterDiameter + InParam.AdditionalDiameterToWaveSplitter));
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> StartToTurnPhaseBarsTransforms;
		GetTransitionPhaseBlocksFromStartRadiusTransformArray(
			InParam.SubBlockLength,
			InParam.SubBlockSpokeDepth,
			OuterRadius,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			0.0,
			InDerive.MapToSubstateAngleStarting[LocalTransition],
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			StartLocation,
			TurnLocation,
			FVector(0.0, 1.0, 0.0),
			FVector(1.0, 0.0, 0.0),
			false,
			InParam.SubBlockMultiplier,
			OutSubstateDisplay.StartToTurnPhaseBarsTransforms);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> StartToTurnPhaseTipsTransforms;
		GetTransitionPhaseBlocksFromStartRadiusTransformArray(
			InParam.SubBlockLength,
			InParam.SubBlockTipDepth,
			OuterRadius,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			InParam.SpokeTipsProportionStart,
			InDerive.MapToSubstateAngleStarting[LocalTransition],
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			StartLocation,
			TurnLocation,
			FVector(0.0, 1.0, 0.0),
			FVector(1.0, 0.0, 0.0),
			false,
			InParam.SubBlockMultiplier,
			OutSubstateDisplay.StartToTurnPhaseTipsTransforms);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform StartToTurnInnerCylinderTransform;
		GetRectangleTransformDirectionZ(
			StartLocation, TurnLocation,
			InnerDiameter, InnerDiameter,
			DirectionAxisY, OutSubstateDisplay.StartToTurnInnerCylinderTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform StartToTurnBoundingCylinderTransform;
		GetRectangleTransformDirectionZ(
			StartLocation, TurnLocation,
			OuterDiameter, OuterDiameter,
			DirectionAxisY, OutSubstateDisplay.StartToTurnBoundingCylinderTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> TurnToStopPhaseBarsTransforms;
		//GetTransitionPhaseBlocksFromStartRadiusTransformArray(
		//	InParam.SubBlockLength,
		//	InParam.SubBlockSpokeDepth,
		//	OuterRadius,
		//	InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
		//	0.0,
		//	InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	TurnLocation,
		//	StopLocation,
		//	FVector(0.0, 1.0, 0.0),
		//	FVector(1.0, 0.0, 0.0),
		//	false,
		//	InParam.SubBlockMultiplier,
		//	OutSubstateDisplay.TurnToStopPhaseBarsTransforms);
		FTransform LocalTurnToStopBarsTransform;
		GetTransitionPhaseBlocksFromStartRadiusTransformSingle(
			InParam.SubBlockSpokeDepth,
			OuterRadius,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			0.0,
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			TurnLocation,
			StopLocation,
			FVector(0.0, 1.0, 0.0),
			false,
			LocalTurnToStopBarsTransform);
		OutSubstateDisplay.TurnToStopPhaseBarsTransforms.Add(LocalTurnToStopBarsTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> TurnToStopPhaseTipsTransforms;
		//GetTransitionPhaseBlocksFromStartRadiusTransformArray(
		//	InParam.SubBlockLength,
		//	InParam.SubBlockTipDepth,
		//	OuterRadius,
		//	InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
		//	InParam.SpokeTipsProportionStart,
		//	InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	TurnLocation,
		//	StopLocation,
		//	FVector(0.0, 1.0, 0.0),
		//	FVector(1.0, 0.0, 0.0),
		//	false,
		//	InParam.SubBlockMultiplier,
		//	OutSubstateDisplay.TurnToStopPhaseTipsTransforms);
		FTransform LocalTurnToStopTipsTransform;
		GetTransitionPhaseBlocksFromStartRadiusTransformSingle(
			InParam.SubBlockSpokeDepth,
			OuterRadius,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			InParam.SpokeTipsProportionStart,
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			TurnLocation,
			StopLocation,
			FVector(0.0, 1.0, 0.0),
			false,
			LocalTurnToStopTipsTransform);
		OutSubstateDisplay.TurnToStopPhaseTipsTransforms.Add(LocalTurnToStopTipsTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform TurnToStopInnerCylinderTransform;
		GetRectangleTransformDirectionZ(
			TurnLocation, StopLocation,
			InnerDiameter, InnerDiameter,
			DirectionAxisY, OutSubstateDisplay.TurnToStopInnerCylinderTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform TurnToStopBoundingCylinderTransform;
		GetRectangleTransformDirectionZ(
			TurnLocation, StopLocation,
			OuterDiameter, OuterDiameter,
			DirectionAxisY, OutSubstateDisplay.TurnToStopBoundingCylinderTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> OutwardsPhaseBarsTransforms;
		//GetTransitionPhaseBlocksFromStartRadiusTransformArray(
		//	InParam.SubBlockLength,
		//	InParam.SubBlockSpokeDepth,
		//	OuterRadius,
		//	InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
		//	0.0,
		//	-InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	-InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	OutwardsBackLocation,
		//	OutwardsFrontLocation,
		//	FVector(1.0, 0.0, 0.0),
		//	FVector(0.0, 1.0, 0.0),
		//	false,
		//	InParam.SubBlockMultiplier,
		//	OutSubstateDisplay.OutwardsPhaseBarsTransforms);
		FTransform LocalOutwardsBarsTransform;
		GetTransitionPhaseBlocksFromStartRadiusTransformSingle(
			InParam.SubBlockSpokeDepth,
			OuterRadius,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			0.0,
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			OutwardsBackLocation,
			OutwardsFrontLocation,
			FVector(1.0, 0.0, 0.0),
			true,
			LocalOutwardsBarsTransform);
		OutSubstateDisplay.OutwardsPhaseBarsTransforms.Add(LocalOutwardsBarsTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> OutwardsPhaseTipsTransforms;
		//GetTransitionPhaseBlocksFromStartRadiusTransformArray(
		//	InParam.SubBlockLength,
		//	InParam.SubBlockTipDepth,
		//	OuterRadius,
		//	InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
		//	InParam.SpokeTipsProportionStart,
		//	-InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	-InDerive.MapToSubstateAngleFinal[LocalTransition],
		//	OutwardsBackLocation,
		//	OutwardsFrontLocation,
		//	FVector(1.0, 0.0, 0.0),
		//	FVector(0.0, 1.0, 0.0),
		//	false,
		//	InParam.SubBlockMultiplier,
		//	OutSubstateDisplay.OutwardsPhaseTipsTransforms);
		FTransform LocalOutwardsTipsTransform;
		GetTransitionPhaseBlocksFromStartRadiusTransformSingle(
			InParam.SubBlockSpokeDepth,
			OuterRadius,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			InParam.SpokeTipsProportionStart,
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			OutwardsBackLocation,
			OutwardsFrontLocation,
			FVector(1.0, 0.0, 0.0),
			true,
			LocalOutwardsTipsTransform);
		OutSubstateDisplay.OutwardsPhaseTipsTransforms.Add(LocalOutwardsTipsTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform OutwardsInnerCylinderTransform;
		GetRectangleTransformDirectionZ(
			OutwardsBackLocation, OutwardsFrontLocation,
			InnerDiameter, InnerDiameter,
			DirectionAxisY, OutSubstateDisplay.OutwardsInnerCylinderTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform OutwardsBoundingCylinderTransform;
		GetRectangleTransformDirectionZ(
			OutwardsBackLocation, OutwardsFrontLocation,
			OuterDiameter, OuterDiameter,
			FVector(1.0, 0.0, 0.0), OutSubstateDisplay.OutwardsBoundingCylinderTransform);
		if(InDerive.MapToSubstateAngleStarting[LocalTransition]- InDerive.MapToSubstateAngleFinal[LocalTransition]<-5.0 
			|| InDerive.MapToSubstateAngleStarting[LocalTransition] - InDerive.MapToSubstateAngleFinal[LocalTransition] > 5.0){
		//if (5.0 < FMath::Abs(InDerive.MapToSubstateAngleStarting[LocalTransition]
		//	- (FMath::RoundToNegativeInfinity(InDerive.MapToSubstateAngleStarting[LocalTransition] / 360.0)) * 360.0)
		//	- (InDerive.MapToSubstateAngleFinal[LocalTransition]
		//		- (FMath::RoundToNegativeInfinity(InDerive.MapToSubstateAngleFinal[LocalTransition] / 360.0)) * 360.0)) {
			//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> FlattenedPhaseBarsTransforms;
			TArray < FTransform > LocalPhaseBars;
			GetTransitionPhaseBlocksFromStartRadiusTransformArray(
				InParam.SubBlockLength,
				InParam.SubBlockSpokeDepth,
				OuterRadius,
				InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
				0.0,
				-InDerive.MapToSubstateAngleStarting[LocalTransition],
				-InDerive.MapToSubstateAngleFinal[LocalTransition],
				OutwardsBackLocation + FVector(0.0, InParam.OffsetSubstateSpokesAxisY, 0.0),
				OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateSpokesAxisY, 0.0),
				FVector(1.0, 0.0, 0.0),
				FVector(0.0, 1.0, 0.0),
				true,
				InParam.SubBlockMultiplier,
				LocalPhaseBars);
				//OutSubstateDisplay.FlattenedPhaseBarsTransforms);
			for (int32 LocalTransformIndex = 1; LocalTransformIndex < (LocalPhaseBars.Num() - 1);LocalTransformIndex++) {
				OutSubstateDisplay.FlattenedPhaseBarsTransforms.Add(LocalPhaseBars[LocalTransformIndex]);
			}
			//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> FlattenedPhaseTipsTransforms;
			TArray < FTransform > LocalPhaseTips;
			GetTransitionPhaseBlocksFromStartRadiusTransformArray(
				InParam.SubBlockLength,
				InParam.SubBlockTipDepth,
				OuterRadius,
				InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
				InParam.SpokeTipsProportionStart,
				-InDerive.MapToSubstateAngleStarting[LocalTransition],
				-InDerive.MapToSubstateAngleFinal[LocalTransition],
				OutwardsBackLocation + FVector(0.0, InParam.OffsetSubstateSpokesAxisY + InParam.OffsetPhaseTipsFromSpokes, 0.0),
				OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateSpokesAxisY + InParam.OffsetPhaseTipsFromSpokes, 0.0),
				FVector(1.0, 0.0, 0.0),
				FVector(0.0, 1.0, 0.0),
				true,
				InParam.SubBlockMultiplier,
				LocalPhaseTips);
				//OutSubstateDisplay.FlattenedPhaseTipsTransforms);
			for (int32 LocalTransformIndex = 1; LocalTransformIndex < (LocalPhaseTips.Num() - 1);LocalTransformIndex++) {
				OutSubstateDisplay.FlattenedPhaseTipsTransforms.Add(LocalPhaseTips[LocalTransformIndex]);
			}
		}
		
		////UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform EdgeCylinderTransform;
		//OutSubstateDisplay.EdgeCylinderTransform = FTransform(
		//	RotatorZero, OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateEdgeAxisY, 0.0),
		//	FVector(OuterRadius, InParam.ThicknessSubstateDisc, OuterRadius));
		FVector AdjustedEdgeCylinderLocation =
			OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateEdgeAxisY, 0.0);
		GetRectangleTransformDirectionZ(
			AdjustedEdgeCylinderLocation - FVector(0.0, InParam.ThicknessSubstateDisc, 0.0),
			AdjustedEdgeCylinderLocation,
			OuterDiameter, OuterDiameter,
			DirectionAxisY, OutSubstateDisplay.EdgeCylinderTransform);
		////UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform BackgroundCylinderTransform;
		FVector AdjustedBackgroundCylinderLocation =
			OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateBackgroundAxisY, 0.0);
		GetRectangleTransformDirectionZ(
			AdjustedBackgroundCylinderLocation - FVector(0.0, InParam.ThicknessSubstateDisc, 0.0),
			AdjustedBackgroundCylinderLocation,
			OuterDiameter, OuterDiameter,
			DirectionAxisY, OutSubstateDisplay.BackgroundCylinderTransform);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform InnerCylinderTransform;
		FVector AdjustedCentralCylinderLocation =
			OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateCentralDiscAxisY, 0.0);
		GetRectangleTransformDirectionZ(
			AdjustedCentralCylinderLocation - FVector(0.0, InParam.ThicknessSubstateDisc, 0.0),
			AdjustedCentralCylinderLocation,
			OuterDiameter* InParam.ProportionalSubstateCenterDisc,
			OuterDiameter* InParam.ProportionalSubstateCenterDisc,
			DirectionAxisY, OutSubstateDisplay.InnerCylinderTransform);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////// BEGIN SUB STATE ARROW STUFF ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		FVector DirectionOfArrow = UKismetMathLibrary::RotateAngleAxis( FVector(1.0, 0.0, 0.0), InDerive.MapToSubstateAngleFinal[LocalTransition], FVector(0.0, -1.0, 0.0));
		FRotator LocalDirectionRotatorZXFacingYZeroAtX = UKismetMathLibrary::MakeRotFromZX(DirectionOfArrow, FVector(1.0, 0.0, 0.0));
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform KetSubstateFinalArrowTransform;
		FVector AdjustedKetSubstateFinalArrowLocation =
			OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateArrowAxisY, 0.0) - FVector(0.0, 0.5 * InParam.ThicknessSubstateDisc, 0.0);
		float LocalSizeOfSubstateCylinderGroup =
			InParam.FillProportionCylinderMainStateRadiusOfSmallestBoxDimension
			* FMath::Min(InDerive.SizeMainStateBox.X, InDerive.SizeMainStateBox.Z);
		GetRectangleTransformDirectionZ(
			AdjustedKetSubstateFinalArrowLocation - DirectionOfArrow * OuterRadius
			* InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			AdjustedKetSubstateFinalArrowLocation + DirectionOfArrow * OuterRadius
			* InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			InParam.ThicknessSubstateArrow,
			//OuterRadius * InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			InParam.ThicknessSubstateDisc,
			DirectionAxisY, OutSubstateDisplay.KetSubstateFinalArrowTransform);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////// BEGIN MAIN STATE VERSION OF SUBSTATE ADDED ARROW STUFF ///////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform KetSubstateAddedArrowTransform;
		//InDerive.MapPositionKetInitialMainState[FIntPoint(LocalTransition.X, LocalTransition.Y)];
		FVector LocalTargetKetLocation = InDerive.MapPositionKetInitialMainState[FIntPoint(LocalTransition.X + 1, LocalTransition.Z)];
		float SizeOfMainStateCylinderGroup =
			InParam.FillProportionCylinderMainStateRadiusOfSmallestBoxDimension
			* FMath::Min(InDerive.SizeMainStateBox.X, InDerive.SizeMainStateBox.Z);
		FVector LocalKetAddedArrowSizeVector = 
			FVector(SizeOfMainStateCylinderGroup, InDerive.SizeMainStateBox.Y, SizeOfMainStateCylinderGroup);
		FVector AdjustedKetAddedArrowLocation =
			LocalTargetKetLocation
			+ FVector(0.0, InParam.OffsetSubstateArrowAxisY, 0.0);
			//- FVector(0.0, 0.5 * LocalKetAddedArrowSizeVector.Y, 0.0);
		FVector AdjustedKetAddedArrowLocationStart = 
			AdjustedKetAddedArrowLocation 
			+ InDerive.MapToSubstateAddedTwoVectors[LocalTransition].v1 
			* 0.5 * SizeOfMainStateCylinderGroup;
		FVector AdjustedKetAddedArrowLocationStop =
			AdjustedKetAddedArrowLocation
			+ InDerive.MapToSubstateAddedTwoVectors[LocalTransition].v2
			* 0.5 * SizeOfMainStateCylinderGroup;
		FVector AdjustedKetAddedArrowLocationDelta = 
			AdjustedKetAddedArrowLocationStop - AdjustedKetAddedArrowLocationStart;
		GetRectangleTransformDirectionZ(
			AdjustedKetAddedArrowLocationStart - AdjustedKetAddedArrowLocationDelta,
			AdjustedKetAddedArrowLocationStart + AdjustedKetAddedArrowLocationDelta,
			InParam.ThicknessMainStateAddedArrow,
			LocalKetAddedArrowSizeVector.Y,
			DirectionAxisY, OutSubstateDisplay.KetSubstateAddedArrowTransform);
		//OutSubstateDisplay.InnerCylinderTransform = FTransform(
		//	RotatorZero, OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateCentralDiscAxisY, 0.0),
		//	FVector(OuterRadius, InParam.ThicknessSubstateDisc, OuterRadius));
	}
	else SuccessFlag = false;
}
void UQCDisplayBlueprintFxnLibrary::GetRectangleTransformDirectionZ(
	FVector StartPosition,
	FVector EndPosition,
	float LengthX,
	float DepthY,
	FVector DirectionTowardsAxisY,
	FTransform& OutputTransform) {
	FVector DimensionsVector = FVector(LengthX, DepthY, (EndPosition - StartPosition).Size());
	FVector FinalPosition = (StartPosition + EndPosition) / 2.0;// -ScaledOffset;
	FVector DirectionTravel = (EndPosition - StartPosition).GetSafeNormal();
	FRotator FinalRotator = UKismetMathLibrary::MakeRotFromZY(DirectionTravel, DirectionTowardsAxisY);
	//FVector RotatedDimensionsVector = FinalRotator.RotateVector(DimensionsVector);
	OutputTransform = FTransform(FinalRotator, FinalPosition, DimensionsVector);
}
void UQCDisplayBlueprintFxnLibrary::GetTransitionPhaseBlocksFromStartRadiusTransformArray(
	float TargetSizeSubBlocks,
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float RadiusFinalFractionStart,
	float AngleStartDegrees,
	float AngleEndDegrees,
	FVector StartPosition,
	FVector EndPosition,
	FVector TowardsZeroDegrees,
	FVector EvolutionDirection,
	bool FixedAtEndPositionFlag,
	int32 SubBlockHighlightMultiplier,
	TArray<FTransform>& TransformBlockArray) {
	TransformBlockArray.Empty();
	FVector FromToVector = EndPosition - StartPosition;
	float WaveDistance = FromToVector.Size();
	int32 TargetNumberOfBlocks = FMath::CeilToInt(WaveDistance / TargetSizeSubBlocks);
	int32 NumberOfDivisions = FMath::CeilToInt(TargetNumberOfBlocks / SubBlockHighlightMultiplier);
	int32 NumberOfBlocks = NumberOfDivisions * SubBlockHighlightMultiplier;
	float BlockLength = WaveDistance / NumberOfBlocks;
	if(FixedAtEndPositionFlag)
		BlockLength = TargetSizeSubBlocks;
	for (int32 Index = 0; Index <= NumberOfBlocks; Index++) {
		//if (Index % SubBlockHighlightMultiplier == 0) {
		//	SubBlockHighlightOffsets.Add(Index);
		//}
		float ProportionCompletedAngle = (1.0 * Index) / (1.0 * NumberOfBlocks);
		float DistancePortionStart = Index / (NumberOfBlocks + 1.0);
		float DistancePortionEnd = (Index + 1.0) / (NumberOfBlocks + 1.0);
		float DistancePortionSet = (Index + 0.5) / (NumberOfBlocks + 1.0);
		//float DistancePortionCenter = (DistancePortionStart + DistancePortionEnd) / 2.0;
		FVector PositionOfSpokeStart =
			FromToVector * DistancePortionSet + StartPosition;
		if (FixedAtEndPositionFlag)
			PositionOfSpokeStart = EndPosition;
		float CurrentAngle =
			(AngleEndDegrees - AngleStartDegrees) * ProportionCompletedAngle + AngleStartDegrees;
		float RadiusOfSpokeSpin = BaseRadius * TransitionRadiusFraction;
		FVector PositionOfSpokeStartModifiedAtZeroDegrees =
			RadiusOfSpokeSpin * RadiusFinalFractionStart * TowardsZeroDegrees;
		FVector PositionOfSpokeStartModified = PositionOfSpokeStart +
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeStartModifiedAtZeroDegrees, CurrentAngle, EvolutionDirection);
		FVector PositionOfSpokeEndAtZeroDegrees = RadiusOfSpokeSpin * TowardsZeroDegrees;
		FVector PositionOfSpokeEnd = PositionOfSpokeStart +
			UKismetMathLibrary::RotateAngleAxis(
				PositionOfSpokeEndAtZeroDegrees, CurrentAngle, EvolutionDirection);
		//FVector DimensionsVector = FVector(BlockLength, WidthSubBlocks, RadiusOfSpokeSpin);
		FTransform LocalTransform;
		GetRectangleTransformDirectionZ(
			PositionOfSpokeStartModified,
			PositionOfSpokeEnd,
			BlockLength,
			WidthSubBlocks,
			TowardsZeroDegrees,
			//TowardsZeroDegrees,
			LocalTransform);
		TransformBlockArray.Add(LocalTransform);
	}
}
void UQCDisplayBlueprintFxnLibrary::GetTransitionPhaseBlocksFromStartRadiusTransformSingle(
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float RadiusFinalFractionStart,
	float AngleStartEndDegrees,
	FVector StartPosition,
	FVector EndPosition,
	FVector TowardsZeroDegrees,
	bool ReflectedFlag,
	FTransform& TransformSingle) {
	float RadiusOfSpokeSpin = BaseRadius * TransitionRadiusFraction;
	FVector FromToVector = EndPosition - StartPosition;
	FVector EvolutionDirection = FromToVector.GetSafeNormal();
	float WaveDistance = FromToVector.Size();
	FVector DirectionZ;
	if (ReflectedFlag) {
		DirectionZ = FVector::CrossProduct(EvolutionDirection, TowardsZeroDegrees).GetSafeNormal();
	}
	else {
		DirectionZ = FVector::CrossProduct(EvolutionDirection, TowardsZeroDegrees).GetSafeNormal();
	}
	FVector SizeVector =
		DirectionZ * WidthSubBlocks
		+ EvolutionDirection * FromToVector.Size()
		+ (1.0 - RadiusFinalFractionStart) * RadiusOfSpokeSpin * TowardsZeroDegrees;
	FRotator FinalRotation;
	if (ReflectedFlag) {
		FinalRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(EvolutionDirection, -AngleStartEndDegrees);
	}
	else {
		FinalRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(EvolutionDirection, AngleStartEndDegrees);
	}
	FVector ZeroDegreesSpoke = TowardsZeroDegrees * RadiusOfSpokeSpin;
	FVector OffsetStartDegreesSpoke = RadiusFinalFractionStart * FinalRotation.RotateVector(ZeroDegreesSpoke);
	FVector OffsetEndDegreesSpoke = FinalRotation.RotateVector(ZeroDegreesSpoke);
	FVector FinalPosition =
		StartPosition
		+ (OffsetStartDegreesSpoke + OffsetEndDegreesSpoke) / 2.0
		+ FromToVector / 2.0;
	TransformSingle = FTransform(FinalRotation, FinalPosition, SizeVector);
}
void UQCDisplayBlueprintFxnLibrary::InitializeQuantumTransitionSubstateDisplaySimplified(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InParam, //InputDisplayParam,
	FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
	int32 OperationIndex,
	int32 KetStateFrom,
	int32 KetStateTo,
	bool& SuccessFlag,
	FQuantumTransitionDisplaySimplified& OutSubstateDisplay) {
	FIntPoint LocalOpKetTo = FIntPoint(OperationIndex, KetStateFrom);
	FIntPoint LocalOpKetFrom = FIntPoint(OperationIndex, KetStateTo);
	FIntVector LocalTransition = FIntVector(OperationIndex, KetStateFrom, KetStateTo);
	FRotator RotatorZero = FRotator::FRotator(0.0, 0.0, 0.0);
	if (InDerive.MapPositionStart.Contains(LocalTransition) &&
		InDerive.MapPositionTurn.Contains(LocalTransition) &&
		InDerive.MapPositionStop.Contains(LocalTransition) &&
		InDerive.MapPositionOutwardsBack.Contains(LocalTransition) && 
		InDerive.MapPositionOutwardsFront.Contains(LocalTransition) &&
		InDerive.MapIndexToBaseRadius.Contains(OperationIndex) &&
		InDerive.MapSubstateMagnitudesFinalized.Contains(LocalTransition) &&
		InDerive.MapToSubstateAngleStarting.Contains(LocalTransition) &&
		InDerive.MapToSubstateAngleFinal.Contains(LocalTransition)) {
		SuccessFlag = true;
		FVector StartLocation = InDerive.MapPositionStart[LocalTransition];
		FVector TurnLocation = InDerive.MapPositionTurn[LocalTransition];
		FVector StopLocation = InDerive.MapPositionStop[LocalTransition];
		FVector OutwardsBackLocation = InDerive.MapPositionOutwardsBack[LocalTransition];
		FVector OutwardsFrontLocation = InDerive.MapPositionOutwardsFront[LocalTransition];
		float OuterDiameter = InDerive.MapIndexToBaseRadius[OperationIndex];
		float InnerDiameter = OuterDiameter * InParam.InnerRadiusAsFractionOfMainRadius;
		float SpokeRadius = OuterDiameter * InDerive.MapSubstateMagnitudesFinalized[LocalTransition];
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> StartToTurnTransforms;
		GetTransitionBlocksTransformArray(
			InParam.SubBlockLength,
			InParam.SubBlockThickness,
			OuterDiameter,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			0.0,
			InDerive.MapToSubstateAngleStarting[LocalTransition],
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			StartLocation,
			TurnLocation,
			FVector(0.0, 1.0, 0.0),
			FVector(1.0, 0.0, 0.0),
			false,
			InParam.SubBlockMultiplier,
			OutSubstateDisplay.StartToTurnTransforms);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> TurnToStopTransforms;
		GetTransitionBlocksTransformArray(
			InParam.SubBlockLength,
			InParam.SubBlockThickness,
			OuterDiameter,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			0.0,
			InDerive.MapToSubstateAngleStarting[LocalTransition],
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			TurnLocation,
			StopLocation,
			FVector(0.0, 1.0, 0.0),
			FVector(1.0, 0.0, 0.0),
			false,
			InParam.SubBlockMultiplier,
			OutSubstateDisplay.TurnToStopTransforms);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> OutwardsTransforms;
		GetTransitionBlocksTransformArray(
			InParam.SubBlockLength,
			InParam.SubBlockThickness,
			OuterDiameter,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			0.0,
			InDerive.MapToSubstateAngleStarting[LocalTransition],
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			OutwardsBackLocation,
			OutwardsFrontLocation,
			FVector(1.0, 0.0, 0.0),
			FVector(0.0, 1.0, 0.0),
			false,
			InParam.SubBlockMultiplier,
			OutSubstateDisplay.OutwardsTransforms);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTransform> FlattenedTransforms;
		GetTransitionBlocksTransformArray(
			InParam.SubBlockLength,
			InParam.SubBlockThickness,
			OuterDiameter,
			InDerive.MapSubstateMagnitudesFinalized[LocalTransition],
			0.0,
			InDerive.MapToSubstateAngleStarting[LocalTransition],
			InDerive.MapToSubstateAngleFinal[LocalTransition],
			OutwardsBackLocation,
			OutwardsFrontLocation,
			FVector(1.0, 0.0, 0.0),
			FVector(0.0, 1.0, 0.0),
			true,
			InParam.SubBlockMultiplier,
			OutSubstateDisplay.FlattenedTransforms);
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform EdgeCylinderTransform;
		OutSubstateDisplay.EdgeCylinderTransform = FTransform(
			RotatorZero, OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateEdgeAxisY, 0.0),
			FVector(OuterDiameter, InParam.ThicknessSubstateDisc, OuterDiameter));
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform BackgroundCylinderTransform;
		OutSubstateDisplay.BackgroundCylinderTransform = FTransform(
			RotatorZero, OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateBackgroundAxisY, 0.0),
			FVector(OuterDiameter, InParam.ThicknessSubstateDisc, OuterDiameter));
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) FTransform InnerCylinderTransform;
		OutSubstateDisplay.EdgeCylinderTransform = FTransform(
			RotatorZero, OutwardsFrontLocation + FVector(0.0, InParam.OffsetSubstateCentralDiscAxisY, 0.0),
			FVector(OuterDiameter, InParam.ThicknessSubstateDisc, OuterDiameter));
	}
	else SuccessFlag = false;
}
void UQCDisplayBlueprintFxnLibrary::GetTransitionBlocksTransformArray(
	float TargetSizeSubBlocks,
	float WidthSubBlocks,
	float BaseRadius,
	float TransitionRadiusFraction,
	float RadiusFinalFractionStart,
	float AngleStartDegrees,
	float AngleEndDegrees,
	FVector StartPosition,
	FVector EndPosition,
	FVector TowardsZeroDegrees,
	FVector EvolutionDirection,
	bool FixedAtEndPositionFlag,
	int32 SubBlockHighlightMultiplier,
	TArray<FTransform>& TransformBlockArray) {
	TransformBlockArray.Empty();
	FVector FromToVector = EndPosition - StartPosition;
	float WaveDistance = FromToVector.Size();
	int32 TargetNumberOfBlocks = FMath::CeilToInt(WaveDistance / TargetSizeSubBlocks);
	int32 NumberOfDivisions = FMath::CeilToInt(TargetNumberOfBlocks / SubBlockHighlightMultiplier);
	int32 NumberOfBlocks = NumberOfDivisions * SubBlockHighlightMultiplier;
	float BlockLength = WaveDistance / NumberOfBlocks;
	float SizeOfCylinderYZ = 2 * BaseRadius * TransitionRadiusFraction;
	if (FixedAtEndPositionFlag)
		BlockLength = TargetSizeSubBlocks;
	for (int32 Index = 0; Index <= NumberOfBlocks; Index++) {
		float ProportionCompletedAngle = (1.0 * Index) / (1.0 * NumberOfBlocks);
		float DistancePortionStart = Index / (NumberOfBlocks + 1.0);
		float DistancePortionEnd = (Index + 1.0) / (NumberOfBlocks + 1.0);
		float DistancePortionSet = (Index + 0.5) / (NumberOfBlocks + 1.0);
		//float DistancePortionCenter = (DistancePortionStart + DistancePortionEnd) / 2.0;
		FVector PositionCurrent =
			FromToVector * DistancePortionSet + StartPosition;
		if (FixedAtEndPositionFlag)
			PositionCurrent = EndPosition;
		float CurrentAngle =
			(AngleEndDegrees - AngleStartDegrees) * ProportionCompletedAngle + AngleStartDegrees;
		FVector DirectionFromBaseZeroDegrees =
			UKismetMathLibrary::RotateAngleAxis(
				FVector(0.0, 1.0, 0.0), CurrentAngle, FVector(1.0, 0.0, 0.0));
		FRotator RotationFinal = 
			UKismetMathLibrary::MakeRotFromXY(EvolutionDirection, DirectionFromBaseZeroDegrees);
		//FVector DimensionsVector = FVector(BlockLength, WidthSubBlocks, RadiusOfSpokeSpin);
		//FTransform LocalTransform = FTransform(RotationFinal, PositionFinal, FVector(SizeOfCylinderYZ, BlockLength, SizeOfCylinderXZ));
		//TransformBlockArray.Add(LocalTransform);
		TransformBlockArray.Add(
			FTransform(RotationFinal, PositionCurrent,
				FVector(BlockLength, SizeOfCylinderYZ, SizeOfCylinderYZ)));
	}
}
void UQCDisplayBlueprintFxnLibrary::AddTransformsTransition(
	TMap< ETransitionISMC, FVector>& MapSizesISMC,
	FQuantumTransitionDisplay& SubstateDisplayToAdd,
	TMap < ETransitionISMC, UInstancedStaticMeshComponent*>& MapTransitionsISMC) {
	if (MapTransitionsISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsStartToTurn) && MapSizesISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsStartToTurn)) {
		if (MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsStartToTurn].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.StartToTurnPhaseBarsTransforms) {
				MapTransitionsISMC[ETransitionISMC::WaveSpokesForTransitionsStartToTurn]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsStartToTurn]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsTurnToStop) && MapSizesISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsTurnToStop)) {
		if (MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsTurnToStop].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.TurnToStopPhaseBarsTransforms) {
				MapTransitionsISMC[ETransitionISMC::WaveSpokesForTransitionsTurnToStop]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsTurnToStop]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsOutward) && MapSizesISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsOutward)) {
		if (MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsOutward].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.OutwardsPhaseBarsTransforms) {
				MapTransitionsISMC[ETransitionISMC::WaveSpokesForTransitionsOutward]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsOutward]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsFlattened) && MapSizesISMC.Contains(ETransitionISMC::WaveSpokesForTransitionsFlattened)) {
		if (MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsFlattened].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.FlattenedPhaseBarsTransforms) {
				MapTransitionsISMC[ETransitionISMC::WaveSpokesForTransitionsFlattened]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::WaveSpokesForTransitionsFlattened]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::TipSpokesForTransitionsStartToTurn) && MapSizesISMC.Contains(ETransitionISMC::TipSpokesForTransitionsStartToTurn)) {
		if (MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsStartToTurn].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.StartToTurnPhaseTipsTransforms) {
				MapTransitionsISMC[ETransitionISMC::TipSpokesForTransitionsStartToTurn]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsStartToTurn]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::TipSpokesForTransitionsTurnToStop) && MapSizesISMC.Contains(ETransitionISMC::TipSpokesForTransitionsTurnToStop)) {
		if (MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsTurnToStop].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.TurnToStopPhaseTipsTransforms) {
				MapTransitionsISMC[ETransitionISMC::TipSpokesForTransitionsTurnToStop]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsTurnToStop]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::TipSpokesForTransitionsOutward) && MapSizesISMC.Contains(ETransitionISMC::TipSpokesForTransitionsOutward)) {
		if (MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsOutward].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.OutwardsPhaseTipsTransforms) {
				MapTransitionsISMC[ETransitionISMC::TipSpokesForTransitionsOutward]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsOutward]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::TipSpokesForTransitionsFlattened) && MapSizesISMC.Contains(ETransitionISMC::TipSpokesForTransitionsFlattened)) {
		if (MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsFlattened].GetMin() > 0.0) {
			for (auto& iter : SubstateDisplayToAdd.FlattenedPhaseTipsTransforms) {
				MapTransitionsISMC[ETransitionISMC::TipSpokesForTransitionsFlattened]->AddInstance(
					FTransform(iter.GetRotation(), iter.GetLocation(),
						iter.GetScale3D() / MapSizesISMC[ETransitionISMC::TipSpokesForTransitionsFlattened]));
			}
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::CoreCylindersStartToTurn) && MapSizesISMC.Contains(ETransitionISMC::CoreCylindersStartToTurn)) {
		if (MapSizesISMC[ETransitionISMC::CoreCylindersStartToTurn].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::CoreCylindersStartToTurn]->AddInstance(
				FTransform(SubstateDisplayToAdd.StartToTurnInnerCylinderTransform.GetRotation(), SubstateDisplayToAdd.StartToTurnInnerCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.StartToTurnInnerCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::CoreCylindersStartToTurn]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::CoreCylindersTurnToStop) && MapSizesISMC.Contains(ETransitionISMC::CoreCylindersTurnToStop)) {
		if (MapSizesISMC[ETransitionISMC::CoreCylindersTurnToStop].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::CoreCylindersTurnToStop]->AddInstance(
				FTransform(SubstateDisplayToAdd.TurnToStopInnerCylinderTransform.GetRotation(), SubstateDisplayToAdd.TurnToStopInnerCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.TurnToStopInnerCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::CoreCylindersTurnToStop]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::CoreCylindersOutward) && MapSizesISMC.Contains(ETransitionISMC::CoreCylindersOutward)) {
		if (MapSizesISMC[ETransitionISMC::CoreCylindersOutward].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::CoreCylindersOutward]->AddInstance(
				FTransform(SubstateDisplayToAdd.OutwardsInnerCylinderTransform.GetRotation(), SubstateDisplayToAdd.OutwardsInnerCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.OutwardsInnerCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::CoreCylindersOutward]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::BoundingCylindersStartToTurn) && MapSizesISMC.Contains(ETransitionISMC::BoundingCylindersStartToTurn)) {
		if (MapSizesISMC[ETransitionISMC::BoundingCylindersStartToTurn].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::BoundingCylindersStartToTurn]->AddInstance(
				FTransform(SubstateDisplayToAdd.StartToTurnBoundingCylinderTransform.GetRotation(), SubstateDisplayToAdd.StartToTurnBoundingCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.StartToTurnBoundingCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::BoundingCylindersStartToTurn]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::WaveSplittersSubstate) && MapSizesISMC.Contains(ETransitionISMC::WaveSplittersSubstate)) {
		if (MapSizesISMC[ETransitionISMC::WaveSplittersSubstate].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::WaveSplittersSubstate]->AddInstance(
				FTransform(SubstateDisplayToAdd.SplitterTransform.GetRotation(), SubstateDisplayToAdd.SplitterTransform.GetLocation(),
					SubstateDisplayToAdd.SplitterTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::WaveSplittersSubstate]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::BoundingCylindersTurnToStop) && MapSizesISMC.Contains(ETransitionISMC::BoundingCylindersTurnToStop)) {
		if (MapSizesISMC[ETransitionISMC::BoundingCylindersTurnToStop].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::BoundingCylindersTurnToStop]->AddInstance(
				FTransform(SubstateDisplayToAdd.TurnToStopBoundingCylinderTransform.GetRotation(), SubstateDisplayToAdd.TurnToStopBoundingCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.TurnToStopBoundingCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::BoundingCylindersTurnToStop]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::BoundingCylindersOutward) && MapSizesISMC.Contains(ETransitionISMC::BoundingCylindersOutward)) {
		if (MapSizesISMC[ETransitionISMC::BoundingCylindersOutward].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::BoundingCylindersOutward]->AddInstance(
				FTransform(SubstateDisplayToAdd.OutwardsBoundingCylinderTransform.GetRotation(), SubstateDisplayToAdd.OutwardsBoundingCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.OutwardsBoundingCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::BoundingCylindersOutward]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::DiscSubstateBackground) && MapSizesISMC.Contains(ETransitionISMC::DiscSubstateBackground)) {
		if (MapSizesISMC[ETransitionISMC::DiscSubstateBackground].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::DiscSubstateBackground]->AddInstance(
				FTransform(SubstateDisplayToAdd.BackgroundCylinderTransform.GetRotation(), SubstateDisplayToAdd.BackgroundCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.BackgroundCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::DiscSubstateBackground]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::DiscSubstateEdge) && MapSizesISMC.Contains(ETransitionISMC::DiscSubstateEdge)) {
		if (MapSizesISMC[ETransitionISMC::DiscSubstateEdge].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::DiscSubstateEdge]->AddInstance(
				FTransform(SubstateDisplayToAdd.EdgeCylinderTransform.GetRotation(), SubstateDisplayToAdd.EdgeCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.EdgeCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::DiscSubstateEdge]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::DiscSubstateCenter) && MapSizesISMC.Contains(ETransitionISMC::DiscSubstateCenter)) {
		if (MapSizesISMC[ETransitionISMC::DiscSubstateCenter].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::DiscSubstateCenter]->AddInstance(
				FTransform(SubstateDisplayToAdd.InnerCylinderTransform.GetRotation(), SubstateDisplayToAdd.InnerCylinderTransform.GetLocation(),
					SubstateDisplayToAdd.InnerCylinderTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::DiscSubstateCenter]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::KetSubstateArrow) && MapSizesISMC.Contains(ETransitionISMC::KetSubstateArrow)) {
		if (MapSizesISMC[ETransitionISMC::KetSubstateArrow].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::KetSubstateArrow]->AddInstance(
				FTransform(SubstateDisplayToAdd.KetSubstateFinalArrowTransform.GetRotation(), SubstateDisplayToAdd.KetSubstateFinalArrowTransform.GetLocation(),
					SubstateDisplayToAdd.KetSubstateFinalArrowTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::KetSubstateArrow]));
		}
	}
	if (MapTransitionsISMC.Contains(ETransitionISMC::KetSubstateAddedArrow) && MapSizesISMC.Contains(ETransitionISMC::KetSubstateAddedArrow)) {
		if (MapSizesISMC[ETransitionISMC::KetSubstateAddedArrow].GetMin() > 0.0) {
			MapTransitionsISMC[ETransitionISMC::KetSubstateAddedArrow]->AddInstance(
				FTransform(SubstateDisplayToAdd.KetSubstateFinalArrowTransform.GetRotation(), SubstateDisplayToAdd.KetSubstateAddedArrowTransform.GetLocation(),
					SubstateDisplayToAdd.KetSubstateAddedArrowTransform.GetScale3D() / MapSizesISMC[ETransitionISMC::KetSubstateAddedArrow]));
		}
	}
}
void UQCDisplayBlueprintFxnLibrary::AddTransformsKetState(
	TMap< EKetDisplayISMC, FVector>& MapSizesISMC,
	FQuantumKetDisplay& MainStateDisplayToAdd,
	TMap <EKetDisplayISMC, UInstancedStaticMeshComponent*>& MapKetsISMC) {
	if (MapKetsISMC.Contains(EKetDisplayISMC::MainDisplayBox) && MapSizesISMC.Contains(EKetDisplayISMC::MainDisplayBox)) {
		if (MapSizesISMC[EKetDisplayISMC::MainDisplayBox].GetMin() > 0.0) {
			MapKetsISMC[EKetDisplayISMC::MainDisplayBox]->AddInstance(
				FTransform(MainStateDisplayToAdd.MainBoxTransform.GetRotation(), MainStateDisplayToAdd.MainBoxTransform.GetLocation(),
					MainStateDisplayToAdd.MainBoxTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::MainDisplayBox]));
		}
	}
	if (MapKetsISMC.Contains(EKetDisplayISMC::CylinderMainStateEdge) && MapSizesISMC.Contains(EKetDisplayISMC::CylinderMainStateEdge)) {
		if (MapSizesISMC[EKetDisplayISMC::CylinderMainStateEdge].GetMin() > 0.0) {
			MapKetsISMC[EKetDisplayISMC::CylinderMainStateEdge]->AddInstance(
				FTransform(MainStateDisplayToAdd.EdgeCylinderTransform.GetRotation(), MainStateDisplayToAdd.EdgeCylinderTransform.GetLocation(),
					MainStateDisplayToAdd.EdgeCylinderTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::CylinderMainStateEdge]));
		}
	}
	if (MainStateDisplayToAdd.NonZeroKet) {
		if (MapKetsISMC.Contains(EKetDisplayISMC::CylinderMainStateMagnitude) && MapSizesISMC.Contains(EKetDisplayISMC::CylinderMainStateMagnitude)) {
			if (MapSizesISMC[EKetDisplayISMC::CylinderMainStateMagnitude].GetMin()>0.0) {
				MapKetsISMC[EKetDisplayISMC::CylinderMainStateMagnitude]->AddInstance(
					FTransform(MainStateDisplayToAdd.MagnitudeCylinderTransform.GetRotation(), MainStateDisplayToAdd.MagnitudeCylinderTransform.GetLocation(),
						MainStateDisplayToAdd.MagnitudeCylinderTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::CylinderMainStateMagnitude]));
			}
		}
		if (MapKetsISMC.Contains(EKetDisplayISMC::CylinderMainStateInner) && MapSizesISMC.Contains(EKetDisplayISMC::CylinderMainStateInner)) {
			if (MapSizesISMC[EKetDisplayISMC::CylinderMainStateInner].GetMin() > 0.0) {
				MapKetsISMC[EKetDisplayISMC::CylinderMainStateInner]->AddInstance(
					FTransform(MainStateDisplayToAdd.InnerCylinderTransform.GetRotation(), MainStateDisplayToAdd.InnerCylinderTransform.GetLocation(),
						MainStateDisplayToAdd.InnerCylinderTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::CylinderMainStateInner]));
			}
		}
		if (MapKetsISMC.Contains(EKetDisplayISMC::FinalKetStateArrow) && MapSizesISMC.Contains(EKetDisplayISMC::FinalKetStateArrow)) {
			if (MapSizesISMC[EKetDisplayISMC::FinalKetStateArrow].GetMin() > 0.0) {
				MapKetsISMC[EKetDisplayISMC::FinalKetStateArrow]->AddInstance(
					FTransform(MainStateDisplayToAdd.FinalKetStateArrowTransform.GetRotation(), MainStateDisplayToAdd.FinalKetStateArrowTransform.GetLocation(),
						MainStateDisplayToAdd.FinalKetStateArrowTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::FinalKetStateArrow]));
			}
		}
		if (MapKetsISMC.Contains(EKetDisplayISMC::FinalKetDirection) && MapSizesISMC.Contains(EKetDisplayISMC::FinalKetDirection)) {
			if (MapSizesISMC[EKetDisplayISMC::FinalKetDirection].GetMin() > 0.0) {
				MapKetsISMC[EKetDisplayISMC::FinalKetDirection]->AddInstance(
					FTransform(MainStateDisplayToAdd.FinalKetDirectionTransform.GetRotation(), MainStateDisplayToAdd.FinalKetDirectionTransform.GetLocation(),
						MainStateDisplayToAdd.FinalKetDirectionTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::FinalKetDirection]));
			}
		}
	}
}
void UQCDisplayBlueprintFxnLibrary::GetTransformsKetState(
	TMap< EKetDisplayISMC, FVector>& MapSizesISMC,
	FQuantumKetDisplay& MainStateDisplayToAdd,
	TMap <FIntPoint, FTransform>& MapKetsTransform) {
	int32 CurrentCount = 0;
	if (MapKetsTransform.Contains(FIntPoint(0, 0))) {
		while (MapKetsTransform.Contains(FIntPoint(CurrentCount, 0))) {
			CurrentCount++;
		}
	}
	if (MapSizesISMC.Contains(EKetDisplayISMC::MainDisplayBox)) {
		MapKetsTransform.Add(FIntPoint(CurrentCount, 0), (
			FTransform(MainStateDisplayToAdd.MainBoxTransform.GetRotation(), MainStateDisplayToAdd.MainBoxTransform.GetLocation(),
				MainStateDisplayToAdd.MainBoxTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::MainDisplayBox])));
	}
	if (MapSizesISMC.Contains(EKetDisplayISMC::CylinderMainStateEdge)) {
		MapKetsTransform.Add(FIntPoint(CurrentCount, 1), (
			FTransform(MainStateDisplayToAdd.EdgeCylinderTransform.GetRotation(), MainStateDisplayToAdd.EdgeCylinderTransform.GetLocation(),
				MainStateDisplayToAdd.EdgeCylinderTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::CylinderMainStateEdge])));
	}
	if (MapSizesISMC.Contains(EKetDisplayISMC::CylinderMainStateInner)) {
		MapKetsTransform.Add(FIntPoint(CurrentCount, 3), (
			FTransform(MainStateDisplayToAdd.InnerCylinderTransform.GetRotation(), MainStateDisplayToAdd.InnerCylinderTransform.GetLocation(),
				MainStateDisplayToAdd.InnerCylinderTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::CylinderMainStateInner])));
	}
	if (MainStateDisplayToAdd.NonZeroKet) {
		if (MapSizesISMC.Contains(EKetDisplayISMC::CylinderMainStateMagnitude)) {
			MapKetsTransform.Add(FIntPoint(CurrentCount, 2), (
				FTransform(MainStateDisplayToAdd.MagnitudeCylinderTransform.GetRotation(), MainStateDisplayToAdd.MagnitudeCylinderTransform.GetLocation(),
					MainStateDisplayToAdd.MagnitudeCylinderTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::CylinderMainStateMagnitude])));
		}
		if (MapSizesISMC.Contains(EKetDisplayISMC::FinalKetStateArrow)) {
			MapKetsTransform.Add(FIntPoint(CurrentCount, 4), (
				FTransform(MainStateDisplayToAdd.FinalKetStateArrowTransform.GetRotation(), MainStateDisplayToAdd.FinalKetStateArrowTransform.GetLocation(),
					MainStateDisplayToAdd.FinalKetStateArrowTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::FinalKetStateArrow])));
		}
		if (MapSizesISMC.Contains(EKetDisplayISMC::FinalKetDirection)) {
			MapKetsTransform.Add(FIntPoint(CurrentCount, 5), (
				FTransform(MainStateDisplayToAdd.FinalKetDirectionTransform.GetRotation(), MainStateDisplayToAdd.FinalKetDirectionTransform.GetLocation(),
					MainStateDisplayToAdd.FinalKetDirectionTransform.GetScale3D() / MapSizesISMC[EKetDisplayISMC::FinalKetDirection])));
		}
		
	}
}
void UQCDisplayBlueprintFxnLibrary::InitializeQubitSplitDisplay(
	UMultiMapIntegerActorComponent* InputMMIAC,
	FQuantumDisplayParam& InParam, //InputDisplayParam,
	FQuantumDisplayDerived& InDerive, //InputQuantumDisplayDerived,
	FQuantumQubitSplitDisplay& OutQubitSplitDisplay) {
	for (auto& iterSplitCoord : InputMMIAC->QubitSplitToQubitSplitBase) {
		if (InDerive.MapToQubitSplitPoint.Contains(iterSplitCoord.Key)
			&& InDerive.MapToQubitSplitPoint.Contains(iterSplitCoord.Value)) {
			FVector StartVector = InDerive.MapToQubitSplitPoint[iterSplitCoord.Key];
			FVector StopVector = InDerive.MapToQubitSplitPoint[iterSplitCoord.Value];
			InParam.DiameterCylinderQubitSplitBeam;
			FTransform LocalTransform;
			GetRectangleTransformDirectionZ(
				StartVector, StopVector,
				InParam.DiameterCylinderQubitSplitBeam,
				InParam.DiameterCylinderQubitSplitBeam,
				FVector(1.0, 0.0, 0.0),
				LocalTransform);
			OutQubitSplitDisplay.QubitSplitTunnelParentTransforms.Add(
				iterSplitCoord.Key, LocalTransform);
			if (InputMMIAC->QubitSplitToQubitSplitBaseZeroFalse.Contains(iterSplitCoord.Key)) {
				OutQubitSplitDisplay.QubitSplitTunnelZeroFalseParentTransforms.Add(
					iterSplitCoord.Key, LocalTransform);
			}
			if (InputMMIAC->QubitSplitToQubitSplitBaseOneTrue.Contains(iterSplitCoord.Key)) {
				OutQubitSplitDisplay.QubitSplitTunnelOneTrueParentTransforms.Add(
					iterSplitCoord.Key, LocalTransform);
			}
		}
	}
	for (auto& iterSplitCoord : InputMMIAC->QubitSplitToQubitSplitBase) {
		if (InDerive.MapToQubitSplitPoint.Contains(iterSplitCoord.Key)
			&& InDerive.MapToQubitSplitPoint.Contains(iterSplitCoord.Value)) {
			FVector StartVector = InDerive.MapToQubitSplitPoint[iterSplitCoord.Key];
			FVector StopVector = InDerive.MapToQubitSplitPoint[iterSplitCoord.Value];
			InParam.DiameterCylinderQubitSplitBeam;
			FTransform LocalTransform;
			GetRectangleTransformDirectionZ(
				StartVector, StopVector,
				InParam.DiameterCylinderQubitSplitBeam,
				InParam.DiameterCylinderQubitSplitBeam,
				FVector(1.0, 0.0, 0.0),
				LocalTransform);
			OutQubitSplitDisplay.QubitSplitLabelTransforms.Add(
				iterSplitCoord.Key, LocalTransform);
		}
		else {
			int something = 1;
		}
	}
	for (auto& iterSplitCoord : InDerive.MapToQubitSplitPoint) {
		FVector StartVector = InDerive.MapToQubitSplitPoint[iterSplitCoord.Key]
			- FVector(InParam.DepthCylinderQubitSplitter / 2.0, 0.0, 0.0);
		FVector StopVector = InDerive.MapToQubitSplitPoint[iterSplitCoord.Key]
			+ FVector(InParam.DepthCylinderQubitSplitter / 2.0, 0.0, 0.0);
		FTransform LocalTransform;
		GetRectangleTransformDirectionZ(
			StartVector, StopVector,
			InParam.DiameterCylinderQubitSplitter,
			InParam.DiameterCylinderQubitSplitter,
			FVector(0.0, 1.0, 0.0),
			LocalTransform);
		OutQubitSplitDisplay.QubitSplitLabelTransforms.Add(
			iterSplitCoord.Key, LocalTransform);
	}
	for (auto& iterNewKets : InDerive.MapPositionKetInitialMainState) {
		int32 asomething = 2;
		FVector temp = iterNewKets.Value;
		FVector TopLeftFrontCorner = temp
			+ FVector(-0.5 * InDerive.SizeMainStateBox.X,
				0.5 * InDerive.SizeMainStateBox.Y,
				0.5 * InDerive.SizeMainStateBox.Z);
		FVector MinorOffset = FVector(5.0, 5.0, -InParam.SpacingTextZeroOneX);
		FVector BottomLeftFrontCornerCurrentBox = TopLeftFrontCorner + MinorOffset;
		FVector TopRightBackCornerCurrentBox = BottomLeftFrontCornerCurrentBox 
			+ FVector(InputMMIAC->QubitCount * InParam.SpacingTextZeroOneX,
				-1.0 * InDerive.SizeMainStateBox.Y,
				2.0 * InParam.SpacingTextZeroOneX);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////
		FVector CurrentBoxBounds = FVector(
			(InputMMIAC->QubitCount + 1.0) * InParam.SpacingTextZeroOneX,
			InDerive.SizeMainStateBox.Y,
			2 * InParam.SpacingTextZeroOneX);
		FVector StartingPosition = BottomLeftFrontCornerCurrentBox
			+ FVector(0.25 * InParam.SpacingTextZeroOneX, InParam.OffsetTextZeroOneY, 0.5 * InParam.SpacingTextZeroOneX);
		FVector CurrentBoxLocation = (BottomLeftFrontCornerCurrentBox + TopRightBackCornerCurrentBox) / 2.0;
		OutQubitSplitDisplay.OpKetLabelBoxTransforms.Add(iterNewKets.Key,
			FTransform(FRotator(0.0, 0.0, 0.0), CurrentBoxLocation, CurrentBoxBounds));
		for (int32 CurrentQubit = 0; CurrentQubit < InputMMIAC->QubitCount; CurrentQubit++) {
			FVector CurrentPositionOneZero = StartingPosition + FVector(CurrentQubit * InParam.SpacingTextZeroOneX, 0.0, 0.0);
			OutQubitSplitDisplay.OpKetQubitLabelZeroOneTransforms.Add(FIntVector(iterNewKets.Key.X, iterNewKets.Key.Y, CurrentQubit),
				FTransform(FRotator(0.0, 0.0, 0.0), CurrentPositionOneZero, FVector(InParam.SpacingTextZeroOneX, 5.0, InParam.SpacingTextZeroOneX)));
		}
	}
}
void UQCDisplayBlueprintFxnLibrary::AddTransformsQubitSplit(
	TMap< EQubitSplitISMC, FVector>& MapSizesISMC,
	FQuantumQubitSplitDisplay& InQubitSplitDisplay,
	TMap <EQubitSplitISMC, UInstancedStaticMeshComponent*> MapQubitSplitISMC) {
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitOpKetLabelBox) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitOpKetLabelBox)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetLabelBox].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.OpKetLabelBoxTransforms) {
				MapQubitSplitISMC[EQubitSplitISMC::QubitSplitOpKetLabelBox]->AddInstance(
					FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
						iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetLabelBox]));
			}
		}
	}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse)
		&& MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse].GetMin() > 0.0
			&& MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.OpKetQubitLabelZeroOneTransforms) {
				uint32 LocalTestUint32 = iter.Key.Y;
				if ((LocalTestUint32 >> iter.Key.Z) % 2 == 0) {
					MapQubitSplitISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]->AddInstance(
						FTransform(FRotator(0.0, -90.0, 0.0), iter.Value.GetLocation(),
							FVector(
								(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
								(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
								(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z
							)));
				}
				else {
					MapQubitSplitISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue]->AddInstance(
						FTransform(FRotator(0.0, -90.0, 0.0), iter.Value.GetLocation(),
							FVector(
								(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
								(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
								(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z
							)));
				}
				
			}
		}
	}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitLabel) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitLabel)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitLabel].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.QubitSplitLabelTransforms) {
				MapQubitSplitISMC[EQubitSplitISMC::QubitSplitLabel]->AddInstance(
					FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
						iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitLabel]));
			}
		}
	}
	//if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParent) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParent)) {
	//	for (auto& iter : InQubitSplitDisplay.QubitSplitTunnelParentTransforms) {
	//		MapQubitSplitISMC[EQubitSplitISMC::QubitSplitTunnelParent]->AddInstance(
	//			FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
	//				iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParent]));
	//	}
	//}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentZeroFalse) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentZeroFalse)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentZeroFalse].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.QubitSplitTunnelZeroFalseParentTransforms) {
				MapQubitSplitISMC[EQubitSplitISMC::QubitSplitTunnelParentZeroFalse]->AddInstance(
					FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
						iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentZeroFalse]));
			}
		}
	}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentOneTrue) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentOneTrue)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentOneTrue].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.QubitSplitTunnelOneTrueParentTransforms) {
				MapQubitSplitISMC[EQubitSplitISMC::QubitSplitTunnelParentOneTrue]->AddInstance(
					FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
						iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentOneTrue]));
			}
		}
	}
}
void UQCDisplayBlueprintFxnLibrary::AddSpecificTransformsQubitSplit(
	TMap< EQubitSplitISMC, FVector>& MapSizesISMC,
	FQuantumQubitSplitDisplay& InQubitSplitDisplay,
	TMap <EQubitSplitISMC, UInstancedStaticMeshComponent*> MapQubitSplitISMC,
	TArray<FIntVector>& OpKetQubitLabelArray,
	TArray<FIntPoint>& TunnelQubitSplitCoordArray,
	TArray<int32>& QubitLineArray) {
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitOpKetLabelBox) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitOpKetLabelBox)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetLabelBox].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.OpKetLabelBoxTransforms) {
				MapQubitSplitISMC[EQubitSplitISMC::QubitSplitOpKetLabelBox]->AddInstance(
					FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
						iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetLabelBox]));
			}
		}
	}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse)
		&& MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse].GetMin() > 0.0
			&& MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.OpKetQubitLabelZeroOneTransforms) {
				if (OpKetQubitLabelArray.Contains(iter.Key)) {
					uint32 LocalTestUint32 = iter.Key.Y;
					if ((LocalTestUint32 >> iter.Key.Z) % 2 == 0) {
						MapQubitSplitISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]->AddInstance(
							FTransform(FRotator(0.0, -90.0, 0.0), iter.Value.GetLocation(),
								FVector(
									(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
									(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
									(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z
								)));
					}
					else {
						MapQubitSplitISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelOneTrue]->AddInstance(
							FTransform(FRotator(0.0, -90.0, 0.0), iter.Value.GetLocation(),
								FVector(
									(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
									(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z,
									(iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitOpKetQubitLabelZeroFalse]).Z
								)));
					}
				}
			}
		}
	}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitLabel) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitLabel)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitLabel].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.QubitSplitLabelTransforms) {
				if (TunnelQubitSplitCoordArray.Contains(iter.Key)) {
					MapQubitSplitISMC[EQubitSplitISMC::QubitSplitLabel]->AddInstance(
						FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
							iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitLabel]));
				}
			}
		}
	}
	//if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParent) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParent)) {
	//	for (auto& iter : InQubitSplitDisplay.QubitSplitTunnelParentTransforms) {
	//		MapQubitSplitISMC[EQubitSplitISMC::QubitSplitTunnelParent]->AddInstance(
	//			FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
	//				iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParent]));
	//	}
	//}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentZeroFalse) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentZeroFalse)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentZeroFalse].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.QubitSplitTunnelZeroFalseParentTransforms) {
				if (TunnelQubitSplitCoordArray.Contains(iter.Key)) {
					MapQubitSplitISMC[EQubitSplitISMC::QubitSplitTunnelParentZeroFalse]->AddInstance(
						FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
							iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentZeroFalse]));
				}
			}
		}
	}
	if (MapQubitSplitISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentOneTrue) && MapSizesISMC.Contains(EQubitSplitISMC::QubitSplitTunnelParentOneTrue)) {
		if (MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentOneTrue].GetMin() > 0.0) {
			for (auto& iter : InQubitSplitDisplay.QubitSplitTunnelOneTrueParentTransforms) {
				if (TunnelQubitSplitCoordArray.Contains(iter.Key)) {
					MapQubitSplitISMC[EQubitSplitISMC::QubitSplitTunnelParentOneTrue]->AddInstance(
						FTransform(iter.Value.GetRotation(), iter.Value.GetLocation(),
							iter.Value.GetScale3D() / MapSizesISMC[EQubitSplitISMC::QubitSplitTunnelParentOneTrue]));
				}
			}
		}
	}
}
void UQCDisplayBlueprintFxnLibrary::SetMeshesToISMC(
	TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualToISMC,
	TMap< EActualISMC, EMeshISMC>& MapActualToMesh,
	TMap< EMeshISMC, UStaticMesh*>& MapMeshToMeshObject) {
	for (auto& iterActual : MapActualToISMC) {
		if (MapActualToMesh.Contains(iterActual.Key)) {
			if (MapMeshToMeshObject.Contains(MapActualToMesh[iterActual.Key])) {
				MapActualToISMC[iterActual.Key]->SetStaticMesh(MapMeshToMeshObject[MapActualToMesh[iterActual.Key]]);
			}
		}
	}
}
void UQCDisplayBlueprintFxnLibrary::SetMaterialInterfacesToISMC(
	TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualToISMC,
	TMap< EActualISMC, EMaterialInterface>& MapActualToMaterialInterface,
	TMap< EMaterialInterface, UMaterialInterface*>& MapMaterialInterfaceToMaterialInterfaceObject) {
	for (auto& iterActual : MapActualToISMC) {
		if (MapActualToMaterialInterface.Contains(iterActual.Key)) {
			if (MapMaterialInterfaceToMaterialInterfaceObject.Contains(MapActualToMaterialInterface[iterActual.Key])) {
				MapActualToISMC[iterActual.Key]->SetMaterial(
					0, MapMaterialInterfaceToMaterialInterfaceObject[MapActualToMaterialInterface[iterActual.Key]]);
			}
		}
	}
}
void UQCDisplayBlueprintFxnLibrary::SetAllTransforms(
	TMap< FIntVector, FQuantumTransitionDisplay>& MapSubstateDisplayISMC,
	TMap< FIntPoint, FQuantumKetDisplay>& MapKetDisplayISMC,
	FQuantumQubitSplitDisplay& QubitSplitDisplayISMC,
	TMap< ETransitionISMC, EActualISMC>& MapTransitionActualISMC,
	TMap< EKetDisplayISMC, EActualISMC>& MapKetActualISMC,
	TMap< EQubitSplitISMC, EActualISMC>& MapQubitSplitActualISMC,
	TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualObjectISMC,
	TMap< EActualISMC, FVector>& MapActualSizeOfMeshISMC) {
	TMap <ETransitionISMC, UInstancedStaticMeshComponent*> LocalMapTransitionObjectISMC;
	TMap <ETransitionISMC, FVector> LocalMapransitionSizeISMC;
	for (auto& iter : MapTransitionActualISMC) {
		if (MapActualObjectISMC.Contains(iter.Value) && MapActualSizeOfMeshISMC.Contains((iter.Value))) {
			LocalMapTransitionObjectISMC.Add(iter.Key,MapActualObjectISMC[iter.Value]);
			LocalMapransitionSizeISMC.Add(iter.Key, MapActualSizeOfMeshISMC[iter.Value]);
		}
	}
	for (auto& iter : MapSubstateDisplayISMC) {
		AddTransformsTransition(
			LocalMapransitionSizeISMC, iter.Value, LocalMapTransitionObjectISMC);
	}
	TMap <EKetDisplayISMC, UInstancedStaticMeshComponent*> LocalMapKetObjectISMC;
	TMap <EKetDisplayISMC, FVector> LocalMapKetSizeISMC;
	for (auto& iter : MapKetActualISMC) {
		if (MapActualObjectISMC.Contains(iter.Value) && MapActualSizeOfMeshISMC.Contains((iter.Value))) {
			LocalMapKetObjectISMC.Add(iter.Key, MapActualObjectISMC[iter.Value]);
			LocalMapKetSizeISMC.Add(iter.Key, MapActualSizeOfMeshISMC[iter.Value]);
		}
	}
	for (auto& iter : MapKetDisplayISMC) {
		AddTransformsKetState(
			LocalMapKetSizeISMC, iter.Value, LocalMapKetObjectISMC);
	}
	TMap <EQubitSplitISMC, UInstancedStaticMeshComponent*> LocalMapQubitSplitObjectISMC;
	TMap <EQubitSplitISMC, FVector> LocalMapQubitSplitSizeISMC;
	for (auto& iter : MapQubitSplitActualISMC) {
		if (MapActualObjectISMC.Contains(iter.Value) && MapActualSizeOfMeshISMC.Contains((iter.Value))) {
			LocalMapQubitSplitObjectISMC.Add(iter.Key, MapActualObjectISMC[iter.Value]);
			LocalMapQubitSplitSizeISMC.Add(iter.Key, MapActualSizeOfMeshISMC[iter.Value]);
		}
	}
	AddTransformsQubitSplit(LocalMapQubitSplitSizeISMC, QubitSplitDisplayISMC, LocalMapQubitSplitObjectISMC);
}
void UQCDisplayBlueprintFxnLibrary::SetSpecificTransforms(
	TMap< FIntVector, FQuantumTransitionDisplay>& MapSubstateDisplayISMC,
	TMap< FIntPoint, FQuantumKetDisplay>& MapKetDisplayISMC,
	FQuantumQubitSplitDisplay& QubitSplitDisplayISMC,
	TMap< ETransitionISMC, EActualISMC>& MapTransitionActualISMC,
	TMap< EKetDisplayISMC, EActualISMC>& MapKetActualISMC,
	TMap< EQubitSplitISMC, EActualISMC>& MapQubitSplitActualISMC,
	TMap< EActualISMC, UInstancedStaticMeshComponent*>& MapActualObjectISMC,
	TMap< EActualISMC, FVector>& MapActualSizeOfMeshISMC,
	//TSet< ETransitionISMC>& SubsetTransitionTargetedArray,
	//TSet< EKetDisplayISMC>& SubsetKetDisplayTargetedArray,
	//TSet< EQubitSplitISMC>& SubsetQubitSplitTargetedArray,
	TArray<int32>& QubitListArray,
	TArray<FIntPoint>& QubitSplitCoordArray,
	TArray<FIntPoint>& OpKetCoordArray,
	TArray<FIntVector>& OpKetQubitCoordArray,
	TArray<FIntVector>& OpKetFromKetToCoordArray,
	float InputGrowthFactor) {
	for (auto& iter : MapActualObjectISMC) {
		iter.Value->ClearInstances();
	}
	TMap <ETransitionISMC, UInstancedStaticMeshComponent*> LocalMapTransitionObjectISMC;
	TMap <ETransitionISMC, FVector> LocalMapransitionSizeISMC;
	for (auto& iter : MapTransitionActualISMC) {
		if (MapActualObjectISMC.Contains(iter.Value) && MapActualSizeOfMeshISMC.Contains((iter.Value))) {
			LocalMapTransitionObjectISMC.Add(iter.Key, MapActualObjectISMC[iter.Value]);
			LocalMapransitionSizeISMC.Add(iter.Key, MapActualSizeOfMeshISMC[iter.Value]);
		}
	}
	TMap<ETransitionISMC, FVector> AdjustedMapTransitionSizeISMC;
	for (auto& iter : LocalMapransitionSizeISMC) {
		AdjustedMapTransitionSizeISMC.Add(iter.Key, (1.0 / InputGrowthFactor) * iter.Value);
	}
	for (auto& iter : MapSubstateDisplayISMC) {
		if (OpKetFromKetToCoordArray.Contains(iter.Key)) {
			AddTransformsTransition(
				AdjustedMapTransitionSizeISMC, MapSubstateDisplayISMC[iter.Key], LocalMapTransitionObjectISMC);
		}
	}
	TMap <EKetDisplayISMC, UInstancedStaticMeshComponent*> LocalMapKetObjectISMC;
	TMap <EKetDisplayISMC, FVector> LocalMapKetSizeISMC;
	for (auto& iter : MapKetActualISMC) {
		if (MapActualObjectISMC.Contains(iter.Value) && MapActualSizeOfMeshISMC.Contains((iter.Value))) {
			LocalMapKetObjectISMC.Add(iter.Key, MapActualObjectISMC[iter.Value]);
			LocalMapKetSizeISMC.Add(iter.Key, MapActualSizeOfMeshISMC[iter.Value]);
		}
	}
	TMap<EKetDisplayISMC, FVector> AdjustedMapKetSizeISMC;
	for (auto& iter : LocalMapKetSizeISMC) {
		AdjustedMapKetSizeISMC.Add(iter.Key, (1.0 / InputGrowthFactor) * iter.Value);
	}
	for (auto& iter : MapKetDisplayISMC) {
		if (OpKetCoordArray.Contains(iter.Key)) {
			AddTransformsKetState(
				AdjustedMapKetSizeISMC, MapKetDisplayISMC[iter.Key], LocalMapKetObjectISMC);
		}
	}
	TMap <EQubitSplitISMC, UInstancedStaticMeshComponent*> LocalMapQubitSplitObjectISMC;
	TMap <EQubitSplitISMC, FVector> LocalMapQubitSplitSizeISMC;
	for (auto& iter : MapQubitSplitActualISMC) {
		if (MapActualObjectISMC.Contains(iter.Value) && MapActualSizeOfMeshISMC.Contains((iter.Value))) {
			LocalMapQubitSplitObjectISMC.Add(iter.Key, MapActualObjectISMC[iter.Value]);
			LocalMapQubitSplitSizeISMC.Add(iter.Key, MapActualSizeOfMeshISMC[iter.Value]);
		}
	}
	TMap<EQubitSplitISMC,FVector> AdjustedMapQubitSplitSizeISMC;
	for (auto& iter : LocalMapQubitSplitSizeISMC) {
		AdjustedMapQubitSplitSizeISMC.Add(iter.Key, (1.0 / InputGrowthFactor) * iter.Value);
	}
	AddSpecificTransformsQubitSplit(
		AdjustedMapQubitSplitSizeISMC,
		QubitSplitDisplayISMC,
		LocalMapQubitSplitObjectISMC,
		OpKetQubitCoordArray,
		QubitSplitCoordArray,
		QubitListArray);
}