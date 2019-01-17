#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SubclassOf.h"
#include "SnakeTail.h"
#include "Snakey.generated.h"

class ASnakeTail;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SNAKE_API ASnakey : public APawn
{
	GENERATED_BODY()
public:

	ASnakey();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleMovement(float delta);
	void TurnRight();
	void TurnLeft();
	void SpawnTail();
	UFUNCTION()
		void OnCollectiveOverlapp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY()
		float MaxCD = 0.5f;
	UPROPERTY()
		float Cooldown;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeTail> MySnakeTail;
	UPROPERTY()
		FVector LastPos;
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* MyBox;
	UPROPERTY()
		ASnakeTail* NextTail;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* MyMesh;
};
