#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlaceableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlaceableInterface : public UInterface
{
	GENERATED_BODY()
};

class TUNDRA_API IPlaceableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool Place(int& _playerMoney) = 0;
};
