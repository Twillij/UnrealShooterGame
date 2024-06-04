#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

class UMainMenuWidget;

UCLASS()
class UNREALSHOOTER_API AMainMenuGameMode : public AGameMode
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

	UMainMenuWidget* GetMainMenuWidget() const { return MainMenuWidget; }
};
