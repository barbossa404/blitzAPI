#include "stdafx.h"
#include "BlitzAPI.h"

void Print(std::string text)
{
	W(text);
}

void Text(int x, int y, std::string text, bool center_x, bool center_y)
{
	Image t = TextImage(text);
	SDL_Rect rect;

	if (center_x)
		rect.x = (x - t.x / 2);
	else
		rect.x = x;

	if (center_y)
		rect.y = (y - t.y / 2);
	else
		rect.y = y;

	rect.w = t.x;
	rect.h = t.y;

	SDL_RenderCopy(BlitzAPI::mRenderer, t.img, NULL, &rect);
}

Font LoadFont(std::string fontName, int size, bool bold, bool italic, bool underlined)
{
	if (!BlitzAPI::dataPath.empty())
		fontName = BlitzAPI::dataPath + fontName;

	// Load the font
	Font t;
	t.font = TTF_OpenFont(fontName.c_str(), size);

	if (t.font == NULL)
	{
		W("Could not load font " << fontName);
		throw - 3;
	}

	// Set the font style correctly
	int flags = TTF_STYLE_NORMAL;

	if (bold)
		flags = flags | TTF_STYLE_BOLD;
	if (italic)
		flags = flags | TTF_STYLE_ITALIC;
	if (underlined)
		flags = flags | TTF_STYLE_UNDERLINE;

	TTF_SetFontStyle(t.font, flags);

	// Cache the settings
	t.bold = bold;
	t.italic = italic;
	t.underline = underlined;
	t.size = size;

	return t;
}

void FreeFont(const Font &_font)
{
	TTF_CloseFont(_font.font);
}

Image TextImage(const std::string& text)
{
	// The surface is required to create the texture
	Image t;
	SDL_Surface* s;

	// Render the text as surface. Blended is the mode with the highest quality, which is the slowest mode as well.
	s = TTF_RenderText_Blended(BlitzAPI::mFont.font, text.c_str(), BlitzAPI::ConvertColour(BlitzAPI::mColor));
	t.img = SDL_CreateTextureFromSurface(BlitzAPI::mRenderer, s);
	SDL_QueryTexture(t.img, NULL, NULL, &t.x, &t.y);

	// Clean up the surface
	SDL_FreeSurface(s);

	return t;
}

void SetFont(const Font &_font)
{
	BlitzAPI::mFont = _font;
}

namespace BlitzAPI
{
	Font mFont;
}