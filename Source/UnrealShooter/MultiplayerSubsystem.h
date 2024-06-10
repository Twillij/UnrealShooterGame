#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerSubsystem, Display, All);

UCLASS()
class UNREALSHOOTER_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	//virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//virtual void Deinitialize() override;
};
