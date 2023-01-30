// Copyright Epic Games, Inc. All Rights Reserved.

#include "TundraGameMode.h"
#include "TundraCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATundraGameMode::ATundraGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
