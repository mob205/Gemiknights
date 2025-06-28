// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandBase.h"

void UCommandBase::SetArguments(TArray<FString>& Arguments)
{
	StoredArgs = MoveTemp(Arguments);
}

void UCommandBase::EndCommand()
{
	OnCommandFinished.ExecuteIfBound();
}

FString UCommandBase::DebugPrintCommand()
{
	FString Result = FString::Printf(TEXT("Command %s with Arguments: "), *GetName());

	for (const auto& Arg : StoredArgs)
	{
		Result += TEXT(" ") + Arg;
	}
	return Result;
}

void UCommandBase::RunCommand_Implementation(AGemiknightsGameMode* GameMode)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Running base command %s"), *GetName()));
}
