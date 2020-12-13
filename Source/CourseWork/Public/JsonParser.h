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

//	UPROPERTY(BlueprintReadOnly, Category = "JsonParser")
//		FString jsonstring;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FString ParseToString(FString path);

	UFUNCTION(BlueprintCallable)
		void WriteToFile(FString text, FString filepath);

};
