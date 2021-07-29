// Fill out your copyright notice in the Description page of Project Settings.


#include "LaTeXCodeCogsActorComponent.h"

// Sets default values for this component's properties
ULaTeXCodeCogsActorComponent::ULaTeXCodeCogsActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Http = &FHttpModule::Get();
	DatabaseMapUpdated = true;
	// ...
}


// Called when the game starts
void ULaTeXCodeCogsActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULaTeXCodeCogsActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

//
//// Sets default values
//AHttpActor::AHttpActor(const class FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	//When the object is constructed, Get the HTTP module
//	
//
//}
//
//// Called when the game starts or when spawned
//void AHttpActor::BeginPlay()
//{
//	////MyHttpCall();
//	Super::BeginPlay();
//}
//
///*Http call*/
//void ULaTeXCodeCogsActorComponent::HttpCall(FString UrlInput)
//{
//	HtmlRequestCompleteFlag = false;
//	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
//	Request->OnProcessRequestComplete().BindUObject(this, &ULaTeXCodeCogsActorComponent::OnResponseReceived);
//	//This is the url on which to process the request
//	Request->SetURL(UrlInput);
//	Request->SetVerb("GET");
//	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
//	//Request->SetHeader("Content-Type", TEXT("application/json"));
//	Request->ProcessRequest();
//}
//
///*Assigned function on successfull http call*/
//void ULaTeXCodeCogsActorComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
//{
//	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
//	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
//	TArray<uint8> ImageData = Response->GetContent();
//	//Create T2D!
//	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
//	{
//		//const TArray<uint8>* UncompressedBGRA = NULL;
//		TArray<uint8> UncompressedBGRA;
//		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
//		{
//			LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
//
//			////Valid?
//			//if (!LoadedT2D) return NULL;
//			////~~~~~~~~~~~~~~
//
//			//Out!
//			Width = ImageWrapper->GetWidth();
//			Height = ImageWrapper->GetHeight();
//
//			//Copy!
//			void* TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
//			FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
//			LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();
//
//			//Update!
//			LoadedT2D->UpdateResource();
//			HtmlRequestCompleteFlag = true;
//		}
//	}
//	FileSize = Response->GetContentLength();
//	ContentType = Response->GetContentType();
//
//	//ContentType = Response->GetContent();
//	//Deserialize the json data given Reader and the actual object to deserialize
//	//if (FJsonSerializer::Deserialize(Reader, JsonObject,0))
//	//{
//	//	//Get the value of the json object by field name
//	//	int32 recievedInt = JsonObject->GetIntegerField("customInt");
//
//	//	//Output it to the engine
//	//	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
//	//}
//}
//TSet<FString> ULaTeXCodeCogsActorComponent::GetStringSetFromStringArray(TArray<FString>& InputStringArray) {
//	TSet<FString> OutputSet;
//	for (auto& iter : InputStringArray) {
//		OutputSet.Add(iter);
//	}
//	return OutputSet;
//}
//TSet<FString> ULaTeXCodeCogsActorComponent::GetStringSetFromMapTexture2D(TMap<FString, UTexture2D*>& InputMap) {
//	TSet<FString> OutputSet;
//	TArray<FString> NewStringArray;
//	InputMap.GetKeys(NewStringArray);
//	for (auto& iter : NewStringArray) {
//		OutputSet.Add(iter);
//	}
//	return OutputSet;
//}
//TSet<FString> ULaTeXCodeCogsActorComponent::GetStringSetFromMapFIntPoint(TMap<FString, FIntPoint>& InputMap) {
//	TSet<FString> OutputSet;
//	TArray<FString> NewStringArray;
//	InputMap.GetKeys(NewStringArray);
//	for (auto& iter : NewStringArray) {
//		OutputSet.Add(iter);
//	}
//	return OutputSet;
//}
void ULaTeXCodeCogsActorComponent::LoadFromGameInstanceSave(
	TMap<FString, UTexture2D*>& TargetUpdateStringToTextureMap,
	TMap<FString, FIntPoint>& TargetUpdateStringToWidthHeightMap) {
	for (auto& iter : TargetUpdateStringToTextureMap) {
		if (!EquationStringToTextureMap.Contains(iter.Key)) {
			EquationStringToTextureMap.Add(iter.Key, iter.Value);
		}
	}
	for (auto& iter : TargetUpdateStringToWidthHeightMap) {
		if (!EquationStringToWidthHeightMap.Contains(iter.Key)) {
			EquationStringToWidthHeightMap.Add(iter.Key, iter.Value);
		}
	}
}
void ULaTeXCodeCogsActorComponent::UpdateGameInstanceSave(
	TMap<FString, UTexture2D*>& TargetUpdateStringToTextureMap,
	TMap<FString, FIntPoint>& TargetUpdateStringToWidthHeightMap,
	bool& IdenticalStringKeysTexture2D,
	bool& IdenticalStringKeysWidthHeightMap) {
	if (EquationStringPending.Num() == 0 && !DatabaseMapUpdated) {
		for (auto& iter : EquationStringToTextureMap) {
			if (!TargetUpdateStringToTextureMap.Contains(iter.Key)) {
				TargetUpdateStringToTextureMap.Add(iter.Key, iter.Value);
			}
		}
		for (auto& iter : EquationStringToWidthHeightMap) {
			if (!TargetUpdateStringToWidthHeightMap.Contains(iter.Key)) {
				TargetUpdateStringToWidthHeightMap.Add(iter.Key, iter.Value);
			}
		}
		//// Latex image as Texture2D
		//// Update Latex FString to Texture2D
		//TSet<FString> SetKeysTargetTextureMap = 
		//	GetStringSetFromMapTexture2D(TargetUpdateStringToTextureMap);
		//TSet<FString> SetKeysSourceTextureMap = 
		//	GetStringSetFromMapTexture2D(EquationStringToTextureMap);
		//TSet<FString> ToUpdateKeysTextureMap = SetKeysSourceTextureMap.Difference(SetKeysTargetTextureMap);
		//for (auto& iter : ToUpdateKeysTextureMap) {
		//	TargetUpdateStringToTextureMap.Add(iter, EquationStringToTextureMap[iter]);
		//}
		////// Test that maps have identical key sets
		////TSet<FString> UpdatedTargetStringSetTextureMap =
		////	GetStringSetFromMapTexture2D(TargetUpdateStringToTextureMap);
		////TSet<FString> NewToUpdateKeysTextureMap = SetKeysSourceTextureMap.Difference(UpdatedTargetStringSetTextureMap);
		////IdenticalStringKeysTexture2D = (NewToUpdateKeysTextureMap.Num() == 0);
		//// Latex image width and height as FIntPoint
		//// Update Latex FString to FIntPoint
		//TSet<FString> SetKeysTargetWidthHeightMap = 
		//	GetStringSetFromMapFIntPoint(TargetUpdateStringToWidthHeightMap);
		//TSet<FString> SetKeysSourceWidthHeightMap = 
		//	GetStringSetFromMapFIntPoint(EquationStringToWidthHeightMap);
		//TSet<FString> ToUpdateKeysWidthHeight = SetKeysSourceWidthHeightMap.Difference(SetKeysTargetWidthHeightMap);
		//for (auto& iter : ToUpdateKeysWidthHeightMap) {
		//	TargetUpdateStringToWidthHeightMap.Add(iter, EquationStringToWidthHeightMap[iter]);
		//}
		//// Test that maps have identical key sets
		//TSet<FString> UpdatedTargetStringSetWidthHeightMap = 
		//	GetStringSetFromMapFIntPoint(TargetUpdateStringToWidthHeightMap);
		//TSet<FString> NewToUpdateKeysWidthHeight = SetKeysSourceWidthHeightMap.Difference(UpdatedTargetStringSetWidthHeightMap);
		//IdenticalStringKeysWidthHeightMap = (NewToUpdateKeysWidthHeight.Num() == 0);
		//// Set flag that the update function has run
		IdenticalStringKeysTexture2D = false;
		IdenticalStringKeysWidthHeightMap = false;
		DatabaseMapUpdated = true;
	}
	// ...
}
/*Http call*/
void ULaTeXCodeCogsActorComponent::HttpCall(
	FString UrlBase, 
	FString HttpQuery, 
	bool& AlreadyPresentFlag, 
	bool& RequestAlreadyPendingFlag) {
	//if (EquationStringToTextureMap.Contains(HttpQuery)) {
	//	int32 LocalSizeX = (**EquationStringToTextureMap.Find(HttpQuery)).GetSizeX();
	//	int32 LocalSizeY = (**EquationStringToTextureMap.Find(HttpQuery)).GetSizeY();
	//	//UTexture2D** RefTextureLocal = EquationStringToTextureMap.Find(HttpQuery);
	//	//UTexture2D** RefTextureLocal = EquationStringToTextureMap.Find;
	//	//if (!(**RefTextureLocal.GetSizeX() >= 1 &&
	//	//	**RefTextureLocal.GetSizeY() >= 1)) {
	//	if (!(LocalSizeX >= 1 &&
	//		LocalSizeY >= 1)) {
	//		EquationStringToTextureMap.Remove(HttpQuery);
	//	}
	//}
	if (!EquationStringToTextureMap.Contains(HttpQuery)){
		DatabaseMapUpdated = false;
		if (!EquationStringPending.Contains(HttpQuery)) {
			AlreadyPresentFlag = false;
			RequestAlreadyPendingFlag = false;
			HtmlRequestCompleteFlag = false;
			TSharedRef<IHttpRequest> Request = Http->CreateRequest();
			Request->OnProcessRequestComplete().BindUObject(this, &ULaTeXCodeCogsActorComponent::OnResponseReceived);
			FString UrlRequest;
			UrlRequest.Append(UrlBase);
			UrlRequest.Append(HttpQuery);
			//This is the url on which to process the request
			Request->SetURL(UrlRequest);
			Request->SetVerb("GET");
			Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
			const FString& ConstRefHttpQuery = HttpQuery;
			Request->SetHeader(TEXT("Http-Query"), ConstRefHttpQuery);
			//Request->SetHeader("Content-Type", TEXT("application/json"));
			EquationStringPending.Add(HttpQuery);
			Request->ProcessRequest();
		}
	}
	else {
		AlreadyPresentFlag = true;
		RequestAlreadyPendingFlag = false;
	}
}
/*Basic Http call*/
void ULaTeXCodeCogsActorComponent::BasicHttpCall(
	FString UrlBase, 
	FString HttpQuery,
	FString& FinalHttpQuery) {
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ULaTeXCodeCogsActorComponent::BasicOnResponseReceived);
	FString UrlRequest;
	UrlRequest.Append(UrlBase);
	UrlRequest.Append(HttpQuery);
	//This is the url on which to process the request
	Request->SetURL(UrlRequest);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	const FString& ConstRefHttpQuery = HttpQuery;
	Request->SetHeader(TEXT("Http-Query"), ConstRefHttpQuery);
	//Request->SetHeader("Content-Type", TEXT("application/json"));
	FinalHttpQuery = ConstRefHttpQuery;
	TCHAR BackslashChar = '\\';
	FString Substring0 = FString();
	Substring0 += BackslashChar;
	Substring0 += BackslashChar;
	FString Substring1 = FString();
	Substring1 += BackslashChar;
	FString HttpQueryToAdd = HttpQuery.Replace(*Substring0, *Substring1); //RequestStringURL.RightChop(QuestionMarkPosition + 1);
	EquationStringPending.Add(HttpQueryToAdd);
	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void ULaTeXCodeCogsActorComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	TArray<uint8> ImageData = Response->GetContent();
	TArray < FString > AllHeadersArray = Response->GetAllHeaders();
	FString RequestStringURL = Response->GetURL();
	int32 QuestionMarkPosition;
	RequestStringURL.FindChar('?', QuestionMarkPosition);
	FString HttpQuery = RequestStringURL.RightChop(QuestionMarkPosition + 1);
	//FString HttpQuery = Response->GetHeader(TEXT("Http-Query"));
	//Create T2D!
	if (ImageWrapper.IsValid() &&
		ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()) &&
		EquationStringPending.Contains(HttpQuery) &&
		!EquationStringToTextureMap.Contains(HttpQuery))
	{
		//const TArray<uint8>* UncompressedBGRA = NULL;
		TArray<uint8> UncompressedBGRA;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			//LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
			EquationStringToTextureMap.Add(HttpQuery, UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8));

			////Valid?
			//if (!LoadedT2D) return NULL;
			////~~~~~~~~~~~~~~

			//Out!
			//Width = ImageWrapper->GetWidth();
			//Height = ImageWrapper->GetHeight();
			EquationStringToWidthHeightMap.Add(HttpQuery, FIntPoint(ImageWrapper->GetWidth(), ImageWrapper->GetHeight()));
			EquationStringToWidthHeightMap.Add(HttpQuery, FIntPoint(ImageWrapper->GetWidth(), ImageWrapper->GetHeight()));

			//Copy!
			void* TextureData = EquationStringToTextureMap[HttpQuery]->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
			EquationStringToTextureMap[HttpQuery]->PlatformData->Mips[0].BulkData.Unlock();

			//Update!
			EquationStringPending.Remove(HttpQuery);
			EquationStringToTextureMap[HttpQuery]->UpdateResource();
			EquationStringToContentSizeMap.Add(HttpQuery, Response->GetContentLength());
			EquationStringToContentTypeMap.Add(HttpQuery, Response->GetContentType());
			if (EquationStringPending.Num() == 0) {
				DatabaseMapUpdated = true;
			}
			HtmlRequestCompleteFlag = true;
		}
	}
	//FileSize = Response->GetContentLength();
	//ContentType = Response->GetContentType();

	//ContentType = Response->GetContent();
	//Deserialize the json data given Reader and the actual object to deserialize
	//if (FJsonSerializer::Deserialize(Reader, JsonObject,0))
	//{
	//	//Get the value of the json object by field name
	//	int32 recievedInt = JsonObject->GetIntegerField("customInt");

	//	//Output it to the engine
	//	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	//}
}


/*Assigned function on successfull http call*/
void ULaTeXCodeCogsActorComponent::BasicOnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	TArray<uint8> ImageData = Response->GetContent();
	TArray < FString > AllHeadersArray = Response->GetAllHeaders();
	FString RequestStringURL = Response->GetURL();
	int32 QuestionMarkPosition;
	RequestStringURL.FindChar('?', QuestionMarkPosition);
	//const TCHAR* Substring0 = "\\\\";
	//const TCHAR* Substring1 = "\\";
	FString Temp = RequestStringURL.RightChop(QuestionMarkPosition + 1);
	FString Substring0 = "\\\\";
	FString Substring1 = "\\";
	FString HttpQuery = Temp.Replace(*Substring0, *Substring1); //RequestStringURL.RightChop(QuestionMarkPosition + 1);
	//FString HttpQuery = Response->GetHeader(TEXT("Http-Query"));
	//Create T2D!
	if (ImageWrapper.IsValid() &&
		ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))/* &&
		EquationStringPending.Contains(HttpQuery) &&
		!EquationStringToTextureMap.Contains(HttpQuery))*/
	{
		//const TArray<uint8>* UncompressedBGRA = NULL;
		TArray<uint8> UncompressedBGRA;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			//LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
			EquationStringToTextureMap.Add(HttpQuery, UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8));

			////Valid?
			//if (!LoadedT2D) return NULL;
			////~~~~~~~~~~~~~~
			//TArray<uint8> FunkyUncompressed;
			//for (int32 LocalIndex = 0; LocalIndex < UncompressedBGRA.Num(); LocalIndex++) {
			//	if (LocalIndex % 4 == 0) {
			//		FunkyUncompressed.Add(UncompressedBGRA[LocalIndex + 3]);
			//		FunkyUncompressed.Add(UncompressedBGRA[LocalIndex + 3]);
			//		FunkyUncompressed.Add(UncompressedBGRA[LocalIndex + 3]);
			//		FunkyUncompressed.Add(UncompressedBGRA[LocalIndex + 3]);
			//	}
			//}
			//Out!
			//Width = ImageWrapper->GetWidth();
			//Height = ImageWrapper->GetHeight();
			//EquationStringToWidthHeightMap.Add(HttpQuery, FIntPoint(ImageWrapper->GetWidth(), ImageWrapper->GetHeight()));
			EquationStringToWidthHeightMap.Add(HttpQuery, FIntPoint(ImageWrapper->GetWidth(), ImageWrapper->GetHeight()));

			//Copy!
			void* TextureData = EquationStringToTextureMap[HttpQuery]->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
			//FMemory::Memcpy(TextureData, FunkyUncompressed.GetData(), FunkyUncompressed.Num());
			EquationStringToTextureMap[HttpQuery]->PlatformData->Mips[0].BulkData.Unlock();

			//Update!
			//EquationStringPending.Remove(HttpQuery);
			EquationStringToTextureMap[HttpQuery]->UpdateResource();
			EquationStringToContentSizeMap.Add(HttpQuery, Response->GetContentLength());
			EquationStringToContentTypeMap.Add(HttpQuery, Response->GetContentType());
			//if (EquationStringPending.Num() == 0) {
			//	DatabaseMapUpdated = true;
			//}
			//HtmlRequestCompleteFlag = true;
		}
	}
	//FileSize = Response->GetContentLength();
	//ContentType = Response->GetContentType();

	//ContentType = Response->GetContent();
	//Deserialize the json data given Reader and the actual object to deserialize
	//if (FJsonSerializer::Deserialize(Reader, JsonObject,0))
	//{
	//	//Get the value of the json object by field name
	//	int32 recievedInt = JsonObject->GetIntegerField("customInt");

	//	//Output it to the engine
	//	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	//}
}

void ULaTeXCodeCogsActorComponent::GetMapIntVectorString(
	int32 InputQubitUpTo,
	TMap<FIntVector, FString>& OutputMap) {
	OutputMap.Empty();
	TArray<FIntVector> KeyArray;
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, 0, true, 0),
		GetDyadicToString(
			0, true, 0, true, 0));
	OutputMap.Add(GetIntVectorOfDyadic(
		1, true, 0, true, 0),
		GetDyadicToString(
			1, true, 0, true, 0));
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, 1, true, 0),
		GetDyadicToString(
			0, true, 1, true, 0));
	OutputMap.Add(GetIntVectorOfDyadic(
		-1, true, 0, true, 0),
		GetDyadicToString(
			-1, true, 0, true, 0));
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, -1, true, 0),
		GetDyadicToString(
			0, true, -1, true, 0));
	for (int32 QubitIndex = 0; QubitIndex < InputQubitUpTo; QubitIndex++) {
		int32 KetCount = FMath::RoundToInt(FMath::Pow(2.0,QubitIndex));
		for (int32 IndexBase = -KetCount; IndexBase <= KetCount; IndexBase++) {
			OutputMap.Add(GetIntVectorOfDyadic(
				IndexBase, false, 0, true, QubitIndex),
				GetDyadicToString(
					IndexBase, false, 0, true, QubitIndex));
			OutputMap.Add(GetIntVectorOfDyadic(
				IndexBase, true, 0, true, QubitIndex),
				GetDyadicToString(
					IndexBase, true, 0, true, QubitIndex));
			OutputMap.Add(GetIntVectorOfDyadic(
				0, true, IndexBase, false, QubitIndex),
				GetDyadicToString(
					0, true, IndexBase, false, QubitIndex));
			OutputMap.Add(GetIntVectorOfDyadic(
				0, true, IndexBase, true, QubitIndex),
				GetDyadicToString(
					0, true, IndexBase, true, QubitIndex));
			for (int32 IndexExtra = 0; IndexExtra < KetCount; IndexExtra++) {
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, false, IndexExtra, false, QubitIndex),
					GetDyadicToString(
						IndexBase, false, IndexExtra, false, QubitIndex));
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, true, IndexExtra, false, QubitIndex),
					GetDyadicToString(
						IndexBase, true, IndexExtra, false, QubitIndex));
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, false, IndexExtra, true, QubitIndex),
					GetDyadicToString(
						IndexBase, false, IndexExtra, true, QubitIndex));
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, true, IndexExtra, true, QubitIndex),
					GetDyadicToString(
						IndexBase, true, IndexExtra, true, QubitIndex));
			}
		}
	}
}
void ULaTeXCodeCogsActorComponent::GetMapIntVectorStringImproved(
	int32 InputQubitUpTo,
	TMap<FIntVector, FString>& OutputMap) {
	OutputMap.Empty();
	//TArray<FIntVector> KeyArray;
	//OutputMap.Add(GetIntVectorOfDyadic(
	//	0, true, 0, true, 0),
	//	GetDyadicToString(
	//		0, true, 0, true, 0));
	//OutputMap.Add(GetIntVectorOfDyadic(
	//	1, true, 0, true, 0),
	//	GetDyadicToString(
	//		1, true, 0, true, 0));
	//OutputMap.Add(GetIntVectorOfDyadic(
	//	0, true, 1, true, 0),
	//	GetDyadicToString(
	//		0, true, 1, true, 0));
	//OutputMap.Add(GetIntVectorOfDyadic(
	//	-1, true, 0, true, 0),
	//	GetDyadicToString(
	//		-1, true, 0, true, 0));
	//OutputMap.Add(GetIntVectorOfDyadic(
	//	0, true, -1, true, 0),
	//	GetDyadicToString(
	//		0, true, -1, true, 0));
	//for (int32 QubitIndex = 1; QubitIndex < InputQubitUpTo; QubitIndex++) {
	//	int32 KetCount = FMath::RoundToInt(FMath::Pow(2.0,QubitIndex));
	//	for (int32 IndexBase = -KetCount; IndexBase <= KetCount; IndexBase++) {
	//		if (2 * IndexBase * IndexBase < KetCount * KetCount) {
	//			OutputMap.Add(GetIntVectorOfDyadic(
	//				IndexBase, false, 0, true, QubitIndex),
	//				GetDyadicToString(
	//					IndexBase, false, 0, true, QubitIndex));
	//			OutputMap.Add(GetIntVectorOfDyadic(
	//				0, true, IndexBase, false, QubitIndex),
	//				GetDyadicToString(
	//					0, true, IndexBase, false, QubitIndex));
	//		}
	//		if (IndexBase * IndexBase < KetCount * KetCount) {
	//			OutputMap.Add(GetIntVectorOfDyadic(
	//				IndexBase, true, 0, true, QubitIndex),
	//				GetDyadicToString(
	//					IndexBase, true, 0, true, QubitIndex));
	//			OutputMap.Add(GetIntVectorOfDyadic(
	//				0, true, IndexBase, true, QubitIndex),
	//				GetDyadicToString(
	//					0, true, IndexBase, true, QubitIndex));
	//		}
	//		for (int32 IndexExtra = 0; IndexExtra < KetCount; IndexExtra++) {
	//			if(not)
	//			if (2 * IndexBase * IndexBase + 2 * IndexExtra * IndexExtra <= KetCount * KetCount) {
	//				OutputMap.Add(GetIntVectorOfDyadic(
	//					IndexBase, false, IndexExtra, false, QubitIndex),
	//					GetDyadicToString(
	//						IndexBase, false, IndexExtra, false, QubitIndex));
	//			}
	//			if (IndexBase * IndexBase + 2 * IndexExtra * IndexExtra <= KetCount * KetCount) {
	//				OutputMap.Add(GetIntVectorOfDyadic(
	//					IndexBase, true, IndexExtra, false, QubitIndex),
	//					GetDyadicToString(
	//						IndexBase, true, IndexExtra, false, QubitIndex));
	//			}
	//			if (2 * IndexBase * IndexBase + IndexExtra * IndexExtra <= KetCount * KetCount) {
	//				OutputMap.Add(GetIntVectorOfDyadic(
	//					IndexBase, false, IndexExtra, true, QubitIndex),
	//					GetDyadicToString(
	//						IndexBase, false, IndexExtra, true, QubitIndex));
	//			}
	//			if (IndexBase * IndexBase + IndexExtra * IndexExtra <= KetCount * KetCount) {
	//				OutputMap.Add(GetIntVectorOfDyadic(
	//					IndexBase, false, IndexExtra, true, QubitIndex),
	//					GetDyadicToString(
	//						IndexBase, false, IndexExtra, true, QubitIndex));
	//			}
	//		}
	//	}
	//}
	GetMapIntVectorStringImprovedSpecified(InputQubitUpTo, "300", "", "White", OutputMap);
}
void ULaTeXCodeCogsActorComponent::GetMapIntVectorStringImprovedSpecified(
	int32 InputQubitUpTo,
	FString InputDPI,
	FString InputSize,
	FString InputColor,
	TMap<FIntVector, FString>& OutputMap) {
	OutputMap.Empty();
	TArray<FIntVector> KeyArray;
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, 0, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			0, true, 0, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		1, true, 0, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			1, true, 0, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, 1, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			0, true, 1, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		-1, true, 0, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			-1, true, 0, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, -1, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			0, true, -1, true, 0, InputDPI, InputSize, InputColor));
	for (int32 QubitIndex = 1; QubitIndex < InputQubitUpTo; QubitIndex++) {
		int32 KetCount = FMath::RoundToInt(FMath::Pow(2.0,QubitIndex));
		for (int32 IndexBase = -KetCount; IndexBase <= KetCount; IndexBase++) {
			if (IndexBase!=0) {
				if (2 * IndexBase * IndexBase < KetCount * KetCount) {
					OutputMap.Add(GetIntVectorOfDyadic(
						IndexBase, false, 0, true, QubitIndex),
						GetDyadicToStringComplexSpecifiedOptions(
							IndexBase, false, 0, true, QubitIndex, InputDPI, InputSize, InputColor));
					OutputMap.Add(GetIntVectorOfDyadic(
						0, true, IndexBase, false, QubitIndex),
						GetDyadicToStringComplexSpecifiedOptions(
							0, true, IndexBase, false, QubitIndex, InputDPI, InputSize, InputColor));
				}
				if (IndexBase * IndexBase < KetCount * KetCount) {
					OutputMap.Add(GetIntVectorOfDyadic(
						IndexBase, true, 0, true, QubitIndex),
						GetDyadicToStringComplexSpecifiedOptions(
							IndexBase, true, 0, true, QubitIndex, InputDPI, InputSize, InputColor));
					OutputMap.Add(GetIntVectorOfDyadic(
						0, true, IndexBase, true, QubitIndex),
						GetDyadicToStringComplexSpecifiedOptions(
							0, true, IndexBase, true, QubitIndex, InputDPI, InputSize, InputColor));
				}
			}
			for (int32 IndexExtra = -KetCount; IndexExtra < KetCount; IndexExtra++) {
				if (IndexBase != 0 && IndexExtra != 0) {
					if (IndexBase == 1 && IndexExtra == 1) {
						int biginteger = 3333;
					}
					if (2 * IndexBase * IndexBase + 2 * IndexExtra * IndexExtra <= KetCount * KetCount) {
						OutputMap.Add(GetIntVectorOfDyadic(
							IndexBase, false, IndexExtra, false, QubitIndex),
							GetDyadicToStringComplexSpecifiedOptions(
								IndexBase, false, IndexExtra, false, QubitIndex, InputDPI, InputSize, InputColor));
					}
					if (IndexBase * IndexBase + 2 * IndexExtra * IndexExtra <= KetCount * KetCount) {
						OutputMap.Add(GetIntVectorOfDyadic(
							IndexBase, true, IndexExtra, false, QubitIndex),
							GetDyadicToStringComplexSpecifiedOptions(
								IndexBase, true, IndexExtra, false, QubitIndex, InputDPI, InputSize, InputColor));
					}
					if (2 * IndexBase * IndexBase + IndexExtra * IndexExtra <= KetCount * KetCount) {
						OutputMap.Add(GetIntVectorOfDyadic(
							IndexBase, false, IndexExtra, true, QubitIndex),
							GetDyadicToStringComplexSpecifiedOptions(
								IndexBase, false, IndexExtra, true, QubitIndex, InputDPI, InputSize, InputColor));
					}
					if (IndexBase * IndexBase + IndexExtra * IndexExtra <= KetCount * KetCount) {
						OutputMap.Add(GetIntVectorOfDyadic(
							IndexBase, true, IndexExtra, true, QubitIndex),
							GetDyadicToStringComplexSpecifiedOptions(
								IndexBase, true, IndexExtra, true, QubitIndex, InputDPI, InputSize, InputColor));
					}
				}
			}
		}
	}
}
void ULaTeXCodeCogsActorComponent::GetMapIntVectorStringSpecified(
	int32 InputQubitUpTo,
	FString InputDPI,
	FString InputSize,
	FString InputColor,
	TMap<FIntVector, FString>& OutputMap) {
	OutputMap.Empty();
	TArray<FIntVector> KeyArray;
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, 0, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			0, true, 0, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		1, true, 0, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			1, true, 0, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, 1, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			0, true, 1, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		-1, true, 0, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			-1, true, 0, true, 0, InputDPI, InputSize, InputColor));
	OutputMap.Add(GetIntVectorOfDyadic(
		0, true, -1, true, 0),
		GetDyadicToStringComplexSpecifiedOptions(
			0, true, -1, true, 0, InputDPI, InputSize, InputColor));
	for (int32 QubitIndex = 0; QubitIndex < InputQubitUpTo; QubitIndex++) {
		int32 KetCount = FMath::RoundToInt(FMath::Pow(2.0, QubitIndex));
		for (int32 IndexBase = -KetCount; IndexBase <= KetCount; IndexBase++) {
			OutputMap.Add(GetIntVectorOfDyadic(
				IndexBase, false, 0, true, QubitIndex),
				GetDyadicToStringComplexSpecifiedOptions(
					IndexBase, false, 0, true, QubitIndex, InputDPI, InputSize, InputColor));
			OutputMap.Add(GetIntVectorOfDyadic(
				IndexBase, true, 0, true, QubitIndex),
				GetDyadicToStringComplexSpecifiedOptions(
					IndexBase, true, 0, true, QubitIndex, InputDPI, InputSize, InputColor));
			OutputMap.Add(GetIntVectorOfDyadic(
				0, true, IndexBase, false, QubitIndex),
				GetDyadicToStringComplexSpecifiedOptions(
					0, true, IndexBase, false, QubitIndex, InputDPI, InputSize, InputColor));
			OutputMap.Add(GetIntVectorOfDyadic(
				0, true, IndexBase, true, QubitIndex),
				GetDyadicToStringComplexSpecifiedOptions(
					0, true, IndexBase, true, QubitIndex, InputDPI, InputSize, InputColor));
			for (int32 IndexExtra = -KetCount; IndexExtra <= KetCount; IndexExtra++) {
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, false, IndexExtra, false, QubitIndex),
					GetDyadicToStringComplexSpecifiedOptions(
						IndexBase, false, IndexExtra, false, QubitIndex, InputDPI, InputSize, InputColor));
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, true, IndexExtra, false, QubitIndex),
					GetDyadicToStringComplexSpecifiedOptions(
						IndexBase, true, IndexExtra, false, QubitIndex, InputDPI, InputSize, InputColor));
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, false, IndexExtra, true, QubitIndex),
					GetDyadicToStringComplexSpecifiedOptions(
						IndexBase, false, IndexExtra, true, QubitIndex, InputDPI, InputSize, InputColor));
				OutputMap.Add(GetIntVectorOfDyadic(
					IndexBase, true, IndexExtra, true, QubitIndex),
					GetDyadicToStringComplexSpecifiedOptions(
						IndexBase, true, IndexExtra, true, QubitIndex, InputDPI, InputSize, InputColor));
			}
		}
	}
}
FIntVector ULaTeXCodeCogsActorComponent::GetIntVectorOfDyadic(
	int32 NumeratorReal,
	bool InputRationalRealFlag,
	int32 NumeratorImaginary,
	bool InputRationalImaginaryFlag,
	int32 PowerOfTwoDenominator){
	//FQuantumDyadicComplexRadical LocalDyadic;
	bool RationalRealFlag;
	if (NumeratorReal == 0) {
		RationalRealFlag = true;
	}
	else {
		RationalRealFlag = InputRationalRealFlag;
	}
	bool RationalImaginaryFlag;
	if (NumeratorImaginary == 0) {
		RationalImaginaryFlag = true;
	}
	else {
		RationalImaginaryFlag = InputRationalImaginaryFlag;
	}
	int32 FlagsValue;
	if (RationalRealFlag && RationalImaginaryFlag) {
		FlagsValue = 3;
	}
	else if (!RationalRealFlag && RationalImaginaryFlag) {
		FlagsValue = 2;
	}
	else if (RationalRealFlag && !RationalImaginaryFlag) {
		FlagsValue = 1;
	}
	else if (!RationalRealFlag && !RationalImaginaryFlag) {
		FlagsValue = 0;
	}
	FIntVector OutputIntVector;
	int32 ActualDenominator = FMath::RoundToInt(FMath::Pow(2.0, PowerOfTwoDenominator));
	bool RealUnityFlag = (ActualDenominator == NumeratorReal || ActualDenominator == -NumeratorReal);
	int32 RealUnityValue = 0;
	if (RealUnityFlag) {
		if (ActualDenominator == NumeratorReal) {
			RealUnityValue = 1;
		}
		else {
			RealUnityValue = -1;
		}
	}
	bool ImaginaryUnityFlag = (ActualDenominator == NumeratorImaginary || ActualDenominator == -NumeratorImaginary);
	int32 ImaginaryUnityValue = 0;
	if (ImaginaryUnityFlag) {
		if (ActualDenominator == NumeratorImaginary) {
			ImaginaryUnityValue = 1;
		}
		else {
			ImaginaryUnityValue = -1;
		}
	}
	if (RealUnityFlag && ImaginaryUnityFlag){
		OutputIntVector = FIntVector(RealUnityValue, ImaginaryUnityValue, FlagsValue);
	}
	else if (NumeratorImaginary == 0 && NumeratorImaginary == 0) {
		OutputIntVector = FIntVector(0, 0, 3);
	}
	else if (RealUnityFlag
		&& NumeratorImaginary == 0) {
		OutputIntVector = FIntVector(RealUnityValue, 0, FlagsValue);
	}
	else if (ImaginaryUnityFlag
		&& NumeratorReal == 0) {
		OutputIntVector = FIntVector(0, ImaginaryUnityValue, FlagsValue);
	}
	else {
		int32 PowerValue = PowerOfTwoDenominator;
		int32 ThirdPiece = PowerValue * 4;
		OutputIntVector = FIntVector(NumeratorReal, NumeratorImaginary, ThirdPiece + FlagsValue);
	}
	//if (ActualDenominator == NumeratorReal
	//	&& RationalRealFlag
	//	&& NumeratorImaginary == 0
	//	&& RationalImaginaryFlag) {
	//	OutputIntVector = FIntVector(1, 0, 3);
	//}
	//else if (ActualDenominator == -NumeratorReal
	//	&& RationalRealFlag
	//	&& NumeratorImaginary == 0
	//	&& RationalImaginaryFlag) {
	//	OutputIntVector = FIntVector(-1, 0, 3);
	//}
	//else if (ActualDenominator == NumeratorImaginary
	//	&& RationalImaginaryFlag
	//	&& NumeratorReal == 0
	//	&& RationalRealFlag) {
	//	OutputIntVector = FIntVector(0, 1, 3);
	//}
	//else if (ActualDenominator == -NumeratorImaginary
	//	&& RationalImaginaryFlag
	//	&& NumeratorReal == 0
	//	&& RationalRealFlag) {
	//	OutputIntVector = FIntVector(0, -1, 3);
	//}
	//else {
	//	int32 PowerValue = PowerOfTwoDenominator;
	//	int32 ThirdPiece = PowerValue * 4;
	//	OutputIntVector = FIntVector(NumeratorReal, NumeratorImaginary, ThirdPiece + FlagsValue);
	//}
	return OutputIntVector;
}
FString ULaTeXCodeCogsActorComponent::GetDyadicToStringSingle(
	int32 Numerator,
	bool RationalFlag,
	bool RealFlag,
	int32 PowerOfTwoDenominator) {
	int32 ActualDenominator = FMath::RoundToInt(FMath::Pow(2.0, PowerOfTwoDenominator));
	FString LocalString = "";
	if (Numerator == -ActualDenominator) {
		if (RealFlag && RationalFlag) {
			LocalString += "-1";
		}
		else if (RealFlag && !RationalFlag) {
			LocalString += "-\\sqrt{2}";
		}
		else if (!RealFlag && RationalFlag) {
			LocalString += "-i";
		}
		else if (!RealFlag && !RationalFlag) {
			LocalString += "-i\\sqrt{2}";
		}
	}
	else if (Numerator == ActualDenominator) {
		if (RealFlag && RationalFlag) {
			LocalString += "1";
		}
		else if (RealFlag && !RationalFlag) {
			LocalString += "\\sqrt{2}";
		}
		else if (!RealFlag && RationalFlag) {
			LocalString += "i";
		}
		else if (!RealFlag && !RationalFlag) {
			LocalString += "i\\sqrt{2}";
		}
	}
	else if (Numerator == -1) {
		if (RealFlag && RationalFlag) {
			LocalString += "\\frac{-1}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RealFlag && !RationalFlag) {
			LocalString += "\\frac{-\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RealFlag && RationalFlag) {
			LocalString += "\\frac{-i}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RealFlag && !RationalFlag) {
			LocalString += "\\frac{-i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
	}
	else if (Numerator == 1) {
		if (RealFlag && RationalFlag) {
			LocalString += "\\frac{1}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RealFlag && !RationalFlag) {
			LocalString += "\\frac{\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RealFlag && RationalFlag) {
			LocalString += "\\frac{i}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RealFlag && !RationalFlag) {
			LocalString += "\\frac{i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
	}
	else {
		if (RealFlag && RationalFlag) {
			LocalString += "\\frac{" 
				+ FString::FromInt(Numerator) + "}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RealFlag && !RationalFlag) {
			LocalString += "\\frac{"
				+ FString::FromInt(Numerator) + "\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RealFlag && RationalFlag) {
			LocalString += "\\frac{"
				+ FString::FromInt(Numerator) + "i}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RealFlag && !RationalFlag) {
			LocalString += "\\frac{"
				+ FString::FromInt(Numerator) + "i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
	}
	return LocalString;
}
FString ULaTeXCodeCogsActorComponent::GetDyadicToStringComplexSpecifiedOptions(
	int32 NumeratorReal,
	bool RationalRealFlag,
	int32 NumeratorImaginary,
	bool RationalImaginaryFlag,
	int32 PowerOfTwoDenominator,
	FString InputDPI,
	FString InputSize,
	FString InputColor) {
	FString LocalString = "";
	if (NumeratorReal == 0 && NumeratorImaginary == 0) {
		LocalString += "0";
	}
	else if (NumeratorReal != 0 && NumeratorImaginary == 0) {
		LocalString += GetDyadicToStringSingle(NumeratorReal,RationalRealFlag, true,PowerOfTwoDenominator);
	}
	else if (NumeratorReal == 0 && NumeratorImaginary != 0) {
		LocalString += GetDyadicToStringSingle(NumeratorImaginary, RationalImaginaryFlag, false, PowerOfTwoDenominator);
	}
	else if (NumeratorReal != 0 && NumeratorImaginary != 0) {
		if (NumeratorImaginary >= 0) {
			LocalString += GetDyadicToStringSingle(NumeratorReal, RationalRealFlag, true, PowerOfTwoDenominator);
			LocalString += "&plus;";
			LocalString += GetDyadicToStringSingle(NumeratorImaginary, RationalImaginaryFlag, false, PowerOfTwoDenominator);
		}
		else {
			LocalString += GetDyadicToStringSingle(NumeratorReal, RationalRealFlag, true, PowerOfTwoDenominator);
			LocalString += "-";
			LocalString += GetDyadicToStringSingle(-NumeratorImaginary, RationalImaginaryFlag, false, PowerOfTwoDenominator);
		}
	}
	FString OutputString;
	if (InputSize == "tiny"
		|| InputSize == "small"
		|| InputSize == "large"
		|| InputSize == "LARGE"
		|| InputSize == "huge") {
		OutputString = "\\" + InputSize + "&space;\\dpi{" + InputDPI + "}&space;{\\color{" + InputColor + "}\\mathbf{" + LocalString + "}}";
	}
	else {
		OutputString = "\\dpi{" + InputDPI + "}&space;{\\color{" + InputColor + "}\\mathbf{" + LocalString + "}}";
	}
	//FString OutputString = "\\" + InputSize + "&space;\\dpi{" + InputDPI + "}&space;{\\color{" + InputColor + "}\\mathbf{" + LocalString + "}}";
	return OutputString;
}
FString ULaTeXCodeCogsActorComponent::GetDyadicToString(
	int32 NumeratorReal,
	bool RationalRealFlag,
	int32 NumeratorImaginary,
	bool RationalImaginaryFlag,
	int32 PowerOfTwoDenominator) {
	//FString OutputString;
	//int32 ActualDenominator = FMath::RoundToInt(FMath::Pow(2.0, PowerOfTwoDenominator));
	//FString LocalString = "";
	//if (NumeratorReal == 0 && NumeratorImaginary == 0) {
	//	LocalString += "0";
	//}
	//else if (NumeratorReal != 0 && NumeratorImaginary == 0) {
	//	if (RationalRealFlag && -NumeratorReal == ActualDenominator) {
	//		LocalString += "-1";
	//	}
	//	else if (RationalRealFlag && NumeratorReal == ActualDenominator) {
	//		LocalString += "1";
	//	}
	//	else if (!RationalRealFlag && NumeratorReal == -1) {
	//		LocalString += "\\frac{-\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (!RationalRealFlag && NumeratorReal == 1) {
	//		LocalString += "\\frac{\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (RationalRealFlag) {
	//		LocalString += "\\frac{"
	//			+ FString::FromInt(NumeratorReal) + "}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else {
	//		LocalString += FString::FString("\\frac{")
	//			+ FString::FromInt(NumeratorReal) + "\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//}
	//else if (NumeratorReal == 0 && NumeratorImaginary != 0) {
	//	if (RationalImaginaryFlag && -NumeratorImaginary == ActualDenominator) {
	//		LocalString += "-i";
	//	}
	//	else if (RationalImaginaryFlag && NumeratorImaginary == ActualDenominator) {
	//		LocalString += "i";
	//	}
	//	else if (!RationalImaginaryFlag && NumeratorImaginary == -1) {
	//		LocalString += "\\frac{-i\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (!RationalImaginaryFlag && NumeratorImaginary == 1) {
	//		LocalString += "\\frac{i\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (RationalImaginaryFlag) {
	//		LocalString += "\\frac{"
	//			+ FString::FromInt(NumeratorImaginary) + "i}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else {
	//		LocalString += FString::FString("\\frac{")
	//			+ FString::FromInt(NumeratorReal) + "i\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//}
	//else if (NumeratorReal != 0 && NumeratorImaginary != 0) {
	//	if (RationalRealFlag && -NumeratorReal == ActualDenominator) {
	//		LocalString += "-1";
	//	}
	//	else if (RationalRealFlag && NumeratorReal == ActualDenominator) {
	//		LocalString += "1";
	//	}
	//	else if (!RationalRealFlag && NumeratorReal == -1) {
	//		LocalString += "\\frac{-\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (!RationalRealFlag && NumeratorReal == 1) {
	//		LocalString += "\\frac{\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (RationalRealFlag) {
	//		LocalString += "\\frac{"
	//			+ FString::FromInt(NumeratorReal) + "}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else {
	//		LocalString += FString::FString("\\frac{")
	//			+ FString::FromInt(NumeratorReal) + "\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	if (RationalImaginaryFlag && -NumeratorImaginary == ActualDenominator) {
	//		LocalString += "-i";
	//	}
	//	else if (RationalImaginaryFlag && NumeratorImaginary == ActualDenominator) {
	//		LocalString += "i";
	//	}
	//	else if (!RationalImaginaryFlag && NumeratorImaginary == -1) {
	//		LocalString += "-\\frac{i\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (!RationalImaginaryFlag && NumeratorImaginary == 1) {
	//		LocalString += "\\frac{i\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (RationalImaginaryFlag && NumeratorImaginary == -1) {
	//		LocalString += "-\\frac{-i}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (RationalImaginaryFlag && NumeratorImaginary == 1) {
	//		LocalString += "\\frac{i}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else if (RationalImaginaryFlag) {
	//		if (NumeratorImaginary < 0) {
	//			LocalString += "-\\frac{"
	//				+ FString::FromInt(-NumeratorImaginary) + "i}{"
	//				+ FString::FromInt(ActualDenominator) + "}";
	//		}
	//		else {
	//			LocalString += "\\frac{"
	//				+ FString::FromInt(NumeratorImaginary) + "i}{"
	//				+ FString::FromInt(ActualDenominator) + "}";
	//		}
	//	}
	//	if (NumeratorImaginary < 0) {
	//		LocalString += "-\\frac{"
	//			+ FString::FromInt(-NumeratorImaginary) + "i\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//	else {
	//		LocalString += "\\frac{"
	//			+ FString::FromInt(NumeratorImaginary) + "i\\sqrt{2}}{"
	//			+ FString::FromInt(ActualDenominator) + "}";
	//	}
	//}
	//OutputString = "\\dpi{150}&space;{\\color{White}\\mathbf{" + LocalString + "}}";
	return GetDyadicToStringComplexSpecifiedOptions(NumeratorReal, RationalRealFlag, NumeratorImaginary, RationalImaginaryFlag,
		PowerOfTwoDenominator, "300", "", "White");
	//return GetDyadicToStringSpecifiedOptions(NumeratorReal, RationalRealFlag, NumeratorImaginary, RationalImaginaryFlag,
		//PowerOfTwoDenominator, "300", "","White");
}
FString ULaTeXCodeCogsActorComponent::GetDyadicToStringSpecifiedOptions(
	int32 NumeratorReal,
	bool RationalRealFlag,
	int32 NumeratorImaginary,
	bool RationalImaginaryFlag,
	int32 PowerOfTwoDenominator,
	FString InputDPI,
	FString InputSize,
	FString InputColor) {
	FString OutputString;
	int32 ActualDenominator = FMath::RoundToInt(FMath::Pow(2.0, PowerOfTwoDenominator));
	FString LocalString = "";
	if (NumeratorReal == 0 && NumeratorImaginary == 0) {
		LocalString += "0";
	}
	else if (NumeratorReal != 0 && NumeratorImaginary == 0) {
		if (RationalRealFlag && -NumeratorReal == ActualDenominator) {
			LocalString += "-1";
		}
		else if (RationalRealFlag && NumeratorReal == ActualDenominator) {
			LocalString += "1";
		}
		else if (!RationalRealFlag && NumeratorReal == -1) {
			LocalString += "\\frac{-\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RationalRealFlag && NumeratorReal == 1) {
			LocalString += "\\frac{\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RationalRealFlag) {
			LocalString += "\\frac{"
				+ FString::FromInt(NumeratorReal) + "}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else {
			LocalString += FString::FString("\\frac{")
				+ FString::FromInt(NumeratorReal) + "\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
	}
	else if (NumeratorReal == 0 && NumeratorImaginary != 0) {
		if (RationalImaginaryFlag && -NumeratorImaginary == ActualDenominator) {
			LocalString += "-i";
		}
		else if (RationalImaginaryFlag && NumeratorImaginary == ActualDenominator) {
			LocalString += "i";
		}
		else if (!RationalImaginaryFlag && NumeratorImaginary == -1) {
			LocalString += "\\frac{-i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RationalImaginaryFlag && NumeratorImaginary == 1) {
			LocalString += "\\frac{i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RationalImaginaryFlag) {
			LocalString += "\\frac{"
				+ FString::FromInt(NumeratorImaginary) + "i}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else {
			LocalString += FString::FString("\\frac{")
				+ FString::FromInt(NumeratorReal) + "i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
	}
	else if (NumeratorReal != 0 && NumeratorImaginary != 0) {
		if (RationalRealFlag && -NumeratorReal == ActualDenominator) {
			LocalString += "-1";
		}
		else if (RationalRealFlag && NumeratorReal == ActualDenominator) {
			LocalString += "1";
		}
		else if (!RationalRealFlag && NumeratorReal == -1) {
			LocalString += "\\frac{-\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RationalRealFlag && NumeratorReal == 1) {
			LocalString += "\\frac{\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RationalRealFlag) {
			LocalString += "\\frac{"
				+ FString::FromInt(NumeratorReal) + "}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else {
			LocalString += FString::FString("\\frac{")
				+ FString::FromInt(NumeratorReal) + "\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		if (RationalImaginaryFlag && -NumeratorImaginary == ActualDenominator) {
			LocalString += "-i";
		}
		else if (RationalImaginaryFlag && NumeratorImaginary == ActualDenominator) {
			LocalString += "i";
		}
		else if (!RationalImaginaryFlag && NumeratorImaginary == -1) {
			LocalString += "-\\frac{i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (!RationalImaginaryFlag && NumeratorImaginary == 1) {
			LocalString += "\\frac{i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RationalImaginaryFlag && NumeratorImaginary == -1) {
			LocalString += "-\\frac{-i}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RationalImaginaryFlag && NumeratorImaginary == 1) {
			LocalString += "\\frac{i}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else if (RationalImaginaryFlag) {
			if (NumeratorImaginary < 0) {
				LocalString += "-\\frac{"
					+ FString::FromInt(-NumeratorImaginary) + "i}{"
					+ FString::FromInt(ActualDenominator) + "}";
			}
			else {
				LocalString += "\\frac{"
					+ FString::FromInt(NumeratorImaginary) + "i}{"
					+ FString::FromInt(ActualDenominator) + "}";
			}
		}
		if (NumeratorImaginary < 0) {
			LocalString += "-\\frac{"
				+ FString::FromInt(-NumeratorImaginary) + "i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
		else {
			LocalString += "\\frac{"
				+ FString::FromInt(NumeratorImaginary) + "i\\sqrt{2}}{"
				+ FString::FromInt(ActualDenominator) + "}";
		}
	}
	if (InputSize == "tiny"
		|| InputSize == "small"
		|| InputSize == "large"
		|| InputSize == "LARGE"
		|| InputSize == "huge") {
		OutputString = "\\" + InputSize + "&space;\\dpi{" + InputDPI + "}&space;{\\color{" + InputColor + "}\\mathbf{" + LocalString + "}}";
	}
	else {
		OutputString = "\\dpi{" + InputDPI + "}&space;{\\color{" + InputColor + "}\\mathbf{" + LocalString + "}}";
	}
	return OutputString;
}
void ULaTeXCodeCogsActorComponent::FxnGetDyadicOfIntVector(
	FIntVector InputIntVector,
	int32& OutputNumeratorReal,
	bool& OutputRationalRealFlag,
	int32& OutputNumeratorImaginary,
	bool& OutputRationalImaginaryFlag,
	int32& PowerOfTwoDenominator,
	bool& ValidMagnitude) {
	OutputNumeratorReal = InputIntVector.X;
	OutputNumeratorImaginary = InputIntVector.Y;
	uint32  LocalValue = InputIntVector.Z;
	PowerOfTwoDenominator = (LocalValue >> 2);
	if (InputIntVector.Z % 4 == 3) {
		OutputRationalRealFlag = true;
		OutputRationalImaginaryFlag = true;
		ValidMagnitude =
			((FMath::Pow(OutputNumeratorReal, 2.0)
				+ FMath::Pow(OutputNumeratorImaginary, 2.0))
				< PowerOfTwoDenominator);
	}
	else if (InputIntVector.Z % 4 == 2) {
		OutputRationalRealFlag = false;
		OutputRationalImaginaryFlag = true;
		ValidMagnitude =
			((2.0 * FMath::Pow(OutputNumeratorReal, 2.0)
				+ FMath::Pow(OutputNumeratorImaginary, 2.0))
				< PowerOfTwoDenominator);
	}
	else if (InputIntVector.Z % 4 == 1) {
		OutputRationalRealFlag = true;
		OutputRationalImaginaryFlag = false;
		ValidMagnitude =
			((FMath::Pow(OutputNumeratorReal, 2.0)
				+ 2.0 * FMath::Pow(OutputNumeratorImaginary, 2.0))
				< PowerOfTwoDenominator);
	}
	else if (InputIntVector.Z % 4 == 0) {
		OutputRationalRealFlag = false;
		OutputRationalImaginaryFlag = false;
		ValidMagnitude =
			((2.0 * FMath::Pow(OutputNumeratorReal, 2.0)
				+ 2.0 * FMath::Pow(OutputNumeratorImaginary, 2.0))
				< PowerOfTwoDenominator);
	}
}
void ULaTeXCodeCogsActorComponent::FxnGetIntVectorOfDyadic(
	int32 InputNumeratorReal,
	bool InputRationalRealFlag,
	int32 InputNumeratorImaginary,
	bool InputRationalImaginaryFlag,
	int32 PowerOfTwoDenominator,
	bool& ValidMagnitude,
	FIntVector& OutputIntVector) {
	int32 LocalValueZ = 0;
	int32 LocalSquareReal, LocalSquareImaginary, LocalSquareActualDenominator;
	LocalSquareActualDenominator = FMath::RoundToInt(FMath::Pow(2.0, PowerOfTwoDenominator * 2.0));
	if (InputRationalRealFlag || InputNumeratorReal == 0) {
		LocalValueZ += 1;
		LocalSquareReal = InputNumeratorReal * InputNumeratorReal;
	}
	else {
		LocalSquareReal = 2 * InputNumeratorReal * InputNumeratorReal;
	}
	if (InputRationalImaginaryFlag || InputNumeratorImaginary == 0) {
		LocalValueZ += 2;
		LocalSquareImaginary = InputNumeratorImaginary * InputNumeratorImaginary;
	}
	else {
		LocalSquareImaginary = 2 * InputNumeratorImaginary * InputNumeratorImaginary;
	}
	LocalValueZ += (4 * PowerOfTwoDenominator);
	OutputIntVector = FIntVector(InputNumeratorReal, InputNumeratorImaginary, LocalValueZ);
	ValidMagnitude = (LocalSquareReal + LocalSquareImaginary) < LocalSquareActualDenominator;
}