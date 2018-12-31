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

	if (PhysicsHandle == nullptr) { return;  } /// Do nothing if there's no Physics Handle
	
	/// if the physics handle is attached move the object we are holding
	if (PhysicsHandle->GrabbedComponent) { PhysicsHandle->SetTargetLocation(GetLineTracePoints().v2); }

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
	/// Find Input Component attached to this owner
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input == nullptr) {
		/// Log error if no Input Component is found (this component is assumed to be attached)
		UE_LOG(LogTemp, Error, TEXT("%s is missing component: Input Component"), *GetOwner()->GetName());

		return;	
	}

	UE_LOG(LogTemp, Warning, TEXT("Input Component Found...Binding Actions"));

	/// Bind a method to an Input Action
	Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	return;
}

void UGrabber::Grab() {
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ActorHit = HitResult.GetActor();
	
	if (ActorHit) {
		auto TargetComponent = HitResult.GetComponent();
		PhysicsHandle->GrabComponent(TargetComponent, NAME_None, TargetComponent->GetOwner()->GetActorLocation(), true);
	}

	return;
}

void UGrabber::Release() {
	PhysicsHandle->ReleaseComponent();
	
	return;
}

// Raycast and return the first physics body it finds
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
	FTwoVectors TracePoints = GetLineTracePoints();
	/// Set up Collision Query Params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Line trace (Ray-cast) to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, TracePoints.v1, TracePoints.v2, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	return Hit;
}

FTwoVectors UGrabber::GetLineTracePoints() const {
	FVector PLocation; /// Player Location
	FRotator PRotation; /// Player Rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PLocation, OUT PRotation);
	
	FVector EndLocation = PLocation + PRotation.Vector() * Reach;
	return FTwoVectors(PLocation, EndLocation);
}