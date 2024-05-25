// Copyright (c) 2024, CatRunner All Rights Reserved.

#include "GameMode/RunGameMode.h"
#include "Cat/CatCharacter.h"
#include "Data/StageLevelTableRow.h"
#include "Kismet/GameplayStatics.h"
#include "Stage/StageGenerator.h"
#include "UObject/ConstructorHelpers.h"

ARunGameMode::ARunGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Cat/BP_Cat"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// enabled tick function.
	PrimaryActorTick.bCanEverTick = false;
}
