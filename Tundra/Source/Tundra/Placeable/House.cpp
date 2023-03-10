#include "House.h"
#include "Components/PrimitiveComponent.h"


AHouse::AHouse()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	OtherMeshes[OtherMeshes.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OtherMesh")))]->SetupAttachment(Mesh);
	OtherMeshes[OtherMeshes.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OtherMesh2")))]->SetupAttachment(Mesh);
	OtherMeshes[OtherMeshes.Add(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chimney")))]->SetupAttachment(Mesh);
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnBeginCursorOver.AddDynamic(this, &AHouse::OnMouseHover);
	Mesh->OnEndCursorOver.AddDynamic(this, &AHouse::OnMouseHoveEnd);
	Mesh->OnClicked.AddDynamic(this, &AHouse::OnMouseClick);

	for(auto& otherMesh : OtherMeshes)
	{
		otherMesh->OnBeginCursorOver.AddDynamic(this, &AHouse::OnMouseHover);
		otherMesh->OnEndCursorOver.AddDynamic(this, &AHouse::OnMouseHoveEnd);
		otherMesh->OnClicked.AddDynamic(this, &AHouse::OnMouseClick);
	}
}

void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

void AHouse::OnMouseClick(UPrimitiveComponent* pComponent, FKey inKey)
{
	UE_LOG(LogTemp, Warning, TEXT("HouseClicked") );
}

void AHouse::OnMouseHover(UPrimitiveComponent* TouchedComponent)
{
	Mesh->SetRenderCustomDepth(true);
	
	for(auto& child : OtherMeshes)
	{
		child->SetRenderCustomDepth(true);
	}
}

void AHouse::OnMouseHoveEnd(UPrimitiveComponent* TouchedComponent)
{
	Mesh->SetRenderCustomDepth(false);
	for(auto& child : OtherMeshes)
	{
		child->SetRenderCustomDepth(false);
	}
}

bool AHouse::Place(int& _playerMoney)
{
	if (_playerMoney >= 100)
	{
		SetGhosted(false);
		_playerMoney -= 100;
		return true;
	}

	return false;
}

void AHouse::SetGhosted(bool _isGhosted)
{
	if (_isGhosted && GhostMaterial)
	{
		Mesh->SetMaterial(0, GhostMaterial);

		for(auto& otherMesh : OtherMeshes)
		{
			otherMesh->SetMaterial(0, GhostMaterial);
		}
	}
	else if (StandardMaterial)
	{
		Mesh->SetMaterial(0, StandardMaterial);

		for(auto& otherMesh : OtherMeshes)
		{
			otherMesh->SetMaterial(0, StandardMaterial);
		}
	}
}

void AHouse::SetValidLocation(bool _isValidLocation)
{
	if (_isValidLocation && GreenGhostMaterial)
	{
		Mesh->SetMaterial(0, GreenGhostMaterial);

		for(auto& otherMesh : OtherMeshes)
		{
			otherMesh->SetMaterial(0, GreenGhostMaterial);
		}
	}
}

