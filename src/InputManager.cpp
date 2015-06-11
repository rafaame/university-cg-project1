#include "InputManager.h"
#include "TimeManager.h"

void InputManager::KeyPressed(InputCodes code)
{
	
	if(Camera == nullptr)
		return;

	
	switch(code)
	{

		case Up:
		case W:
		case w:

			Camera->MoveCamera(Camera->GetSpeed() * TimeManager::Instance().DeltaTime);

			break;
		
		case Down:
		case S:
		case s:

			Camera->MoveCamera(-1 * Camera->GetSpeed() * TimeManager::Instance().DeltaTime);

			break;		

	}

}

void InputManager::MouseMoved(float mouseX, float mouseY)
{
	
	if(Camera == nullptr)
		return;
	
	Camera->SetViewByMouse(mouseX, mouseY);

}