#include "MainMenuGameMode.h"
#include "Widgets/MainMenuWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	MainMenuWidget = NewObject<UMainMenuWidget>(this);
}
