#include "MyGameMode.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "MYGameState.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
}