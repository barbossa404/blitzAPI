#include "stdafx.h"
#include "BlitzAPI.h"

void Color(int red, int green, int blue)
{
	SDL_SetRenderDrawColor(BlitzAPI::mRenderer, red, green, blue, 255);
	BlitzAPI::mColor.red = red;
	BlitzAPI::mColor.green = green;
	BlitzAPI::mColor.blue = blue;
}

void Color(Colour _color)
{
	SDL_SetRenderDrawColor(BlitzAPI::mRenderer, _color.red, _color.green, _color.red, _color.alpha);
	BlitzAPI::mColor = _color;
}

void Plot(int x, int y)
{
	if (BlitzAPI::mLock)
	{
		// Create point
		SDL_Point t;
		t.x = x;
		t.y = y;
		// Queue it
		BlitzAPI::mQueuedPoints.push_back(t);
	}
	else {
		// Directly draw a point
		SDL_RenderDrawPoint(BlitzAPI::mRenderer, x, y);
	}
}

void Plot(Point _point)
{
	if (BlitzAPI::mLock)
	{
		// Queue it
		BlitzAPI::mQueuedPoints.push_back(_point);
	}
	else {
		// Directly draw a point
		SDL_RenderDrawPoint(BlitzAPI::mRenderer, _point.x, _point.y);
	}
}

void Line(int x, int y, int x2, int y2)
{
	if (BlitzAPI::mLock)
	{
		Point p, p2;
		p.x = x;
		p.y = y;
		p2.x = x2;
		p2.y = y2;

		BlitzAPI::mQueuedLines.push_back(p);
		BlitzAPI::mQueuedLines.push_back(p2);
	}
	else {
		// Directly draw the line
		SDL_RenderDrawLine(BlitzAPI::mRenderer, x, y, x2, y2);
	}
}

void Line(Point p1, Point p2)
{
	if (BlitzAPI::mLock)
	{
		BlitzAPI::mQueuedLines.push_back(p1);
		BlitzAPI::mQueuedLines.push_back(p2);
	}
	else {
		// Directly draw the line
		SDL_RenderDrawLine(BlitzAPI::mRenderer, p1.x, p1.y, p2.x, p2.y);
	}
}

void Rect(int x, int y, int w, int h)
{
	SDL_Rect _rect;
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;

	if (BlitzAPI::mLock)
	{
		BlitzAPI::mQueuedRects.push_back(_rect);
	}
	else {
		// Draw directly
		SDL_RenderDrawRect(BlitzAPI::mRenderer, &_rect);
	}
}

void Rect(SDL_Rect _rect)
{
	if (BlitzAPI::mLock)
	{
		BlitzAPI::mQueuedRects.push_back(_rect);
	}
	else {
		// Draw directly
		SDL_RenderDrawRect(BlitzAPI::mRenderer, &_rect);
	}
}

void Viewport(int x, int y, int width, int height)
{
	SDL_Rect t;
	t.x = x;
	t.y = y;
	t.w = width;
	t.h = height;

	SDL_RenderSetViewport(BlitzAPI::mRenderer, &t);
}

void DisableViewport()
{
	SDL_RenderSetViewport(BlitzAPI::mRenderer, NULL);
}

namespace BlitzAPI
{
	void FlushPoints()
	{
		if (!mQueuedPoints.empty())
		{
			SDL_RenderDrawPoints(mRenderer, mQueuedPoints.data(), mQueuedPoints.size());
			mQueuedPoints.clear();
		}
	}

	void FlushRects()
	{
		if (!mQueuedRects.empty())
		{
			SDL_RenderDrawRects(mRenderer, mQueuedRects.data(), mQueuedRects.size());
			mQueuedRects.clear();
		}
	}

	void FlushLines()
	{
		if (!mQueuedLines.empty())
		{
			SDL_RenderDrawLines(mRenderer, mQueuedLines.data(), mQueuedLines.size());
			mQueuedLines.clear();
		}
	}

	std::vector<Point> mQueuedPoints;
	std::vector<Point> mQueuedLines;
	std::vector<SDL_Rect> mQueuedRects;

}