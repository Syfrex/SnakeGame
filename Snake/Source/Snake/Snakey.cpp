#include "Snakey.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/World.h"
#include "Collectible.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ASnakey::ASnakey()
{
	PrimaryActorTick.bCanEverTick = true;
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HEAD"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = MyBox;
	MyMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	MyMesh->SetupAttachment(MyBox);
	MyMesh->OnComponentBeginOverlap.AddDynamic(this, &ASnakey::OnCollectiveOverlapp);
}
void ASnakey::BeginPlay()
{
	Super::BeginPlay();
	Cooldown = MaxCD;
	MyMesh->SetWorldScale3D(MyBox->GetComponentScale());
}
void ASnakey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMovement(DeltaTime);
}
void ASnakey::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("TurnRight", IE_Pressed, this, &ASnakey::TurnRight);
	PlayerInputComponent->BindAction("TurnLeft", IE_Pressed, this, &ASnakey::TurnLeft);
}

void ASnakey::HandleMovement(float delta)
{
	if (Cooldown > 0)
		Cooldown -= delta;
	if (Cooldown <= 0)
	{
		LastPos = GetActorLocation();
		this->AddActorWorldOffset(this->GetActorForwardVector() * 100);
		if (NextTail != nullptr)
			NextTail->Move(LastPos);
		Cooldown = MaxCD;
	}
}
void ASnakey::TurnRight()
{
	this->AddActorWorldRotation(FRotator(0, 90, 0));
}

void ASnakey::TurnLeft()
{
	this->AddActorWorldRotation(FRotator(0, -90, 0));
}

void ASnakey::SpawnTail()
{
	if (NextTail != nullptr)
		NextTail->SpawnTail();
	else
		NextTail = GetWorld()->SpawnActor<ASnakeTail>(MySnakeTail, LastPos, FRotator(0));
}

void ASnakey::OnCollectiveOverlapp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != NextTail && !OtherActor->IsA<ACollectible>() && OtherActor->GetName() != "SpectatorPawn_0" && OtherActor->GetName() != "BP_Snakey_C_0") // By some reason, it collides with spectatorpawn and bp_snake_C_0.. I have no idea what that is
		UGameplayStatics::OpenLevel(GetWorld(), "?Restart");
}

