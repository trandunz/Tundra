#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCell.h"

#include "GridManager.generated.h"

UCLASS()
class TUNDRA_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridManager();

	UFUNCTION()
	FVector GetClosestGridPosition(FVector& _inVec);

	UFUNCTION()
	bool IsGridPositionValid(FVector _inVec);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void PopulateGrid();

	UFUNCTION()
	void CreateLines();

	UFUNCTION()
	void CreateMaterialInstance();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AGridCell> GridCellPrefab;
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int GridSize = 10;

	UPROPERTY(EditAnywhere)
	int WorldGridSize = 1000;

	UPROPERTY(EditAnywhere)
	TArray<AGridCell*> GridArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UProceduralMeshComponent* ProceduralMesh;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* Material;
};
