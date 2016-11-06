#pragma once

#ifdef _WIN32
#include <tchar.h>
#include "targetver.h"
#include <Windows.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifdef COMPILING_BLITZ_API
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#endif

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdio.h>

#include <string>
#include <vector>

#include <iostream>
