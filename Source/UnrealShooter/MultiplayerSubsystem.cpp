#include "MultiplayerSubsystem.h"

void UMultiplayerSubsystem::ConnectToServer(APlayerController* Client, const FString& IpAddress, const ETravelType TravelType)
{
	Client->ClientTravel(IpAddress, TravelType);
}
