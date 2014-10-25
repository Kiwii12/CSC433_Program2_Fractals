#ifndef _FRACTALVIEW_H_
#define _FRACTALVIEW_H_

class FractalView;

#include <list>
#include <math.h>
#include "Fractal.h"
#include "Fractals.h"
#include "View.h"
#include "Button.h"

#ifndef PI
#define PI	3.14159265
#endif

class FractalView : public View
{
private:
	bool generated;
	bool generating;
	int generror;
	Button build_button;

	void completePoints(list<Fractal::point>* points);
	void fractalize(
		list<Fractal::point>::iterator it,
		list<Fractal::point> &fractal,
		const list<Fractal::point> &generator);

public:
	list<Fractal::point> fractal;
	
	FractalView(double x = 0, double y = 0, double w = 0, double h = 0);
	~FractalView();
	
	void calculate();

	void mouseclick(int button, int state, double x, double y);
	void mousemove(double x, double y);
	void mousedrag(double x, double y);

	void draw();
};

#endif
