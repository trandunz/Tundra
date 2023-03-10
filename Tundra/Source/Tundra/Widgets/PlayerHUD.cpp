#include "PlayerHUD.h"

#include "Components/Button.h"

#include "Components/TextBlock.h"
#include "Tundra/TundraCharacter.h"
#include "Tundra/TundraPlayerState.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlaceHouse->OnPressed.AddDynamic(this, &UPlayerHUD::StartHousePlacement);
}

void UPlayerHUD::StartHousePlacement()
{
	
	if (ATundraCharacter* character = Cast<ATundraCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Start House Placement") );
		character->StartPlacement(HousePrefab);
	}
}

void UPlayerHUD::UpdateMoneyText()
{
	if (MoneyText)
	{
		
		if (ATundraPlayerState* playerState = Cast<ATundraPlayerState>(GetOwningPlayerState()))
		{
			
			MoneyText->MoneyText->SetText(FText::FromString("$" + FString::FromInt(playerState->Money)));
		}
	}
}
