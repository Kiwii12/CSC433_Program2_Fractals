#ifndef _FRACTALVIEW_H_
#define _FRACTALVIEW_H_

class FractalView;

#include <list>
#include "Fractal.h"

class FractalView
{
private:
	double x;
	double y;
	double height;
	double width;

public:
	list<Fractal::point> fractal;
	
	FractalView(double x = 0, double y = 0, double w = 0, double h = 0);
	
	void mouseclick(int button, int state, int x, int y);
	void mousemove(int x, int y);
	void mousedrag(int x, int y);
	void draw();
};

#endif
