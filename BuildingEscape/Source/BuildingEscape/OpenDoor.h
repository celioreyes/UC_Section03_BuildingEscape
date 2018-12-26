// Celio Reyes 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent 
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

private:
	// Will be visible in Unreal Editor
	UPROPERTY(EditAnywhere)
	float OpenAngle = 75.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	UPROPERTY(EditAnywhere)
	AActor* TargetActor;

	// Won't be visible in Unreal Editor
	AActor* Owner;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};