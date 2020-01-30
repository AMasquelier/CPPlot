# CPPlot
## Features :
  - Adaptive scale
  - Dynamic use
  - Handle multiple dataset
#### Example
  Vector x(41), y(41);
	for (int i = 0; i < 41; i++)
	{
		x[i] = i / 4.; y[i] = 3+30*sin(2*PI*(i / 4. - 5)/10.);
	}
	
	Plot plot(x, y);
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
		plot.append_data(0, x + 10 * n, y);
		Clock::sleep(1000);
		n++;
	}
  This example create a sinus function with more data every econd

![alt text][Demo]


[Demo]: CPPlot.png "CPPlot"
