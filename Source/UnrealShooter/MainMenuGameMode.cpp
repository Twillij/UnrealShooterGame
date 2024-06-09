#include "MainMenuGameMode.h"
#include "MainMenuController.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	PlayerControllerClass = AMainMenuController::StaticClass();
}
