// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JsonParser.generated.h"

UCLASS()
class COURSEWORK_API AJsonParser : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJsonParser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//TMap<FString, TMap<FString, FString>> fieldsDict;

	//	UPROPERTY(BlueprintReadOnly, Category = "JsonParser")
	//		FString jsonstring;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		FString ParseToString(FString path);

	UFUNCTION(BlueprintCallable)
		void WriteToFile(FString text, FString filepath);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE USkeletalMesh* LoadSkMeshFromPath(FString Path)
	{
		return Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *Path));
	}

	/*
	UFUNCTION(BlueprintCallable)
		TMap<FString, FString> GetPartsFieldsByType(FString type);

	UFUNCTION(BlueprintCallable)
		TArray<FString> GetPartsFieldsKeys();
	*/

	UFUNCTION(BlueprintCallable)
		void ReadSchema(FString Path, TMap<FString, FString>& Robot, TMap<FString, FString>& Hands, TMap<FString, FString>& Legs, TMap<FString, FString>& Bodies, TMap<FString, FString>& Heads);

};
