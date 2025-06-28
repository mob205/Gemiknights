// Copyright Epic Games, Inc. All Rights Reserved.

#include "GemiknightsGameMode.h"
#include "GemiknightsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGemiknightsGameMode::AGemiknightsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
