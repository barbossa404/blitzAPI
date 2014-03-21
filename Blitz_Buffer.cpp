#include "stdafx.h"
#include "BlitzAPI.h"

void LockBuffer()
{
	if (BlitzAPI::mLock)
	{
		W("Warning: Buffer is already locked!");
	}
	else {
		BlitzAPI::mLock = true;
	}
}

void UnlockBuffer()
{
	if (BlitzAPI::mLock)
	{
		BlitzAPI::FlushPoints();
		BlitzAPI::FlushRects();
		BlitzAPI::FlushLines();

		BlitzAPI::mLock = false;
	}
	else {
		W("Warning: Buffer was not locked!")
	}
}

void SaveBuffer(std::string fileName)
{
	W("Not implemented.");
}

void LoadBuffer(std::string fileName)
{
	SDL_Texture* img = NULL;

	// Define fullscreen rect to draw to
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.h = BlitzAPI::mHeight;
	rect.w = BlitzAPI::mWidth;

	// Load image from disk. In case it does not exist, SDL will use a blank image instead.
	img = IMG_LoadTexture(BlitzAPI::mRenderer, fileName.c_str());

	// Copy the image to the buffer
	SDL_RenderCopy(BlitzAPI::mRenderer, img, NULL, &rect);

	// Free the texture
	SDL_DestroyTexture(img);
}