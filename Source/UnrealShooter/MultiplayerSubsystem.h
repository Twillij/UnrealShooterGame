#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerSubsystem, Display, All);

UCLASS()
class UNREALSHOOTER_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	FOnlineSessionSettings DefaultSessionSettings;
	FOnlineSessionSearch DefaultSessionSearch;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FName OnlineSubsystemName = NAME_None;
	
	IOnlineSessionPtr SessionInterface = nullptr;
	TArray<FName> CurrentSessionNames;

public:
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void CreateSession(const FName SessionName);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void DestroySession(const FName SessionName);

	UFUNCTION(BlueprintCallable)
	void FindSession(const FName SessionName);
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
};
