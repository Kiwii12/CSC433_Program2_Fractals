#include "TabButton.h"

TabButton::TabButton(string l, double x, double y, double w, double h)
: Button(l, x, y, w, h), active(false)
{

}

TabButton::~TabButton()
{

}

void TabButton::draw()
{
	// Back up status
	bool hover = this->hover;
	bool pressed = this->pressed;
	
	// Make button display hover mode when active
	if (active)
	{
		if (this->hover == false)
		{
			this->hover = true;
			this->pressed = false;
		}
	}
	
	// Draw self
	Button::draw();

	// Restore status
	this -> hover = hover;
	this -> pressed = pressed;
}
