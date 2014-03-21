#include "stdafx.h"
#include "BlitzAPI.h"

void Graphics(int width, int height, int colorDepth, int modifier)
{
	if (BlitzAPI::mWindow)
	{
		// Just change resolution
	}
	else {
		// Initialise SDL.
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
		{
			W("Failed to initialize SDL! " << SDL_GetError());
			throw - 1;
		}

		switch (modifier)
		{
		case 0:	BlitzAPI::mWindow = SDL_CreateWindow("SDL Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP); break;
		case 1: BlitzAPI::mWindow = SDL_CreateWindow("SDL Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN); break;
		case 2: BlitzAPI::mWindow = SDL_CreateWindow("SDL Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_INPUT_GRABBED); break;
		}

		if (!BlitzAPI::mWindow)
		{
			W("Failed to create window! " << SDL_GetError());
			throw - 2;
		}

		BlitzAPI::mRenderer = SDL_CreateRenderer(BlitzAPI::mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!BlitzAPI::mRenderer)
		{
			W("Failed to initialize renderer! " << SDL_GetError());
			throw - 3;
		}

		SDL_GetRendererOutputSize(BlitzAPI::mRenderer, &BlitzAPI::mWidth, &BlitzAPI::mHeight);

		// Initialise font rendering
		TTF_Init();

		// Initialise Input
		BlitzAPI::InitKeyboard();

		// Initialise performance counting
		// todo: Create one base frequency per thread.
		BlitzAPI::InitTimer();
	}
}

void EndGraphics()
{
	TTF_Quit();
	SDL_DestroyRenderer(BlitzAPI::mRenderer);
	SDL_DestroyWindow(BlitzAPI::mWindow);
	SDL_Quit();
}

void Flip()
{
	SDL_RenderPresent(BlitzAPI::mRenderer);
	SDL_PumpEvents();
}

void Cls()
{
	SDL_RenderClear(BlitzAPI::mRenderer);
	SDL_PumpEvents();
}

void ClsColor(int red, int green, int blue)
{
	BlitzAPI::mClsColor.red = red;
	BlitzAPI::mClsColor.green = green;
	BlitzAPI::mClsColor.blue = blue;

	W("Warning: Overriding draw color!");
	SDL_SetRenderDrawColor(BlitzAPI::mRenderer, red, green, blue, 255);
}

void ClsColor(Colour _color)
{
	BlitzAPI::mClsColor = _color;

	W("Warning: Overriding draw color!");
	SDL_SetRenderDrawColor(BlitzAPI::mRenderer, _color.red, _color.green, _color.blue, _color.alpha);
}

void AppTitle(std::string fileName)
{
	SDL_SetWindowTitle(BlitzAPI::mWindow, fileName.c_str());
}

Uint32 millisecs()
{
	return SDL_GetTicks();
}

double ticks()
{
	return (double)(SDL_GetPerformanceCounter() / BlitzAPI::mPerformanceFrequency);
}

double fps()
{
	BlitzAPI::mNewTime = ticks();
	double t = 1000 / (BlitzAPI::mNewTime - BlitzAPI::mOldTime);
	BlitzAPI::mOldTime = BlitzAPI::mNewTime;
	
	return t;
}

namespace BlitzAPI
{
	SDL_Window* mWindow = 0;
	SDL_Renderer* mRenderer = 0;
	Colour mClsColor;
	Colour mColor;

	int mWidth = 0;
	int mHeight = 0;

	double mOldTime = 0;
	double mNewTime = 0;

	bool mLock = false;

	SDL_Color ConvertColour(const Colour &_color)
	{
		SDL_Color t;
		t.a = _color.alpha;
		t.b = _color.blue;
		t.g = _color.green;
		t.r = _color.red;

		return t;
	}

	Uint64 mPerformanceFrequency;

	void InitTimer()
	{
		mPerformanceFrequency = SDL_GetPerformanceFrequency() / 1000;
	}
}
