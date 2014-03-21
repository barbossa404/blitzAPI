#include "stdafx.h"
#include "BlitzAPI.h"

bool KeyDown(SDL_Scancode scancode)
{
	if (BlitzAPI::mKeyboardState[scancode])
		return true;
	else
		return false;
}

void UpdateWorld()
{
	// Only processes events for now.
	SDL_PumpEvents();
}

std::string KeyName(SDL_Scancode scancode)
{
	std::string t(
		SDL_GetKeyName(
			SDL_GetKeyFromScancode(scancode)
		));

	return t;
}

namespace BlitzAPI
{
	const Uint8* mKeyboardState;

	void InitKeyboard()
	{
		mKeyboardState = SDL_GetKeyboardState(NULL);
		if (mKeyboardState == NULL)
		{
			W("Error: Could not get KeyboardState!");
		}
	}
}