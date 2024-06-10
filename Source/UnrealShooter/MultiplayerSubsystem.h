#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerSubsystem, Display, All);

UCLASS()
class UNREALSHOOTER_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void ConnectToServer(APlayerController* Client, const FString& IpAddress, const ETravelType TravelType = TRAVEL_Relative);
	
protected:
	//virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//virtual void Deinitialize() override;
};
