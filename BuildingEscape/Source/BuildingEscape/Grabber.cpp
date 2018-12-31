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
	
	// Preform any initialization that needs to happen to ensure
	// the logic within this class can function as planned
	Initialize();

	return;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		/// OUT Params
		FVector PLocation;
		FRotator PRotation;

		/// Grab the player's viewpoint
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PLocation, OUT PRotation);

		/// Calculate a LineTraceEnd
		FVector LineTraceEnd = PLocation + PRotation.Vector() * Reach;
		
		/// move the object that we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

	return;
}

// Preform any actions to ensure that class is ready for use
void UGrabber::Initialize() {
	FindPhysicsHandler();
	SetupInputComponent();

	return;
}

// Find the Physics Handler attached to this owner
void UGrabber::FindPhysicsHandler() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) { UE_LOG(LogTemp, Error, TEXT("%s is missing component: Physics Handle"), *GetOwner()->GetName()); }

	return;
}

void UGrabber::SetupInputComponent() {
	// Find Input Component attached to this owner
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found...Binding Actions"));

		/// Bind a method to an Input Action
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		/// Log error
		UE_LOG(LogTemp, Error, TEXT("%s is missing component: Input Component"), *GetOwner()->GetName());
	}

	return;
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ActorHit = HitResult.GetActor();
	
	if (ActorHit) {
		auto TargetComponent = HitResult.GetComponent();
		PhysicsHandle->GrabComponent(TargetComponent, NAME_None, TargetComponent->GetOwner()->GetActorLocation(), true);
	}

	return;
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	
	PhysicsHandle->ReleaseComponent();
	
	return;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	/// OUT Params
	FVector PLocation;
	FRotator PRotation;

	/// Grab the player's viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PLocation, OUT PRotation);

	/// Calculate a LineTraceEnd
	FVector LineTraceEnd = PLocation + PRotation.Vector() * Reach;

	/// Set up Collision Query Params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Line trace (Ray-cast) to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	if (Hit.GetActor() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Ray-Cast colliding with %s"), *Hit.GetActor()->GetName());
	}

	return Hit;
}
