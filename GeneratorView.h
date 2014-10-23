#ifndef _GENERATORVIEW_H_
#define _GENERATORVIEW_H_

class GeneratorView;

#include <list>
#include "Fractal.h"
#include "View.h"

class GeneratorView: public View
{
private:
	bool rubberband;
	
public:
	list<Fractal::point> generator;
	
	GeneratorView(double x = 0, double y = 0, double w = 0, double h = 0);
	
	void mouseclick(int button, int state, double x, double y);
	void mousemove(double x, double y);
	void mousedrag(double x, double y);
	void draw();
};

#endif
