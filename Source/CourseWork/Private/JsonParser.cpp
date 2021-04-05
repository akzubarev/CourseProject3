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

void AJsonParser::WriteToFile(FString text, FString filepath) {

	const FString fullpath = FPaths::ProjectContentDir() + filepath;
	FFileHelper::SaveStringToFile(text, *fullpath);//, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

}

USkeletalMesh* AJsonParser::LoadSkMeshFromPath(FString Path)
{
	return Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *Path));
}

/*
TMap<FString, FString> AJsonParser::GetPartsFieldsByType(FString type)
{
	return *fieldsDict.Find(type);
}

TArray<FString> AJsonParser::GetPartsFieldsKeys()
{
	//return fieldsDict.GetKeys();   //TMap has no fuction for keys???
	TArray<FString> res;
	for (auto elem : fieldsDict)
		res.Add(elem.Key);
	return res;
}
*/

void mylog(FString text)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}


void mylog(int num)
{
	FString text = FString::FromInt(num);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}


int findPartEnd(FString text)
{
	int opened = 0;
	for (int i = 0; i < text.Len(); i++)
	{
		if (text[i] == '{')
			opened++;
		if (text[i] == '}')
			if (opened > 1)
				opened--;
			else
				return i;

	}
	return -1;
}

void AJsonParser::ReadSchema(FString Path, TMap<FString, FString>& Robot,
	TMap<FString, FString>& Hands, TMap<FString, FString>& Legs,
	TMap<FString, FString>& Bodies, TMap<FString, FString>& Heads)
{
	FString schema = AJsonParser::ParseToString(Path);
	FString part = "", name = "", type = "";
	int idxtocut = schema.Find(TEXT("defs")) + 5;
	schema = schema.RightChop(idxtocut);
	idxtocut = schema.Find("{");
	bool readRobot = false;
	int count = 0;

	while (!readRobot)
	{
		schema = schema.RightChop(idxtocut + 1);

		idxtocut = findPartEnd(schema) + 2;
		FString toanalyze = schema.Mid(0, idxtocut);
		//mylog(toanalyze);

		int start = toanalyze.Find("\"");
		int end = toanalyze.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromStart, start + 1);
		part = toanalyze.Mid(start + 1, (end - 1) - (start + 1) + 1);
		//mylog("Part: " + part);

		toanalyze = toanalyze.RightChop(end + 1);
		TMap<FString, FString> fields;
		bool readPart = false;
		end = -1;

		while (!readPart) {
			start = toanalyze.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromStart, end + 1);
			if (start < 0)
			{
				readPart = true;
				break;
			}

			end = toanalyze.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromStart, start + 1);
			name = toanalyze.Mid(start + 1, (end - 1) - (start + 1) + 1);

			int refidx = toanalyze.Find("ref", ESearchCase::IgnoreCase, ESearchDir::FromStart, end + 1);
			int typeidx = toanalyze.Find("type", ESearchCase::IgnoreCase, ESearchDir::FromStart, end + 1);
			if ((refidx > typeidx || refidx == -1)
				&& typeidx != -1)
				start = typeidx + 5;
			else
				start = refidx + 4;

			start = toanalyze.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromStart, start);
			end = toanalyze.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromStart, start + 1);

			type = toanalyze.Mid(start + 1, (end - 1) - (start + 1) + 1);

			if (type.Contains("#"))
				type = TEXT("part");

			//mylog(name + ": " + type);
			fields.Add(name, type);
		}



		//fieldsDict.Add(part, fields);

		// there is no c++ switch for string types in ue4
		if (part == "Combat")
			Hands = fields;
		else if (part == "Movement")
			Legs = fields;
		else if (part == "Armour")
			Bodies = fields;
		else if (part == "Basis")
			Heads = fields;
		else if (part == "Robot")
		{
			Robot = fields;
			readRobot = true;
		}
	}
}