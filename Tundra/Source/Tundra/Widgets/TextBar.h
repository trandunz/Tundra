#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBar.generated.h"

class UTextBlock;
UCLASS()
class TUNDRA_API UTextBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* MoneyText;
};
