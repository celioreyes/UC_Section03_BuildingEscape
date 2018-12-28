// Celio Reyes 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber | Running in BeginPlay()"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// OUT Params
	FVector PLocation;
	FRotator PRotation;

	// Grab the player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PLocation, OUT PRotation);
	UE_LOG(LogTemp, Warning, TEXT("Grabber | Player Location: %s | Player Viewpoint: %s"), *PLocation.ToString(), *PRotation.ToString());

	// Ray-cast to reach distance

	// Check what we hit
}

