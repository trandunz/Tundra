#include "GridManager.h"

#include "GridCell.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

FVector AGridManager::GetClosestGridPosition(FVector& _inVec)
{
	if (GridArray.Num() > 0)
	{
		FVector closestPos = GridArray[0]->GetActorLocation();
		float closestDist = FVector::Distance(_inVec, GridArray[0]->GetActorLocation());

		for(auto& cell : GridArray)
		{
			if (FVector::Distance(_inVec, cell->GetActorLocation()) < closestDist)
			{
				closestDist = FVector::Distance(_inVec, cell->GetActorLocation());
				closestPos = cell->GetActorLocation();
			}
		}
		return closestPos;
	}
	return {};
}

bool AGridManager::IsGridPositionValid(FVector _inVec)
{
	//if (GridArray.Num() > 0)
	//{
	//	float closestDist = 999999.0f;
	//
	//	auto gridWithoughtHere = GridArray;
	//	
	//	for(auto& cell : GridArray)
	//	{
	//		if (FVector::Distance(_inVec, cell->GetActorLocation()) < closestDist)
	//		{
	//			closestDist = FVector::Distance(_inVec, cell->GetActorLocation());
	//		}
	//	}
//
	//	UE_LOG(LogTemp, Warning, TEXT("closestDist = %s"),  *FString::FromInt(closestDist));
	//	if (closestDist >= WorldGridSize)
	//	{
	//		return true;
	//	}
	//}
	return false;
}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	PopulateGrid();
}

void AGridManager::PopulateGrid()
{
	if (GridCellPrefab)
	{
		GridArray = {};
	
		float worldOffset = ((WorldGridSize * GridSize) * 0.5f) - (WorldGridSize* 0.5f);
		for(int i = 0; i < GridSize; i++)
		{
			for(int y = 0; y < GridSize; y++)
			{
				auto a = y * WorldGridSize;
				auto b = i * WorldGridSize;

				auto da = a - worldOffset;
				auto db = b - worldOffset;

				FVector vec {da, db, GetActorLocation().Z};

				FActorSpawnParameters params{};
				GridArray.Add(GetWorld()->SpawnActor<AGridCell>(GridCellPrefab, vec, {}));
			}
		}
	}
}

void AGridManager::CreateLines()
{
	
}

void AGridManager::CreateMaterialInstance()
{
	if (UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this))
	{
		DynMaterial->SetVectorParameterValue("Color", FLinearColor{0.6f,1.9f,0.0f});
		DynMaterial->SetScalarParameterValue("Opacity", 0.5f);
	}
}

void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

