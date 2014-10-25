#ifndef _INITIATORVIEW_H_
#define _INITIATORVIEW_H_

class InitiatorView;

#include <list>
#include "Fractal.h"
#include "Fractals.h"
#include "View.h"
#include "Button.h"

class InitiatorView: public View
{
private:
	double endx;
	double endy;
	bool leftButton;
	Button clear_button;

public:
	list<Fractal::point> initiator;
	
	InitiatorView(double x = 0, double y = 0, double w = 0, double h = 0);
	~InitiatorView();
	
	void mouseclick(int button, int state, double x, double y);
	void mousemove(double x, double y);
	void mousedrag(double x, double y);
	void draw();
};

#endif
