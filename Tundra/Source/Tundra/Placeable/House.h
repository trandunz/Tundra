#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tundra/Interfaces/PlaceableInterface.h"
#include "House.generated.h"

UCLASS()
class TUNDRA_API AHouse : public AActor, public IPlaceableInterface
{
	GENERATED_BODY()
	
public:	
	AHouse();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category=Default)
	void OnMouseClick(UPrimitiveComponent* pComponent, FKey inKey);
	UFUNCTION(Category=Default)
	void OnMouseHover(UPrimitiveComponent* TouchedComponent);
	UFUNCTION(Category=Default)
	void OnMouseHoveEnd(UPrimitiveComponent* TouchedComponent);

	virtual bool Place(int& _playerMoney) override;
	void SetGhosted(bool _isGhosted);

	void SetValidLocation(bool _isValidLocation);
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<	class UStaticMeshComponent*> OtherMeshes{};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterial* GhostMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterial* GreenGhostMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterial* StandardMaterial;
};
