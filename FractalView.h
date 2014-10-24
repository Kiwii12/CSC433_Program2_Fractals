#ifndef _FRACTALVIEW_H_
#define _FRACTALVIEW_H_

class FractalView;

#include <list>
#include "Fractal.h"
#include "Fractals.h"
#include "View.h"
#include "Button.h"

class FractalView : public View
{
private:
	bool generated;
	bool generating;
	int generror;
	Button build_button;

public:
	list<Fractal::point> fractal;
	
	FractalView(double x = 0, double y = 0, double w = 0, double h = 0);
	
	void calculate();

	void mouseclick(int button, int state, double x, double y);
	void mousemove(double x, double y);
	void mousedrag(double x, double y);

	void draw();
};

#endif
