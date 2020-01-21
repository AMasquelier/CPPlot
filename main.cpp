#include "plot.h"
#include "inputs.h"
#include "core.h"

bool close = false;
Window window;

void Init()
{
	if (!init_graphics())
	{
		close = true;
		std::cout << "Failed to init graphics" << std::endl;
	}
	if (!window.create("Game Engine", 1080, 720, 200, 120))
	{
		close = true;
		std::cout << "Failed to create window" << std::endl;
	}
	Draw::Init();
	Plot::Init();
}

int main(int argc, char *argv[])
{
	Clock framerate_timer; framerate_timer.start();
	float main_framerate = 30.0;

	Init();

	Inputs input; 
	Vector x(41), y(41), a(41), b(41), c(41), d(41);
	for (int i = 0; i < 41; i++)
	{
		x[i] = i / 4.; y[i] = (i / 4. - 5) * (i / 4. - 5);
		a[i] = i / 4.; b[i] = (i / 4. - 2) * (i / 4. - 2);
		c[i] = i / 4.; d[i] = (i / 4. - 8) * (i / 4. - 8);
	}
	
	Plot plot(x, y);
	plot.add_data(a, b, rgb_color(0.4, 1, 0.4));
	plot.add_data(c, d, rgb_color(0.4, 1, 1));
	plot.set_axtitle("x-Axis");
	plot.set_aytitle("y-Axis");

	while (!close)
	{
		if (framerate_timer.duration() >= 1000000.0 / main_framerate)
		{
			double act_fps = ceilf(1000000.0 / framerate_timer.duration());
			framerate_timer.start();
			// Inputs
			input.UpdateKeyboardInputs(true);
			if (input.close_win) close = true;



			// Rendering
			window.clear();

			//Draw::Debug_Text(Point2D(500, 20), "CPPlot", 20, rgb_color(1, 1, 1));

			plot.display();

			window.update();
		}
		else Clock::sleep(1000.0 / main_framerate - framerate_timer.duration() * 0.001);
	}

	return 0;
}
