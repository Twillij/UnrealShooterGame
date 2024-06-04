#include "MultiplayerSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UMultiplayerSubsystem::CreateServer(const FString& ServerName)
{
	if (ServerName.IsEmpty())
	{
		return;
	}

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsDedicated = true;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bShouldAdvertise = true;
	
	SessionInterface->CreateSession(0, "TestServer", FOnlineSessionSettings());
}

void UMultiplayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		const FString OnlineSubsystemName = OnlineSubsystem->GetSubsystemName().ToString();
		UE_LOG(LogTemp, Display, TEXT("Connected to OSS: %s"), *OnlineSubsystemName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to a valid OSS."));
		return;
	}
	
	SessionInterface = OnlineSubsystem->GetSessionInterface();
}
