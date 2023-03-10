#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TundraPlayerState.generated.h"

UCLASS()
class TUNDRA_API ATundraPlayerState : public APlayerState
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Money{200};
};
