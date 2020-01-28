#include "plot.h"

void Plot::draw_axes(double xmin, double xmax, double ymin, double ymax)
{
	double gx = 150, gy = 80, gw = _window->get_width() - 230, gh = _window->get_height() - 160;


	Draw::Rectangle(Vector2(gx, gy + gh), Vector2(gx + gw, gy), rgb_color(1, 1, 1));
	double scale = (gh / (ymax - ymin));
	int order = int(log10f((ymax - ymin))) - 1;
	double y_step = ceil(((ymax - ymin) / 10) / pow(10, order)) * pow(10, order);


	double min = ceil((ymin / y_step)) * y_step;

	for (int i = 0; i < 12; i++)
	{
		double y = gy + gh - scale * (min + i * y_step - ymin);
		if (y < gx) break;
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
}


Font Plot::_font;
Window* Plot::_window;
void Plot::Init()
{
	_font.load("Hack-Regular.ttf");
}

void Plot::Link_window(Window* win)
{
	_window = win;
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

void Plot::display()
{
	double gx = 150, gy = 80, gw = _window->get_width() - 230, gh = _window->get_height() - 160;


	draw_axes(_xmin, _xmax, _ymin, _ymax);
	double yscale = (gh / (_ymax - _ymin));
	double xscale = (gw / (_xmax - _xmin));

	if (_title.is_loaded()) Draw::TEXTURE(Point2D(gx + (gw-_title.get_w())/2, 20), _title);
	if (_axtitle.is_loaded()) Draw::TEXTURE(Point2D(gx + (gw - _axtitle.get_w()) / 2, gy + gh + 40), _axtitle);
	if (_aytitle.is_loaded()) Draw::Rotated_TEXTURE(Point2D(gx-130, gy + (gh - _aytitle.get_h()) / 2), Point2D(_aytitle.get_w() / 2, _aytitle.get_h() / 2), -PI/2, _aytitle);

	for (int i = 0; i < _data.size(); i++)
	{
		double lx, ly;
		for (int j = 0; j < _data[i].X.get_size(); j++)
		{
			double x = gx + xscale * (_data[i].X[j] - _xmin);
			double y = gy + gh - yscale * (_data[i].Y[j] - _ymin);
			//Draw::Circle(Point2D(x, y), 3, 20, _data[i].col);
			if (j > 0)
				Draw::Line(Point2D(x, y), Point2D(lx, ly), _data[i].col);
			lx = x; ly = y;
		}
	}
}

void Plot::add_data(Vector x, Vector y, Color color)
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
	_title.LoadText(_font, title, 24, rgb_color(1, 1, 1));
}

void Plot::set_axtitle(string title)
{
	_axtitle.LoadText(_font, title, 20, rgb_color(1, 1, 1));
}

void Plot::set_aytitle(string title)
{
	_aytitle.LoadText(_font, title, 20, rgb_color(1, 1, 1));
}

void Plot::set_axis_title(string title)
{
	_axtitle.LoadText(_font, title, 20, rgb_color(1, 1, 1));
	_aytitle.LoadText(_font, title, 20, rgb_color(1, 1, 1));
}
