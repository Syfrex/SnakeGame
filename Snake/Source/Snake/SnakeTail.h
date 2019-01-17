#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeTail.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class SNAKE_API ASnakeTail : public AActor
{
	GENERATED_BODY()
public:
	ASnakeTail();
	UFUNCTION()
		void SpawnTail();
	UFUNCTION()
		void Move(FVector Position);
	UPROPERTY()
		ASnakeTail* SnakeTail;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* MyBox;
};
