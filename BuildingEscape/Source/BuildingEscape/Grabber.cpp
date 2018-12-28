// Celio Reyes 2018

#include "Grabber.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();
		
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandler == nullptr) {
		/// Log error
		UE_LOG(LogTemp, Error, TEXT("%s is missing component: Physics Handle"), *GetOwner()->GetName());
	}

	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found"));
		/// Bind a method to an Input Action
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	} else {
		/// Log error
		UE_LOG(LogTemp, Error, TEXT("%s is missing component: Input Component"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// OUT Params
	FVector PLocation;
	FRotator PRotation;

	/// Grab the player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PLocation, OUT PRotation);

	FVector  LineTraceEnd = PLocation + PRotation.Vector() * Reach;
	DrawDebugLine( GetWorld(), PLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 10.f );
	
	/// Set up Collision Query Params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	/// Line trace (Ray-cast) to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

