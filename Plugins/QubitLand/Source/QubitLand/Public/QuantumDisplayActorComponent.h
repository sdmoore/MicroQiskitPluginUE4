// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "Kismet/BlueprintFunctionLibrary.h"
//#include "QCDisplayBlueprintFxnLibrary.h"
//#include "QuantumLandBlueprintFxnLibrary.h"
//#include "MultiMapIntegerActorComponent.h"
//#include "QuantumGateType.h"
//#include "Components/ActorComponent.h"
//#include "QuantumDisplayActorComponent.generated.h"
//
//
//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
//class QUBITLAND_API UQuantumDisplayActorComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:	
//	// Sets default values for this component's properties
//	UQuantumDisplayActorComponent();
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> NormalMaterialMap;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> GlowMaterialMap;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMaterialInterface, UMaterialInterface*> HighlightMaterialMap;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EActualISMC, EMeshISMC> MapActualToMesh;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, FVector> MapSizeMesh;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EKetDisplayISMC, EActualISMC> DisplyKetToActualISMC;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<ETransitionISMC, EActualISMC> DisplyTransitionToActualISMC;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EQubitSplitISMC, EActualISMC> DisplyQubitSplitToActualISMC;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumDisplayParam QuantumDisplayParam;
//	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, FRotator> MapRotatorMeshZY;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<EMeshISMC, UStaticMesh*> MapStaticMesh;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntVector, FQuantumTransitionDisplay> MapIntVectorTransitionDisplay;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FIntPoint, FQuantumKetDisplay> MapIntPointKetDisplay;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumQubitSplitDisplay QubitSplitDisplay;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) FQuantumDisplayDerived QuantumDisplayDerived;
//	//UFUNCTION(BlueprintCallable, Category = "Quantum Display Function")
//	//	void InitializeDisplayStructuresForKetCircuit(
//	//		UPARAM(ref) UMultiMapIntegerActorComponent* InputMMIAC,
//	//		UPARAM(ref) FQuantumDisplayParam& InputDisplayParam,
//	//		UPARAM(ref) TMap<int32, FVector2D>& InputKetMap,
//	//		UPARAM(ref) TArray<FQuantumGateSpecifier>& InputCircuitArray,
//	//		UPARAM(ref) TMap<FIntVector, FVector2D>& InputOperatorMapToUpdate,
//	//		UPARAM(ref) TMap<FIntVector, FVector2D>& InputTransitionMapToUpdate,
//	//		UPARAM(ref) TMap<FIntPoint, FVector2D>& InputKetMapToUpdate,
//	//		bool& SuccessFlag);
//
//};
