#include "Collectible.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "UnrealMathUtility.h"
#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"
#include "Snakey.h"

ACollectible::ACollectible()
{
	PrimaryActorTick.bCanEverTick = true;
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collect"));
	RootComponent = MyBox;
	MyBox->SetCollisionProfileName(TEXT("OverlapAll"));
	MyBox->Mobility = EComponentMobility::Stationary;
	MyBox->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::OnCollectiveOverlapp);
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MyMesh->SetupAttachment(RootComponent);
	
}

void ACollectible::OnCollectiveOverlapp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<ASnakey>())
	{
		UWorld* world = GetWorld();
		Cast<ASnakey>(OtherActor)->SpawnTail();
		if (Cast<ASnakey>(OtherActor)->MaxCD > 0.2f)
		{
			Cast<ASnakey>(OtherActor)->MaxCD -= 0.05f;
		}
		ACollectible* collectible = world->SpawnActor<ACollectible>(MyCollectible, FVector(FMath::Rand() % 2000, FMath::Rand() % 2000, 80), FRotator(0));
		Destroy(this);
	}
}

