#include "MainMenuController.h"
#include "Widgets/MainMenuWidget.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		MainMenuWidget = Cast<UMainMenuWidget>(CreateWidget(this, MainMenuWidgetClass));
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
