#include "Button.h"

Button::Button(string l, double x, double y, double w, double h)
: label(l), x(x), y(y), width(w), height(h), hover(false), pressed(false)
{
	
}

Button::~Button()
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
			pressed = true;
			draw();
			glFlush();
		}

		break;
	case 1:		// on release
		if (pressed)
		{
			pressed = false;
			if (onMe)
			{
				draw();
				glFlush();
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
		glFlush();
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
	if (hover)
	{
		if (pressed)
		{
			// hovering and pressed = dark blue box
			glColor3ub(0, 191, 255);
		}
		else
		{
			// hovering but not pressed = light blue box
			glColor3ub(135, 206, 250);
		}
	}
	else
	{
		// Not hovering = white box
		glColor3ub(255, 255, 255);
	}
	
	glRecti((int) x, (int) y, (int) (x + width), (int) (y + height));

	// Draw black border
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2d(x + 0.5, y + 0.5);
		glVertex2d(x + 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + 0.5);
	}
	glEnd();

	// Draw black text
	glColor3ub(0, 0, 0);

	double padding = (height - 18) / 2 + 2;
	glRasterPos2d(x + padding, y + padding);
	glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char *) label.c_str() );
}
