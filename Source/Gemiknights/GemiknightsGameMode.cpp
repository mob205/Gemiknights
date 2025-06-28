// Copyright Epic Games, Inc. All Rights Reserved.

#include "GemiknightsGameMode.h"

#include "CommandBase.h"
#include "GemiknightsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGemiknightsGameMode::AGemiknightsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void AGemiknightsGameMode::ParseText(const FString& Text)
{
	TArray<FString> CommandTokens{};

	// $ is command delimiter
	Text.ParseIntoArray(CommandTokens, TEXT("$"));

	int NumTokensRead{};
	for (const auto& Token : CommandTokens)
	{
		TArray<FString> CommandArgs{};
		Token.ParseIntoArray(CommandArgs, TEXT(" "));

		FString CommandKey{};
		// Even command is dialogue
		if (NumTokensRead % 2 == 0)
		{
			CommandKey = TEXT("DIALOG");
		}
		else
		{
			CommandKey = CommandArgs[0];
		}

		if (!RegisteredCommands.Contains(CommandKey))
		{
			UE_LOG(LogTemp, Error, TEXT("GK: Unregistered command encountered: %s"), *CommandKey);
			continue;
		}

		TSubclassOf<UCommandBase> CommandClass = RegisteredCommands[CommandKey];
		UCommandBase* CommandObject = NewObject<UCommandBase>(this, CommandClass);


		if (NumTokensRead % 2 == 0)
		{
			TArray<FString> DialogArgs = {Token};
			CommandObject->SetArguments(DialogArgs);
		}
		else
		{
			CommandObject->SetArguments(CommandArgs);
		}

		CurrentCommands.Add(CommandObject);

		++NumTokensRead;
	}
	ProcessNextCommand();
}

FString AGemiknightsGameMode::GetAPIKey() const
{
	FString APIKey{};
	if (GConfig)
	{
		GConfig->GetString(
			TEXT("GeminiKey"),             // Section name
			TEXT("APIKey"),              // Key name
			APIKey,                      // Output variable
			FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("Secret.ini")) // Full path to ini file
		);
	}
	return APIKey;
}

void AGemiknightsGameMode::ProcessNextCommand()
{
	if (CurrentCommands.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("GK: No commands left"));
		return;
	}

	UCommandBase* CurrentCommand = CurrentCommands[0];
	CurrentCommands.RemoveAt(0);

	UE_LOG(LogTemp, Log, TEXT("GK: Running command: %s"), *CurrentCommand->DebugPrintCommand());

	CurrentCommand->OnCommandFinished.BindUObject(this, &AGemiknightsGameMode::ProcessNextCommand);
	CurrentCommand->RunCommand(this);
}


