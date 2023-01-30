#include "TundraGameMode.h"
#include "TundraCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATundraGameMode::ATundraGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
