#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "House.generated.h"

UCLASS()
class TUNDRA_API AHouse : public AActor
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<	class UStaticMeshComponent*> OtherMeshes{};
};
