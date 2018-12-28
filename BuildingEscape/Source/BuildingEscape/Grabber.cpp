// Celio Reyes 2018

#include "Grabber.h"


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
	//UE_LOG(LogTemp, Warning, TEXT("Grabber | Player Location: %s | Player Viewpoint: %s"), *PLocation.ToString(), *PRotation.ToString());

	FVector  LineTraceEnd = PLocation + PRotation.Vector() * Reach;
	DrawDebugLine( GetWorld(), PLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 10.f );
	
	// Ray-cast to reach distance

	// Check what we hit
}

