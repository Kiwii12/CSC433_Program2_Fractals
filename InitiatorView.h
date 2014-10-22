#ifndef _INITIATORVIEW_H_
#define _INITIATORVIEW_H_

class InitiatorView;

#include <list>

class InitiatorView
{
private:
	bool rubberband;
	
public:
	list<Fractal::point> initiator;
	
	InitiatorView(double x = 0, double y = 0, double w = 0, double h = 0);
	
	void mouseclick(int button, int state, int x, int y);
	void mousemove(int x, int y);
	void mousedrag(int x, int y);
	void draw();
};

#endif
