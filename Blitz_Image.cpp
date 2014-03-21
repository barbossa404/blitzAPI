#include "stdafx.h"
#include "BlitzAPI.h"

Image LoadImage(std::string fileName)
{
	Image t;
	t.img = IMG_LoadTexture(BlitzAPI::mRenderer, fileName.c_str());

	SDL_QueryTexture(t.img, NULL, NULL, &t.x, &t.y);

#ifndef DISABLE_LOGGING
	if ((!t.x) || (!t.y))
	{
		W("Failed to load image " << fileName << ".");
	}
	else{
		W("Loaded Image with " << t.x << "x" << t.y << " from file " << fileName);
	}
#endif

	return t;
}

void FreeImage(Image _image)
{
	SDL_DestroyTexture(_image.img);
	_image.img = NULL;
}

void DrawImage(const Image &_image, int x, int y)
{
	// Construct the rectangle to draw to
	SDL_Rect rect;
	rect.w = _image.x;
	rect.h = _image.y;
	rect.x = x;
	rect.y = y;

	// Copy the texture to the buffer
	SDL_RenderCopy(BlitzAPI::mRenderer, _image.img, NULL, &rect);
}

void TileImage(const Image &_image, int x, int y)
{
	for (int i = 0; i < BlitzAPI::mWidth; i += _image.x)
	{
		for (int ii = 0; ii < BlitzAPI::mHeight; ii += _image.y)
			DrawImage(_image, i, ii);
	}
}