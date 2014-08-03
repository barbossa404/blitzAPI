#include "stdafx.h"
#include "BlitzAPI.h"

bool KeyDown(SDL_Scancode scancode, bool forceUpdate)
{
    if (forceUpdate)
        UpdateWorld();
    
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

void WaitKey()
{
    /* An SDL_Event */
    SDL_Event event;
 
    while (true)
    {
        SDL_WaitEvent(&event);

        /* If a quit event has been sent */
        if ((event.type == SDL_KEYDOWN) || (event.type == SDL_QUIT))
            return;
    }
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
