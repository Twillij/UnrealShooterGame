#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"

class UMainMenuWidget;

UCLASS()
class UNREALSHOOTER_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	UMainMenuWidget* MainMenuWidget = nullptr;
	
protected:
	virtual void BeginPlay() override;
};
