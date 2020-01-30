#include "plot.h"

int main(int argc, char *argv[])
{
	
	Vector x(41), y(41), a(41), b(41), c(41), d(41);
	for (int i = 0; i < 41; i++)
	{
		x[i] = i / 4.; y[i] = 3+30*sin(2*PI*(i / 4. - 5)/10.);
		a[i] = i / 4.; b[i] = (i / 4. - 2) * (i / 4. - 2) - 10;
		c[i] = i / 4.; d[i] = (i / 4. - 8) * (i / 4. - 8) - 10;
	}
	
	Plot plot(x, y);
	plot.add_dataset(a, b, rgb_color(0.4, 1, 0.4));
	plot.add_dataset(c, d, rgb_color(0.4, 1, 1));
	plot.set_axtitle("x-Axis");
	plot.set_aytitle("y-Axis");
	plot.set_title("Test");
	plot.show_height();
	plot.show_lines(false);

	plot.show();

	string command;
	int n = 1;
	while (plot.is_open())
	{
		std::cin >> command;
		if (command == "nd") plot.show_dots(false);
		else if (command == "d") plot.show_dots();
		else if (command == "nl") plot.show_lines(false);
		else if (command == "l") plot.show_lines();
		else if (command == "ns") plot.show_surface(false);
		else if (command == "s") plot.show_surface();
		else if (command == "nh") plot.show_height(false);
		else if (command == "h") plot.show_height();
		else plot.set_title(command);
		plot.append_data(0, x + 10 * n, y);
		n++;
	}

	return 0;
}
