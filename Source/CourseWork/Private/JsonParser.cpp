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

/*
// Example Blueprint function that receives any struct as input
UFUNCTION(BlueprintCallable, Category = "Example", CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
static void ReceiveSomeStruct(UProperty* AnyStruct);

DECLARE_FUNCTION(execReceiveSomeStruct)
{
	// Steps into the stack, walking to the next property in it
	Stack.Step(Stack.Object, NULL);

	// Grab the last property found when we walked the stack
	// This does not contains the property value, only its type information
	UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

	// Grab the base address where the struct actually stores its data
	// This is where the property value is truly stored
	void* StructPtr = Stack.MostRecentPropertyAddress;

	// We need this to wrap up the stack
	P_FINISH;

	// Iterate through the struct
	IterateThroughStructProperty(StructProperty, StructPtr);
}


void ParseProperty(UProperty* Property, void* ValuePtr)
{

	float FloatValue;
	int32 IntValue;
	bool BoolValue;
	FString StringValue;
	FName NameValue;
	FText TextValue;


	// Here's how to read integer and float properties
	if (UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property))
	{
		if (NumericProperty->IsFloatingPoint())
		{
			FloatValue = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
		}
		else if (NumericProperty->IsInteger())
		{
			IntValue = NumericProperty->GetSignedIntPropertyValue(ValuePtr);
		}
	}

	// How to read booleans
	if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
	{
		BoolValue = BoolProperty->GetPropertyValue(ValuePtr);
	}

	// Reading names
	if (UNameProperty* NameProperty = Cast<UNameProperty>(Property))
	{
		NameValue = NameProperty->GetPropertyValue(ValuePtr);
	}

	// Reading strings
	if (UStrProperty* StringProperty = Cast<UStrProperty>(Property))
	{
		StringValue = StringProperty->GetPropertyValue(ValuePtr);
	}

	// Reading texts
	if (UTextProperty* TextProperty = Cast<UTextProperty>(Property))
	{
		TextValue = TextProperty->GetPropertyValue(ValuePtr);
	}

	// Reading an array
	if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
	{
		// We need the helper to get to the items of the array            
		FScriptArrayHelper Helper(ArrayProperty, ValuePtr);
		for (int32 i = 0, n = Helper.Num(); i < n; ++i)
		{
			ParseProperty(ArrayProperty->Inner, Helper.GetRawPtr(i));
		}
	}

	// Reading a nested struct
	if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
	{
		IterateThroughStructProperty(StructProperty, ValuePtr);
	}
}

void IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr)
{
	// Walk the structs' properties
	UScriptStruct* Struct = StructProperty->Struct;
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = *It;

		// This is the variable name if you need it
		FString VariableName = Property->GetName();

		// Never assume ArrayDim is always 1
		for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++)
		{
			// This grabs the pointer to where the property value is stored
			void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, ArrayIndex);

			// Parse this property
			ParseProperty(Property, ValuePtr);
		}
	}
}

UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary")
static void switchValue(const float a,const float b, float &a_out, float &b_out);

void UMyBlueprintFunctionLibrary::switchValue(const float a, const float b, float &a_out, float &b_out)
{
a_out = b;
b_out = a;
}


*/