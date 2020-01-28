#pragma once
#include"graphics.h"
#include <string>
using namespace std;

class Plot_data
{
public:
	Plot_data(Vector x, Vector y, Color color);

	Vector X, Y;
	Color col;
};

class Plot
{
	public: 
		static void Init();
		static void Link_window(Window* win);
		static void draw_axes(double xmin, double xmax, double ymin, double ymax);

		Plot();
		Plot(Vector x, Vector y);

		void display();
		void add_data(Vector x, Vector y, Color color);
		void set_title(string title);
		void set_axtitle(string title);
		void set_aytitle(string title);
		void set_axis_title(string title);

	private:
		static Font _font;
		static Window* _window;

		vector<Plot_data> _data;
		double _xmin, _xmax;
		double _ymin, _ymax;
		bool _valid = false;

		Texture _title, _axtitle, _aytitle;

};