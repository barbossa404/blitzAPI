#include "stdafx.h"
#include "BlitzAPI.h"

#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#else 
int main()
#endif
{
	Graphics(1280, 720, 32, 0);

	Color(255, 255, 255);

	//LoadBuffer("test.jpg");
	Image img = LoadImage("../Media/test.jpg");
	Image img2 = LoadImage("../Media/test2.jpg");
	int img2_x = 10;
	bool reverse = false;

	AppTitle("Hello World!");

	Font arial = LoadFont("../Media/Fonts/SourceCodePro-Regular.ttf", 30, false, false, false);
	SetFont(arial);
	Image t = TextImage("TExt!");
	Image t2 = TextImage("Press <" + KeyName(SDL_SCANCODE_ESCAPE) + "> to exit.");

	while (true)
	{
		TileImage(img);

		LockBuffer();
		for (int i = 1; i < 1000; i++)
		{
			Plot(100 + i, 100);
		}
		UnlockBuffer();

		DrawImage(t, 100, 100);
		DrawImage(t2, 600, 600);
		Text(10, 10, "Shit.");

		if (KeyDown(SDL_SCANCODE_ESCAPE))
			break;
		if (KeyDown(SDL_SCANCODE_SPACE))
			Text(10, 650, "Stop pressing the spacebar!");

		if ((img2_x < 1000) && (!reverse))
		{
			img2_x++;
		}
		else if ((img2_x > 1000) && (!reverse)) {
			reverse = true;
			img2_x--;
		}
		else {
			if (img2_x < 15)
			{
				reverse = false;
			}
			img2_x--;
		}
		DrawImage(img2, img2_x, 300);

		// Timing test
#ifdef _WIN32
		// std::to_string is currently broken in GCC and is therefore windows only. Sorry. You can
		// replace it with sstreams, but for the sake of readability it is not done here.
		Text(1100, 650, std::to_string((int)fps()) + " FPS");
#endif

		Flip();
	}

	FreeImage(t);
	FreeImage(t2);
	FreeImage(img);
	FreeFont(arial);

	EndGraphics();

	return 0;
}

