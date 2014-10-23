#ifndef _INITIATORVIEW_H_
#define _INITIATORVIEW_H_

class InitiatorView;

#include <list>
#include "Fractal.h"
#include "View.h"

class InitiatorView: public View
{
private:
	bool rubberband;

	double x;
	double y;
	double height;
	double width;
	
public:
	list<Fractal::point> initiator;
	
	InitiatorView(double x = 0, double y = 0, double w = 0, double h = 0);
	
	void mouseclick(int button, int state, int x, int y);
	void mousemove(int x, int y);
	void mousedrag(int x, int y);
	void draw();
};

#endif
