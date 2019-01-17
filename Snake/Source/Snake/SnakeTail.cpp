#include "SnakeTail.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/World.h"
#include "Class.h"

ASnakeTail::ASnakeTail()
{
	PrimaryActorTick.bCanEverTick = true;
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Tail"));
	RootComponent = MyBox;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MyMesh->SetupAttachment(RootComponent);
	SnakeTail = nullptr;
}

void ASnakeTail::SpawnTail()
{
	if (SnakeTail != nullptr)
		SnakeTail->SpawnTail();
	else
		SnakeTail = GetWorld()->SpawnActor<ASnakeTail>(GetClass(), GetActorLocation(), FRotator(0));
}

void ASnakeTail::Move(FVector Position)
{
	if (SnakeTail != nullptr)
		SnakeTail->Move(GetActorLocation());
	this->SetActorLocation(Position);
}


