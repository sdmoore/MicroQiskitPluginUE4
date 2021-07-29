// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "LatexTextureFetchObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUBITLAND_API ULatexTextureFetchObject : public UObject
{
	GENERATED_BODY()
public:
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
		void HttpInitialize();
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
};
