// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/Queue.h"
#include "CommandBase.h"
#include "GemiknightsGameMode.generated.h"


UCLASS(minimalapi)
class AGemiknightsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGemiknightsGameMode();

	UFUNCTION(BlueprintCallable)
	void ParseText(const FString& Text);

	UFUNCTION(BlueprintCallable)
	FString GetAPIKey() const;

protected:
	UPROPERTY(EditAnywhere)
	TMap<FString, TSubclassOf<UCommandBase>> RegisteredCommands{};

private:
	UPROPERTY()
	TArray<TObjectPtr<UCommandBase>> CurrentCommands{};

	void ProcessNextCommand();
};



