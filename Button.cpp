/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Button.h"

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Constructor - initilizes data, and creates a window from information
 * 
 * 
 * @param[in]	   string 1 - name of this button
 * @param[in]      double x - left coordinant of window
 * @param[in]      double y - bottom coordinant of window
 * @param[in]      double w - width of window
 * @param[in]      double h - height of window
 *****************************************************************************/
Button::Button(string l, double x, double y, double w, double h)
: label(l), x(x), y(y), width(w), height(h), hover(false), pressed(false)
{
	
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Destructor - exists
 *****************************************************************************/
Button::~Button()
{
	
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * binds a function to the button
 * 
 * 
 * @param[in]      function<void()> action - function that button performs
 *****************************************************************************/
void Button::setAction(function<void()> action)
{
	this->callback = action;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * performs action when clicked on, only when clicked on
 *
 *
 *
 * @param[in]      int button - mouse button pressed
 * @param[in]      int state - mouse button pressed or released
 * @param[in]      double x - x coordinant of click
 * @param[in]      double y - y coordinant of click
 *****************************************************************************/
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

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * highlights buttons that the mouse is over
 *
 *
 *
 * @param[in]      double x - x coordinant of mouse
 * @param[in]      double y - y coordinant of mouse
 *****************************************************************************/
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

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * passes mouse drag to mouse move
 *
 *
 *
 * @param[in]      double x - x coordinant of mouse
 * @param[in]      double y - y coordinant of mouse
 *****************************************************************************/
void Button::mousedrag(double x, double y)
{
	if (pressed)
	{
		mousemove(x, y);
	}
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Draws the button and highlights it when hovered on by mouse
 *****************************************************************************/
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
