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
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
	Super::BeginPlay();
	
	Owner = GetOwner(); /// Find owning actor aka the door
	
	/// make sure that a trigger volume is set on the door
	if (PressurePlate == nullptr) { UE_LOG(LogTemp, Error, TEXT("%s is missing pressure plate (Trigger Volume)"), *Owner->GetName()); }
	return;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CalculateTotalMassOnPlate() >= MassToOpen) { 
		OnOpen.Broadcast();
	} else {
		OnClose.Broadcast();
	}

	return;
}

float UOpenDoor::CalculateTotalMassOnPlate() const {
	float TotalMass = 0.f;

	if (PressurePlate == nullptr) { return TotalMass; } /// No Trigger Volume? Just return

	/// Find all overlapping actors
	TArray<AActor*> Actors;
	PressurePlate->GetOverlappingActors(OUT Actors);
	
	/// Loop and sum all masses
	for (const auto& Actor : Actors) {
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());

		/// Sum the total mass of actors on the pressure plate
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
