// Celio Reyes 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
	Super::BeginPlay();
	
	Owner = GetOwner(); // Find owning actor aka the door

	return;
}

void UOpenDoor::OpenDoor() {
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f)); // Open Door

	return;
}

void UOpenDoor::CloseDoor() {
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f)); // Open Door

	return;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CalculateTotalMassOnPlate() > 50.f) { // If TargetActor is in volume
		OpenDoor();
		TimeLastOpen = GetWorld()->GetTimeSeconds();
	}

	if ((GetWorld()->GetTimeSeconds() - TimeLastOpen) > CloseDelay) {
		// Close
		CloseDoor();
	}

	return;
}

float UOpenDoor::CalculateTotalMassOnPlate() const {
	float TotalMass = 40.f;
	

	/// Find all overlapping actors
	TArray<AActor*> Actors;
	PressurePlate->GetOverlappingActors(OUT Actors);
	
	/// Loop and sum all masses

	return TotalMass;
}
