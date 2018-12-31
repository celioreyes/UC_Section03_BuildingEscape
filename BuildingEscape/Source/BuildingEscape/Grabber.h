// Celio Reyes 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()
		
// Unreal Specific 
public:	
	// Sets default values for this component's properties
	UGrabber();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Unreal Specific 
protected: 
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	// How far ahead of the player can we reach in cm
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* Input = nullptr;
	
	// Preform any actions wanted to ensure that class is ready for use
	void Initialize();

	// Called when grab is released
	void FindPhysicsHandler();

	// Setup (assumed) attached input component
	void SetupInputComponent();
	
	// Ray-Cast and grab object in reach
	void Grab();

	// Releases the grabbed object
	void Release();

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
	
	// Returns current start and end of reach line
	FTwoVectors GetLineTracePoints() const;
};
