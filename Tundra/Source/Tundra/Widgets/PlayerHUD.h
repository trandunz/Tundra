#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tundra/Widgets/TextBar.h"
#include "PlayerHUD.generated.h"

class UButton;
UCLASS()
class TUNDRA_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Placeables, meta = (AllowPrivateAccess))
	TSubclassOf<AActor> HousePrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Buttons, meta = (BindWidget))
	UButton* PlaceHouse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Buttons, meta = (BindWidget))
	UTextBar* MoneyText;
public:
	UFUNCTION(BlueprintCallable)
	void StartHousePlacement();

	UFUNCTION(BlueprintCallable)
	void UpdateMoneyText();
};
