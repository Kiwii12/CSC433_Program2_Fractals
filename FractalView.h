#ifndef _GENERATORVIEW_H_
#define _GENERATORVIEW_H_

class GeneratorView;

#include <list>

class GeneratorView
{
public:
	list<Fractal::point> fractal;
	
	GeneratorView(double x = 0, double y = 0, double w = 0, double h = 0);
	
	void mouseclick(int button, int state, int x, int y);
	void mousemove(int x, int y);
	void mousedrag(int x, int y);
	void draw();
};

#endif
