#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ASnakeTail;
UCLASS()
class SNAKE_API ACollectible : public AActor
{
	GENERATED_BODY()
		ACollectible();
public:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MyMesh;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* MyBox;
	UFUNCTION()
		void OnCollectiveOverlapp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACollectible> MyCollectible;

};
