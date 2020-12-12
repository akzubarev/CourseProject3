// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParser.h"
#include "Json.h"
#include "Engine.h"

// Sets default values
AJsonParser::AJsonParser()
{

}

// Called when the game starts or when spawned
void AJsonParser::BeginPlay()
{
	Super::BeginPlay();
}

void AJsonParser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



FString AJsonParser::ParseToString(FString path)
{

	//UE_LOG(LogTemp, Warning, TEXT("FirstDebugMessageGlog"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("First debug message"));
	//GLog->Log("FirstDebugMessageGlog" + jsonstring);

	const FString JsonFilePath = FPaths::ProjectContentDir() + path;
	FString JsonString; //Json converted to FString
	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);


	return JsonString;
	/*
	//Displaying the json in a string format inside the output log


	//Create a json object to store the information from the json string
	//The json reader is used to deserialize the json object later on
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		//The person "object" that is retrieved from the given json file
		TSharedPtr<FJsonObject> PersonObject = JsonObject->GetObjectField("Person");

		//Getting various properties
		GLog->Log("Balance:" + PersonObject->GetStringField("balance"));
		GLog->Log("Age:" + FString::FromInt(PersonObject->GetIntegerField("age")));
		FString IsActiveStr = (PersonObject->GetBoolField("isActive")) ? "Active" : "Inactive";
		GLog->Log("IsActive:" + IsActiveStr);
		GLog->Log("Latitude:" + FString::SanitizeFloat(PersonObject->GetNumberField("latitude")));

		//Retrieving an array property and printing each field
		TArray<TSharedPtr<FJsonValue>> objArray = PersonObject->GetArrayField("family");
		GLog->Log("printing family names...");
		for (int32 index = 0; index < objArray.Num(); index++)
		{

			GLog->Log("name:" + objArray[index]->AsString());
		}
	}
	else
	{
		GLog->Log("couldn't deserialize");
	}
	*/
}


