// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "LaTeXCodeCogsActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUBITLAND_API ULaTeXCodeCogsActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULaTeXCodeCogsActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FHttpModule* Http;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int32 Width;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int32 Height;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FSlateBrush> OperatorEquationBrushMap;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FString, UTexture2D*> EquationStringToTextureMap;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FString, FIntPoint> EquationStringToWidthHeightMap;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FString, FString> EquationStringToContentTypeMap;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FString, int32> EquationStringToContentSizeMap;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FIntVector, FSlateBrush> KetEquationBrushMap;
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TMap<FString, UTexture2D*> KetEquationTextureMap;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) TSet<FString> EquationStringPending;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int32 FileSize;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) FString ContentType;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) bool HtmlRequestCompleteFlag;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) bool DatabaseMapUpdated;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) UTexture2D* LoadedT2D;
	/* The actual HTTP call */
	UFUNCTION(BlueprintCallable)
		void HttpCall(
			UPARAM() FString UrlBase,
			UPARAM() FString HttpQuery,
			bool& AlreadyPresentFlag,
			bool& RequestAlreadyPendingFlag);
	UFUNCTION(BlueprintCallable)
		void BasicHttpCall(
			UPARAM() FString UrlBase,
			UPARAM() FString HttpQuery,
			FString& FinalHttpQuery);
	UFUNCTION(BlueprintCallable)
		void UpdateGameInstanceSave(
			UPARAM(ref) TMap<FString, UTexture2D*>& TargetUpdateStringToTextureMap,
			UPARAM(ref) TMap<FString, FIntPoint>& TargetUpdateStringToWidthHeightMap,
			bool& IdenticalStringKeysTexture2D,
			bool& IdenticalStringKeysWidthHeightMap);
	UFUNCTION(BlueprintCallable)
		void LoadFromGameInstanceSave(
			UPARAM(ref) TMap<FString, UTexture2D*>& TargetUpdateStringToTextureMap,
			UPARAM(ref) TMap<FString, FIntPoint>& TargetUpdateStringToWidthHeightMap);
	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void BasicOnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	//TSet<FString> GetStringSetFromStringArray(TArray<FString>& InputStringArray);
	//TSet<FString> GetStringSetFromMapTexture2D(TMap<FString, UTexture2D*>& InputMap);
	//TSet<FString> GetStringSetFromMapFIntPoint(TMap<FString, FIntPoint>& InputMap);
	//UFUNCTION(BlueprintCallable)
	//	void UpdateGame();
	UFUNCTION(BlueprintCallable)
		void FxnGetDyadicOfIntVector(
			UPARAM() FIntVector InputIntVector,
			int32& OutputNumeratorReal,
			bool& OutputRationalRealFlag,
			int32& OutputNumeratorImaginary,
			bool& OutputRationalImaginaryFlag,
			int32& PowerOfTwoDenominator,
			bool& ValidMagnitude);
	UFUNCTION(BlueprintCallable)
		void FxnGetIntVectorOfDyadic(
			UPARAM() int32 InputNumeratorReal,
			UPARAM() bool InputRationalRealFlag,
			UPARAM() int32 InputNumeratorImaginary,
			UPARAM() bool InputRationalImaginaryFlag,
			UPARAM() int32 PowerOfTwoDenominator,
			bool& ValidMagnitude,
			FIntVector& OutputIntVector);
	UFUNCTION(BlueprintCallable)
		void GetMapIntVectorString(
			UPARAM() int32 InputQubitUpTo,
			TMap<FIntVector, FString>& OutputMap);
	UFUNCTION(BlueprintCallable)
		void GetMapIntVectorStringSpecified(
			UPARAM() int32 InputQubitUpTo, 
			UPARAM() FString InputDPI,
			UPARAM() FString InputSize,
			UPARAM() FString InputColor,
			TMap<FIntVector, FString>& OutputMap);
	UFUNCTION(BlueprintCallable)
		void GetMapIntVectorStringImproved(
			UPARAM() int32 InputQubitUpTo,
			TMap<FIntVector, FString>& OutputMap);
	UFUNCTION(BlueprintCallable)
		void GetMapIntVectorStringImprovedSpecified(
			UPARAM() int32 InputQubitUpTo,
			UPARAM() FString InputDPI,
			UPARAM() FString InputSize,
			UPARAM() FString InputColor,
			TMap<FIntVector, FString>& OutputMap);
	FString GetDyadicToString(
		int32 NumeratorReal,
		bool RationalRealFlag,
		int32 NumeratorImaginary,
		bool RationalImaginaryFlag,
		int32 PowerOfTwoDenominator);
	FString GetDyadicToStringSingle(
		int32 Numerator,
		bool RationalFlag,
		bool RealFlag,
		int32 PowerOfTwoDenominator);
	FString GetDyadicToStringSpecifiedOptions(
		int32 NumeratorReal,
		bool RationalRealFlag,
		int32 NumeratorImaginary,
		bool RationalImaginaryFlag,
		int32 PowerOfTwoDenominator,
		FString InputDPI,
		FString InputSize,
		FString InputColor);
	FString GetDyadicToStringComplexSpecifiedOptions(
		int32 NumeratorReal,
		bool RationalRealFlag,
		int32 NumeratorImaginary,
		bool RationalImaginaryFlag,
		int32 PowerOfTwoDenominator,
		FString InputDPI,
		FString InputSize,
		FString InputColor);
	FIntVector GetIntVectorOfDyadic(
		int32 NumeratorReal,
		bool InputRationalRealFlag,
		int32 NumeratorImaginary,
		bool InputRationalImaginaryFlag,
		int32 PowerOfTwoDenominator);
};
