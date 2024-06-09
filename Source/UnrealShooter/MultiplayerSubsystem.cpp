#include "MultiplayerSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Online/OnlineSessionNames.h"

DEFINE_LOG_CATEGORY(LogMultiplayerSubsystem);

void UMultiplayerSubsystem::CreateSession_Implementation(const FName SessionName)
{
	SessionInterface->CreateSession(0, SessionName, DefaultSessionSettings);
}

bool UMultiplayerSubsystem::CreateSession_Validate(const FName SessionName)
{
	if (SessionName.IsNone())
	{
		return false;
	}
	return true;
}

void UMultiplayerSubsystem::DestroySession_Implementation(const FName SessionName)
{
	SessionInterface->DestroySession(SessionName);
}

bool UMultiplayerSubsystem::DestroySession_Validate(const FName SessionName)
{
	if (SessionName.IsNone())
	{
		return false;
	}
	return true;
}

void UMultiplayerSubsystem::FindSession(const FName SessionName)
{
	LastSessionSearch = MakeShareable(new FOnlineSessionSearch(DefaultSessionSearch));
	SessionInterface->FindSessions(0, LastSessionSearch.ToSharedRef());
}

void UMultiplayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		UE_LOG(LogMultiplayerSubsystem, Error, TEXT("Failed to connect to a valid OSS."))
		return;
	}

	// Store the name of the subsystem
	OnlineSubsystemName = OnlineSubsystem->GetSubsystemName();
	UE_LOG(LogMultiplayerSubsystem, Display, TEXT("Connected to OSS: %s"), *OnlineSubsystemName.ToString());

	// Bind delegates to the session interface
	SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (SessionInterface)
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerSubsystem::OnCreateSessionComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerSubsystem::OnDestroySessionComplete);
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerSubsystem::OnFindSessionComplete);
	}

	// Create the default settings for online sessions
	DefaultSessionSettings.bIsLANMatch = OnlineSubsystemName == "NULL";
	DefaultSessionSettings.NumPublicConnections = 2;
	DefaultSessionSettings.bIsDedicated = true;
	DefaultSessionSettings.bAllowJoinInProgress = true;
	DefaultSessionSettings.bShouldAdvertise = true;
	DefaultSessionSettings.bUseLobbiesIfAvailable = true;
	DefaultSessionSettings.bUsesPresence = true;
	DefaultSessionSettings.bAllowJoinViaPresence = true;

	// Create the default settings for online searches
	DefaultSessionSearch.bIsLanQuery = OnlineSubsystemName == "NULL";
	DefaultSessionSearch.MaxSearchResults = 64;
	DefaultSessionSearch.QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
}

void UMultiplayerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	// TODO: Need to actually check whether all players have left the session.
	for (const FName SessionName : CurrentSessionNames)
	{
		SessionInterface->DestroySession(SessionName);
	}
}

void UMultiplayerSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		CurrentSessionNames.Add(SessionName);
	}
	UE_LOG(LogMultiplayerSubsystem, Display, TEXT("Creating session \"%s\": %hs"), *SessionName.ToString(), bWasSuccessful ? "SUCCESS" : "FAILED")
}

void UMultiplayerSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		CurrentSessionNames.Remove(SessionName);
	}
	UE_LOG(LogMultiplayerSubsystem, Display, TEXT("Destroying session \"%s\": %hs"), *SessionName.ToString(), bWasSuccessful ? "SUCCESS" : "FAILED")
}

void UMultiplayerSubsystem::OnFindSessionComplete(bool bWasSuccessful)
{
	// TODO: Need to check whether this is called by the user who initiated the search
	if (GetWorld() && GetWorld()->GetNetMode() != NM_Client)
		return;
	
	if (!bWasSuccessful)
	{
		UE_LOG(LogMultiplayerSubsystem, Display, TEXT("Finding session: FAILED"))
		return;
	}
	
	UE_LOG(LogMultiplayerSubsystem, Display, TEXT("Finding session: %i result"), LastSessionSearch->SearchResults.Num());
	UE_LOG(LogMultiplayerSubsystem, Display, TEXT("Default session: %i result"), DefaultSessionSearch.SearchResults.Num());
}
