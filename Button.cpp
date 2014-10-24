#include "Button.h"

Button::Button(string l, double x, double y, double w, double h)
: label(l), x(x), y(y), width(w), height(h)
{

}

void Button::setAction(function<void()> action)
{
	this->callback = action;
}

void Button::mouseclick(int button, int state, double x, double y)
{
	// Cancel if it's not a left-click, since we don't care about those
	if (button != 0)
		return;

	// Detect if click occured over us
	bool onMe = !(x < this->x || x > this->x + this->width ||
				  y < this->y || y > this->y + this->height);
	
	switch (state)
	{
	case 0:		// on press
		if (!onMe)
		{
			return;
		}
		else
		{
			bool pressed = true;
		}

		break;
	case 1:		// on release
		if (pressed)
		{
			pressed = false;
			if (onMe)
			{
				draw();
				this->callback();
			}
		}
		break;
	default:	// I DON'T KNOW
		break;
	}
}

void Button::mousemove(double x, double y)
{
	// Detect if click occured over us
	bool onMe = !(x < this->x || x > this->x + this->width ||
				  y < this->y || y > this->y + this->height);
	bool redrawMe = onMe != hover;

	hover = onMe;
	if (redrawMe)
	{
		draw();
	}
}

void Button::mousedrag(double x, double y)
{
	if (pressed)
	{
		mousemove(x, y);
	}
}

void Button::draw()
{
	static const double border = 2;
	static const float white[3]	=	{ 1.0, 1.0, 1.0 };
	static const float gray[3] =	{ 0.3, 0.3, 0.3 };
	static const float black[3] =	{ 0.0, 0.0, 0.0 };

	if (hover)
	{
		if (pressed)
		{
			// hovering & pressed = white box with black text
			glColor3fv(white);
			glRectd(x, y, x+width, y+height);
			glColor3fv(black);
		}
		else
		{
			// hovering but not pressed = white border, grey box, white text
			glColor3fv(white);
			glRectd(x, y, x+width, y+height);
			glColor3fv(gray);
			glRectd(x+border, y+border, x+width-border, y+height-border);
			glColor3fv(white);
		}
	}
	else
	{
		glColor3fv(white);
		glRectd(x, y, x+width, y+height);
		glColor3fv(black);
		glRectd(x+border, y+border, x+width-border, y+height-border);
		glColor3fv(white);
	}

	glPushMatrix();
	glScalef( 0.25, 0.25, 1.0 );
    glTranslated((width / 2) * 4.0, (height / 2 + 10) * 4.0, 0);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char*) label.c_str());
    glPopMatrix();
}
