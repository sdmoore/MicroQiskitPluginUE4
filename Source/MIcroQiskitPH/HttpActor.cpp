//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "HttpActor.h"
//
//// Sets default values
//AHttpActor::AHttpActor()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}
//
//// Called when the game starts or when spawned
//void AHttpActor::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void AHttpActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
// Fill out your copyright notice in the Description page of Project Settings.

//#include "CPPProject.h"
#include "HttpActor.h"

// Sets default values
AHttpActor::AHttpActor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//When the object is constructed, Get the HTTP module
	Http = &FHttpModule::Get();
	
}

// Called when the game starts or when spawned
void AHttpActor::BeginPlay()
{
	////MyHttpCall();
	Super::BeginPlay();
}

/*Http call*/
void AHttpActor::MyHttpCall(FString UrlInput)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceived);
	//This is the url on which to process the request
	//FString InputURL = FString("https://pbs.twimg.com/media/Bz2wpB3CMAAJWoa.png");
	//FString InputURL = FString("https://latex.codecogs.com/gif.latex?\frac{\\sqrt{2}}{2}");
	Request->SetURL(UrlInput);
	Request->SetVerb("GET");
	
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	//Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void AHttpActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	TArray<uint8> ImageData = Response->GetContent();
	//Create T2D!
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
	{
		//const TArray<uint8>* UncompressedBGRA = NULL;
		TArray<uint8> UncompressedBGRA;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

			////Valid?
			//if (!LoadedT2D) return NULL;
			////~~~~~~~~~~~~~~

			//Out!
			int32 Width = ImageWrapper->GetWidth();
			int32 Height = ImageWrapper->GetHeight();

			//Copy!
			void* TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
			LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();

			//Update!
			LoadedT2D->UpdateResource();
		}
	}
	//Create a pointer to hold the json serialized data
	//TSharedPtr JsonObject;

	//Create a reader pointer to read the json data
	//TSharedRef Reader = TJsonReaderFactory::Create(Response->GetContentAsString());
	//TSharedRef< TJsonReader < TCHAR > > Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	//TSharedRef Reader = ReaderDirect;
	FileSize = Response->GetContentLength();
	ContentType = Response->GetContentType();
	
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

