#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSubsystem.generated.h"

UCLASS()
class UNREALSHOOTERGAME_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	IOnlineSessionPtr SessionInterface;
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
