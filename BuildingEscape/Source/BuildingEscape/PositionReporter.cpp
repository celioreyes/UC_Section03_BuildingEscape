// © Celio Reyes 2018

#include "PositionReporter.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPositionReporter::BeginPlay() {
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName(); // Grab the name of the current GameObject
	FString ObjectPos = GetOwner()->GetActorLocation().ToString(); // Gets the Vector location of current GameObject
	UE_LOG(LogTemp, Warning, TEXT("%s at %s"), *ObjectName, *ObjectPos);

}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
