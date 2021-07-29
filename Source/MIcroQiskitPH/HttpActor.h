//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "HttpActor.generated.h"
//
//UCLASS()
//class MICROQISKITPH_API AHttpActor : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AHttpActor();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "HttpActor.generated.h"

UCLASS()
class MICROQISKITPH_API AHttpActor : public AActor
{
	GENERATED_BODY()

public:
	FHttpModule* Http;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int32 FileSize;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) FString ContentType;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) bool IsLoaded;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) bool WasAccessed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) UTexture2D* LoadedT2D;
	/* The actual HTTP call */
	//UFUNCTION()
	//	void MyHttpCall();
	//UFUNCTION(BlueprintCallable)
	//	void MyHttpCall();
	//IImageWrapperModule& ImageWrapperModule; // = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	//TSharedPtr<IImageWrapper> ImageWrapper; // = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	UFUNCTION(BlueprintCallable)
		void MyHttpCall(
			UPARAM() FString UrlInput);
	//UFUNCTION(BlueprintCallable)
	//	void MyHttpCall(
	//		int32 OutputFileSize,
	//		FString OutputContentType);

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Sets default values for this actor's properties
	AHttpActor(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};