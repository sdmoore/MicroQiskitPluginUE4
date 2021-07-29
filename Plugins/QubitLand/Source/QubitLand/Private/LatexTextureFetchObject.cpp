// Fill out your copyright notice in the Description page of Project Settings.


#include "LatexTextureFetchObject.h"
void ULatexTextureFetchObject::HttpInitialize(){
	Http = &FHttpModule::Get();
	DatabaseMapUpdated = true;
}
void ULatexTextureFetchObject::LoadFromGameInstanceSave(
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
void ULatexTextureFetchObject::UpdateGameInstanceSave(
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
void ULatexTextureFetchObject::HttpCall(
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
	if (!EquationStringToTextureMap.Contains(HttpQuery)) {
		DatabaseMapUpdated = false;
		if (!EquationStringPending.Contains(HttpQuery)) {
			AlreadyPresentFlag = false;
			RequestAlreadyPendingFlag = false;
			HtmlRequestCompleteFlag = false;
			TSharedRef<IHttpRequest> Request = Http->CreateRequest();
			Request->OnProcessRequestComplete().BindUObject(this, &ULatexTextureFetchObject::OnResponseReceived);
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
void ULatexTextureFetchObject::BasicHttpCall(
	FString UrlBase,
	FString HttpQuery,
	FString& FinalHttpQuery) {
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ULatexTextureFetchObject::BasicOnResponseReceived);
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
void ULatexTextureFetchObject::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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
void ULatexTextureFetchObject::BasicOnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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

