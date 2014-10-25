#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button;

#include <string>
#include <functional>
#include "Drawable.h"

using namespace std;

class Button : public Drawable
{
protected:
	string label;
	double x;
	double y;
	double width;
	double height;
	bool hover;
	bool pressed;
	function<void()> callback;

public:
	Button(string l, double x, double y, double w, double h);
	virtual ~Button();

	void setAction(function<void()> action);
	void mouseclick(int button, int state, double x, double y);
	void mousemove(double x, double y);
	void mousedrag(double x, double y);
	void draw();
};

#endif
