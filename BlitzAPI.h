#include "stdafx.h"
#pragma once

#define W(x) std::cout << x << std::endl;

#define BACKBUFFER 0x1
#define FRONTBUFFER 0x2
#define Point SDL_Point

/*
 Compability hack for Win32. Why is everything from windows thrown into ::* by default again?
 */
#ifdef LoadImage
#undef LoadImage
#endif

/*
Custom Datatypes
*/

// Colour-Struct which supports alpha-values.
struct Colour 
{
	Colour() : red(255), green(255), blue(255), alpha(255)
	{
	}
	
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;
};

// Image. Is automatically freed when it goes out of scope if ENABLE_DESTRUCTION is defined.
struct Image
{
#ifdef ENABLE_DESTRUCTION
	~Image()
	{
		if (img)
			SDL_DestroyTexture(img);
	}
#endif
	
	Image() : img(NULL), x(0), y(0)
	{
	}

	SDL_Texture* img;
	int x;
	int y;
};

struct Font
{
	TTF_Font* font;
	bool bold;
	bool italic;
	bool underline;
	int size;
};

/*
	Graphics 2D: 2D API Set
*/

/*
	Initializes Graphics and sets the mode.
	This will also initialise SDL when not done previously.
	Modifier specifies the current mode:
		- 0: Fullscreen at the current desktop resolution
		- 1: Fullscreen
		- 2: Windowed
*/
void Graphics(int width, int height, int colorDepth = 32, int modifier = SDL_RENDERER_ACCELERATED);

/*
	Exits the graphicmode and frees up SDL and all resources.
*/
void EndGraphics();

/*
	Changes the active buffer mode.
	Possible modes: FRONTBUFFER and BACKBUFFER.
	BackBuffer is the default, use Flip() to display the current buffer.
*/
void SetBuffer(char BufferMode = BACKBUFFER);

/*
	Loads an image directly into the currently active buffer and frees it afterwards, so it should be used only
	to display images one time.
*/
void LoadBuffer(std::string fileName);

/*
	Saves the currently active buffer to an image file --> Screenshot e.g.
	Currently only BMP is supported.
*/
void SaveBuffer(std::string fileName);

/*
	Restricts all drawing operations to the given viewport. To undo it,
	just issue a DisableViewport().
*/
void Viewport(int x, int y, int width, int height);

/*
	Disable the restrictions created by Viewport(). Use this to use the full
	resolution again.
*/
void DisableViewport();

/*
	Sets the origin for all further drawing operations, so after this command all coordinates will be offsets
	of the given coordinats.
	To undo this, issue a ResetOrigin();
*/
void Origin(int x, int y);

/*
	Resets the origin to the default upper left of the screen (0/0).
*/
void ResetOrigin();

/*
	Swaps out Front- and Backbuffer, so the Backbuffer will be displayed.
*/
void Flip();

/*
	Clears the current buffer
*/
void Cls();

/*
	Sets the color Cls() uses. Default RGB.
*/
void ClsColor(int red, int green, int blue);
void ClsColor(Colour _color);

/*
	Sets the color used for all drawing operations (text, rect, line, cls)
*/
void Color(int red, int green, int blue);
void Color(Colour _color);

/*
	Loads an image from disk and returns the image-object.
	The created object can be freed again by using 
*/
Image LoadImage(std::string fileName);

/*
	Removes the given image from memory.
*/
void FreeImage(Image _image);

/*
	Draws the given image on the current buffer.
*/
void DrawImage(const Image &_image, int x, int y);

/*
	Tiles a image across the current buffer. Use x and y as an offset if you want.
*/
void TileImage(const Image &_image, int x = 0, int y = 0);

/*
	Does not actually lock the buffer but enables queuing of drawing operations which
	will increase performance for multiple operations dramatically.
	Keep in mind that you will need to unlock the buffer again to see any effect!
*/
void LockBuffer();

/*
	See LockBuffer(). This functions "unlocks" the buffer again and executes all queued drawing operations.
*/
void UnlockBuffer();

/*
	Draws a point at the given coordinates.
	If you want to draw multiple points, consider using LockBuffer() beforehand
	to improve performance.
*/
void Plot(int x, int y);
void Plot(Point _point);

/*
	Start- and endpoint of the line. When the current buffer is locked, all lines will be
	created connected.
*/
void Line(int x, int y, int x2, int y2);
void Line(Point p1, Point p2);

/*
	Draws a rectangle on the current buffer. If you want to draw multiple rectangles,
	consider using LockBuffer() beforehand to improve the performance.
*/
void Rect(int x, int y, int w, int h);
void Rect(SDL_Rect _rect);

/*
	Sets the window title.
*/
void AppTitle(std::string title);

/*
	Prints text.
*/
void Print(std::string text);

/*
	Loads the font "fontName" with the given parameters.
*/
Font LoadFont(std::string fontName, int size, bool bold = false, bool italic = false, bool underlined = false);

/*
	Frees a font.
*/
void FreeFont(const Font &_font);

/*
	Creates an Image from the given text. This is a faster alternative to Text() when you want to draw the same
	text more than once. Improves performance.
*/
Image TextImage(std::string text);

/*
	Sets the currently active font.
*/
void SetFont(const Font &_font);

/*
	Draws the text at the given coordinates. Keep in mind that if you want to draw a text multiple times (e.g. each frame),
	you should use TextImage() to improve performance.
*/
void Text(int x, int y, std::string text, bool center_x = false, bool center_y = false);

/*
	Returns wether a certain key is beeing held down. Differently from BB this function takes SDL_SCANCODE_??? as parameter.
	Keep in mind that the internal keystate array is updated on Cls(), Flip() and UpdateWorld() only, so keys pressed between the
	calls can be missed out.
	If you want to wait for a certain event, use WaitKey() instead.
*/
bool KeyDown(SDL_Scancode scancode);

/*
	Want to offer rebindable keys? This function returns a human readable name for a given scancode so you can
	use it in your menu.
*/
std::string KeyName(SDL_Scancode scancode);

/*
	Returns the time since Graphics() was called in milliseconds. The resolution should be enough for 1/1000s, for more accurate
	results for profiling (down to times between single API-calls) consider using ticks() instead.
*/
Uint32 millisecs();

/*
	Returns a high resolution time for profiling. The actual resolution may vary due to energy saving features of the
	processor. If you just want to measure frametimes, fps or other simple times, consider using millisecs() instead.

	The time returned is in milliseconds, so a value of 0.001 means that about one microsecond has passed.
*/
double ticks();

/*
	Returns the current fps in high precision form. Keep in mind that this function measures delta-times, so that
	you need to call the function at least twice. The first call after Graphics() may return invalid fps, so you aren't doing
	anything wrong.
*/
double fps();

/*
	Returns wether time A has passed time B.
*/
#define TimeElapsed SDL_TICKS_PASSED

/*
	Originally meant for the 3D-Part. Use it to process window events when you don't want to update your screen using
	Flip() or Cls().
*/
void UpdateWorld();


/*
	----- BlitzAPI-Namespace is used for internal variables -----
*/
namespace BlitzAPI
{
	extern SDL_Window* mWindow;
	extern SDL_Renderer* mRenderer;
	extern Colour mClsColor;

	extern int mWidth;
	extern int mHeight;

	extern bool mLock;

	extern std::vector<Point> mQueuedPoints;
	extern std::vector<Point> mQueuedLines;
	extern std::vector<SDL_Rect> mQueuedRects;

	extern Font mFont;
	extern Colour mColor;

	extern const Uint8* mKeyboardState;
	void InitKeyboard();

	void FlushLines();
	void FlushRects();
	void FlushPoints();

	SDL_Color ConvertColour(const Colour &_color);

	extern Uint64 mPerformanceFrequency;
	void InitTimer();
	extern double mOldTime;
	extern double mNewTime;
}