// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CommandBase.generated.h"

class AGemiknightsGameMode;

DECLARE_DELEGATE(OnCommandFinishedSignature);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GEMIKNIGHTS_API UCommandBase : public UObject
{
	GENERATED_BODY()
	
public:
	void SetArguments(TArray<FString>& Arguments);

	UFUNCTION(BlueprintNativeEvent)
	void RunCommand(AGemiknightsGameMode* GameMode);

	UFUNCTION(BlueprintCallable)
	void EndCommand();
	
	OnCommandFinishedSignature OnCommandFinished;

	FString DebugPrintCommand();
protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> StoredArgs{};
};

