#pragma once
#include"graphics.h"
#include <string>
#include <thread>
using namespace std;

class Plot_data
{
public:
	Plot_data(Vector x, Vector y, Color color);

	Vector X, Y;
	Color col;
	double xmin, xmax;
	double ymin, ymax;
};

class Plot
{
	public: 
		Plot();
		Plot(Vector x, Vector y);
		~Plot();

		void show();
		void append_data(int dataset, Vector x, Vector y);
		void add_dataset(Vector x, Vector y, Color color);
		void set_title(string title);
		void set_axtitle(string title);
		void set_aytitle(string title);
		void set_axis_title(string xtitle, string ytitle);
		void show_dots(bool show=true);
		void show_lines(bool show=true);
		void show_surface(bool show=true);
		void show_height(bool show=true);
		void scatter_plot();

		bool is_open();

	private:
		void draw_axes(double xmin, double xmax, double ymin, double ymax);
		void display();
		void loop();
		Window _window;
		thread *_thread;

		Font _font;

		vector<Plot_data> _data;
		double _xmin, _xmax;
		double _ymin, _ymax;
		bool _valid = false;

		bool _global_scale = true;
		bool _surf = false, _dot = true, _line = true, _height = true;
		string _title_str, _axtitle_str, _aytitle_str;
		bool _t_change = false, _axt_change = false, _ayt_change = false;

		Texture _title, _axtitle, _aytitle;

		int _chosen_plot = -1;

};