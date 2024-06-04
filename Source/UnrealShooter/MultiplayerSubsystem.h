#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSubsystem.generated.h"

UCLASS()
class UNREALSHOOTER_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	IOnlineSessionPtr SessionInterface;

public:
	UFUNCTION(BlueprintCallable)
	void CreateServer(const FString& ServerName);
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
