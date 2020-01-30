#include "plot.h"
#include "inputs.h"


void Plot::draw_axes(double xmin, double xmax, double ymin, double ymax)
{
	double gx = 150, gy = 80, gw = _window.get_width() - 230, gh = _window.get_height() - 160;

	Draw::Rectangle(Vector2(gx, gy + gh), Vector2(gx + gw, gy), rgb_color(1, 1, 1));
	double scale = (gh / (ymax - ymin));
	int order = int(log10f((ymax - ymin))) - 1;
	double y_step = ceil(((ymax - ymin) / 10) / pow(10, order)) * pow(10, order);


	double min = ceil((ymin / y_step)) * y_step;

	for (int i = 0; i < 12; i++)
	{
		double y = gy + gh - scale * (min + i * y_step - ymin);
		if (y < gy) break;
		Draw::Line(Point2D(gx-5, y), Point2D(gx+5, y), rgb_color(1, 1, 1));
		string str = to_string(min + i * y_step); str = str.substr(0, str.find(".") + 3);
		Draw::Debug_Text(Point2D(gx - 10 - str.length() * 8, y - 6), str, 12, rgb_color(1, 1, 1));
	}
	if (abs(ymin - min) > y_step / 2)
	{
		double y = gy + gh;
		Draw::Line(Point2D(gx-5, y), Point2D(gx+5, y), rgb_color(1, 1, 1));
		string str = to_string(ymin); str = str.substr(0, str.find(".") + 3);
		Draw::Debug_Text(Point2D(gx - 10 - str.length() * 8, y - 6), str, 12, rgb_color(1, 1, 1));
	}

	scale = (gw / (xmax - xmin));
	order = int(log10f((xmax - xmin))) - 1;
	double x_step = ceil(((xmax - xmin) / 10) / pow(10, order)) * pow(10, order);

	min = ceil((xmin / x_step)) * x_step;


	for (int i = 0; i < 12; i++)
	{
		double x = gx + scale * (min + i * x_step - xmin);
		if (x > gx + gw) break;
		Draw::Line(Point2D(x, gy + gh - 5), Point2D(x, gy + gh + 5), rgb_color(1, 1, 1));
		string str = to_string(min + i * x_step); str = str.substr(0, str.find(".") + 3);
		Draw::Debug_Text(Point2D(x - str.length() * 8 / 2, gy + gh + 15), str, 12, rgb_color(1, 1, 1));
	}
	if (abs(xmin - min) > x_step / 2)
	{
		double x = gx;
		Draw::Line(Point2D(x, gy + gh - 5), Point2D(x, gy + gh + 5), rgb_color(1, 1, 1));
		string str = to_string(xmin); str = str.substr(0, str.find(".") + 3);
		Draw::Debug_Text(Point2D(x - str.length() * 8 / 2, gy + gh + 15), str, 12, rgb_color(1, 1, 1));

	}

}



Plot_data::Plot_data(Vector x, Vector y, Color color)
{
	X = x; Y = y;
	col = color;
	xmin = X.min(); ymin = Y.min();
	xmax = X.max(); ymax = Y.max();
}


Plot::Plot()
{
	
}

Plot::Plot(Vector x, Vector y)
{
	if (x.get_size() == y.get_size())
	{
		_valid = true;
		_data.push_back(Plot_data(x, y, rgb_color(1, 0.6, 0.6)));
		_xmin = min(x.min(), _xmin); _xmax = max(x.max(), _xmax);
		_ymin = min(y.min(), _ymin); _ymax = max(y.max(), _ymax);


		_title.LoadText(_font, "CPPlot", 24, rgb_color(1, 1, 1));
	}
	else _valid = false;
}

Plot::~Plot()
{
	_thread->join();
	delete _thread;
}

void Plot::show()
{
	if (!_valid) return;
	_thread = new thread(&Plot::loop, this);
}

void Plot::append_data(int dataset, Vector x, Vector y)
{
	if (dataset >= 0 && dataset < _data.size() && x.get_size() == y.get_size())
	{
		_data[dataset].X.append(x);
		_data[dataset].Y.append(y);
	}
	_data[dataset].xmin = _data[dataset].X.min(); _data[dataset].ymin = _data[dataset].Y.min();
	_data[dataset].xmax = _data[dataset].X.max(); _data[dataset].ymax = _data[dataset].Y.max();

	bool initialized = false;
	for (int i = 0; i < _data.size(); i++)
	{
		if (_chosen_plot == -1 || _chosen_plot >= _data.size() || i == _chosen_plot)
		{
			if (initialized)
			{
				_xmin = min(_data[i].xmin, _xmin); _xmax = max(_data[i].xmax, _xmax);
				_ymin = min(_data[i].ymin, _ymin); _ymax = max(_data[i].ymax, _ymax);
			}
			else
			{
				_xmin = _data[i].xmin; _xmax = _data[i].xmax;
				_ymin = _data[i].ymin; _ymax = _data[i].ymax;
				initialized = true;
			}
		}
	}
}


void Plot::display()
{
	double gx = 150, gy = 80, gw = _window.get_width() - 230, gh = _window.get_height() - 160;

	double xmin, ymin;
	double xmax, ymax;

	if (_global_scale)
	{
		xmin = _xmin; ymin = _ymin;
		xmax = _xmax; ymax = _ymax;
	}
	else
	{
		bool initialized = false;
		for (int i = 0; i < _data.size(); i++)
		{
			if (_chosen_plot == -1 || _chosen_plot >= _data.size() || i == _chosen_plot)
			{
				if (initialized)
				{
					xmin = min(_data[i].xmin, xmin); xmax = max(_data[i].xmax, xmax);
					ymin = min(_data[i].ymin, ymin); ymax = max(_data[i].ymax, ymax);
				}
				else
				{
					xmin = _data[i].xmin; xmax = _data[i].xmax;
					ymin = _data[i].ymin; ymax = _data[i].ymax;
					initialized = true;
				}
			}
		}
		
	}
	draw_axes(xmin, xmax, ymin, ymax);
	
	double yscale = (gh / (ymax - ymin));
	double xscale = (gw / (xmax - xmin));

	if (_title.is_loaded()) Draw::TEXTURE(Point2D(gx + (gw-_title.get_w())/2, 20), _title);
	if (_axtitle.is_loaded()) Draw::TEXTURE(Point2D(gx + (gw - _axtitle.get_w()) / 2, gy + gh + 40), _axtitle);
	if (_aytitle.is_loaded()) Draw::Rotated_TEXTURE(Point2D(gx-130, gy + (gh - _aytitle.get_h()) / 2), Point2D(_aytitle.get_w() / 2, _aytitle.get_h() / 2), -PI/2, _aytitle);

	for (int i = 0; i < _data.size(); i++)
	{
		if (_chosen_plot == -1 || _chosen_plot >= _data.size() || i == _chosen_plot)
		{
			double lx, ly;
			for (int j = 0; j < _data[i].X.get_size(); j++)
			{
				double x = gx + xscale * (_data[i].X[j] - xmin);
				double y = gy + gh - yscale * (_data[i].Y[j] - ymin);
				if (_dot) Draw::Circle(Point2D(x, y), 3, 20, _data[i].col);
				if (_height) Draw::Line(Point2D(x, y), Point2D(x, gy + gh - yscale * (-ymin)), _data[i].col);
				if (j > 0)
				{
					if (_line) Draw::Line(Point2D(x, y), Point2D(lx, ly), _data[i].col);
					if (_surf)
					{
						if (((_data[i].Y[j] < 0 && _data[i].Y[j - 1] > 0)) && abs(_data[i].Y[j]) > 10e-7 && abs(_data[i].Y[j - 1]) > 10e-7)
						{
							double x0 = _data[i].X[j - 1] + (_data[i].X[j] - _data[i].X[j - 1]) * (_data[i].Y[j] / (_data[i].Y[j] - _data[i].Y[j - 1]));
							double x02 = gx + xscale * (x0 - xmin);

							Draw::Filled_Triangle(Point2D(x, y), Point2D(x02, gy + gh - yscale * (-ymin)), Point2D(x, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
							Draw::Filled_Triangle(Point2D(lx, ly), Point2D(x02, gy + gh - yscale * (-ymin)), Point2D(lx, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
							//Draw::Filled_Rectangle(Point2D(lx, y), Point2D(x, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
						}
						else if (((_data[i].Y[j] > 0 && _data[i].Y[j - 1] < 0)) && abs(_data[i].Y[j]) > 10e-7 && abs(_data[i].Y[j - 1]) > 10e-7)
						{
							double x0 = _data[i].X[j - 1] - (_data[i].X[j] - _data[i].X[j - 1]) * (_data[i].Y[j - 1] / (_data[i].Y[j] - _data[i].Y[j - 1]));
							double x02 = gx + xscale * (x0 - xmin);

							Draw::Filled_Triangle(Point2D(x, y), Point2D(x02, gy + gh - yscale * (-ymin)), Point2D(x, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
							Draw::Filled_Triangle(Point2D(lx, ly), Point2D(x02, gy + gh - yscale * (-ymin)), Point2D(lx, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
							//Draw::Filled_Rectangle(Point2D(lx, y), Point2D(x, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
						}
						else if (abs(_data[i].Y[j]) > abs(_data[i].Y[j - 1]))
						{
							Draw::Filled_Triangle(Point2D(x, y), Point2D(lx, ly), Point2D(x, ly), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
							Draw::Filled_Rectangle(Point2D(lx, ly), Point2D(x, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));

						}
						else
						{
							Draw::Filled_Triangle(Point2D(x, y), Point2D(lx, ly), Point2D(lx, y), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));
							Draw::Filled_Rectangle(Point2D(x, y), Point2D(lx, gy + gh - yscale * (-ymin)), rgba_color(_data[i].col.r, _data[i].col.g, _data[i].col.b, 0.1));

						}
					}
				}
				lx = x; ly = y;
			}
		}
	}
}

void Plot::loop()
{
	// Init
	bool close = false;
	_font.load("Hack-Regular.ttf");
	if (!init_graphics())
	{
		std::cout << "Failed to init graphics" << std::endl;
		close = true;
	}
	if (!_window.create("CPPlot", 1080, 720, 200, 120))
	{
		std::cout << "Failed to create window" << std::endl;
		close = true;
	}

	Draw::Init();

	if (_title_str.size() > 0) _title.LoadText(_font, _title_str, 24, rgb_color(1, 1, 1));
	if (_axtitle_str.size() > 0)_axtitle.LoadText(_font, _axtitle_str, 20, rgb_color(1, 1, 1));
	if (_aytitle_str.size() > 0)_aytitle.LoadText(_font, _aytitle_str, 20, rgb_color(1, 1, 1));


	// Loop
	Clock framerate_timer; framerate_timer.start();
	float main_framerate = 20;
	Inputs input;

	bool a = false;

	while (!close)
	{
		if (framerate_timer.duration() >= 1000000.0 / main_framerate)
		{
			double act_fps = ceilf(1000000.0 / framerate_timer.duration());
			framerate_timer.start();
			// Inputs
			input.UpdateKeyboardInputs(true);
			if (input.close_win) close = true;
			if (input.pushedInput(input.F1))  _chosen_plot = (_chosen_plot == 0) ? -1 : 0;
			if (input.pushedInput(input.F2))  _chosen_plot = (_chosen_plot == 1) ? -1 : 1;
			if (input.pushedInput(input.F3))  _chosen_plot = (_chosen_plot == 2) ? -1 : 2;
			if (input.pushedInput(input.F4))  _chosen_plot = (_chosen_plot == 3) ? -1 : 3;
			if (input.pushedInput(input.F5))  _chosen_plot = (_chosen_plot == 4) ? -1 : 4;
			if (input.pushedInput(input.S))   _global_scale = !_global_scale;

			if (_t_change)
			{
				_title.LoadText(_font, _title_str, 24, rgb_color(1, 1, 1));
				_t_change = false;
			}

			// Rendering
			_window.clear();

			//Draw::Debug_Text(Point2D(500, 20), "CPPlot", 20, rgb_color(1, 1, 1));

			display();

			_window.update();
		}
		else Clock::sleep(1000.0 / main_framerate - framerate_timer.duration() * 0.001);
	}
	_valid = false;
}

void Plot::add_dataset(Vector x, Vector y, Color color)
{
	if (x.get_size() == y.get_size())
	{
		_valid = true;
		_data.push_back(Plot_data(x, y, color));
		_xmin = min(x.min(), _xmin); _xmax = max(x.max(), _xmax);
		_ymin = min(y.min(), _ymin); _ymax = max(y.max(), _ymax);
	}
	else _valid = false;
}

void Plot::set_title(string title)
{
	_title_str = title;
	_t_change = true;
}

void Plot::set_axtitle(string title)
{
	_axtitle_str = title;
	if (_font) _axtitle.LoadText(_font, title, 20, rgb_color(1, 1, 1));
}

void Plot::set_aytitle(string title)
{
	_aytitle_str = title;
	if (_font) _aytitle.LoadText(_font, title, 20, rgb_color(1, 1, 1));
}

void Plot::set_axis_title(string xtitle, string ytitle)
{
	_axtitle_str = xtitle;
	_aytitle_str = ytitle;
	if (_font)
	{
		_axtitle.LoadText(_font, xtitle, 20, rgb_color(1, 1, 1));
		_aytitle.LoadText(_font, ytitle, 20, rgb_color(1, 1, 1));
	}
}

void Plot::show_dots(bool show)
{
	_dot = show;
}

void Plot::show_lines(bool show)
{
	_line = show;
}

void Plot::show_surface(bool show)
{
	_surf = show;
}

void Plot::show_height(bool show)
{
	_height = show;
}

void Plot::scatter_plot()
{
	_dot = true;
	_line = _surf = _height = false;
}

bool Plot::is_open()
{
	return _valid;
}
