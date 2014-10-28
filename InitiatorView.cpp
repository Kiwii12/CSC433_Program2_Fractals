/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the implementatio for the View class.
 *
 * @brief Contains the implementation for the InitiatorView Subclass.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "InitiatorView.h"

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Constructor - initilizes data, and creates a window from information
 * 
 * 
 * @param[in]      x - left coordinate of window
 * @param[in]      y - bottom coordinate of window
 * @param[in]      w - width of window
 * @param[in]      h - height of window
 *****************************************************************************/
InitiatorView::InitiatorView(double x, double y, double w, double h)
: View(x, y, w, h), endx(0), endy(0), leftButton(false),
clear_button("Clear Initiator", Fractals::button_x, Fractals::button_y,
			 Fractals::button_w * 2, Fractals::button_h)
{
	// Initialize button with its action
	clear_button.setAction([](){
		Fractals::getInstance()->initiatorView->initiator.clear();
		Fractals::getInstance()->initiatorView->draw();
		glFlush();
	});
	drawObject(&clear_button);
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Destructor - deletes the linked list
 *****************************************************************************/
InitiatorView::~InitiatorView()
{
	initiator.clear();
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * relays mouse clicks to the button class and allows the user to make the
 * initiator
 *
 * @param[in]      button - mouse button pressed
 * @param[in]      state - mouse button pressed or released
 * @param[in]      x - x coordinate of click
 * @param[in]      y - y coordinate of click
 *****************************************************************************/
void InitiatorView::mouseclick(int button, int state, double x, double y)
{
	clear_button.mouseclick(button, state, x, y);

	point p;
	
	// Cancel if point is outside view
	if (state == 0
		&& (x < this->x || y < this->y ||
			x > this->x + this->width || y > this->y + this->height))
	{
		return;
	}
	
	switch ( button )
    {
        case 0:				// left button: create objects
            if ( state == 0 )		// press - new start point
            {
				leftButton = true;

				if (initiator.size() == 0)
				{
					p.x = x;
					p.y = y;
					p.angle = 0;
					p.distance = 0;
					initiator.push_back(p);
				}
                // store mouse coordinates
                endx = x;
                endy = y;

				glutPostRedisplay();
            }

            else if ( state == 1 && leftButton)	// release - new endpoint
            {
				leftButton = false;

				if (x < this->x) x = this->x;
				if (y < this->y) y = this->y;
				if (x > this->x + this->width) x = this->x + this->width;
				if (y > this->y + this->height) y = this->y + this->height;

                p.x = x;
				p.y = y;
				p.angle = 0;
				p.distance = 0;
				initiator.push_back(p);

                // force redraw
				glutPostRedisplay();
            }

            break;

        case 2:				// Mouse right button
			if (state == 0) // pressed
			{
				// Delete last point
				if (initiator.size() == 2)
				{
					initiator.clear();
				}
				else if (initiator.size() > 0)
				{
					initiator.pop_back();
				}
			}
			glutPostRedisplay();
			break;

		default:
			break;
    }
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * passes mouse movement info to the build button(instance of button class
 *
 * @param[in]      x - x coordinate of mouse
 * @param[in]      y - y coordinate of mouse
 *****************************************************************************/
void InitiatorView::mousemove(double x, double y)
{
	clear_button.mousemove(x, y);
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * passes mouse drag info to the build button(instance of button class
 *
 * @param[in]      x - x coordinate of mouse
 * @param[in]      y - y coordinate of mouse
 *****************************************************************************/
void InitiatorView::mousedrag(double x, double y)
{
	clear_button.mousedrag(x, y);

	if (initiator.size() > 0 && leftButton) //left Mouse Button
    {
		// If mouse is out of bounds, make it in bounds
		if (x < this->x) x = this->x;
		if (y < this->y) y = this->y;
		if (x > this->x + this->width) x = this->x + this->width;
		if (y > this->y + this->height) y = this->y + this->height;

        endx = x;
        endy = y;

		draw();
		glFlush();
    }
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Draws the background, the drawing grid, and the intiator as the user draws
 * it. after it passes drawing control back to view
 *****************************************************************************/
void InitiatorView::draw()
{
	const static double grid_spacing = 32.0;

	// Draw background
	glColor3ub(255, 255, 255);
	glRectd(x, y, x+width, y+height);

	// Draw grid
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_LINES);
	for (double i = grid_spacing; i < width; i += grid_spacing)
	{
		glVertex2d(x + i - 0.5, y);
		glVertex2d(x + i - 0.5, y + height);
	}
	for (double i = grid_spacing; i < height; i += grid_spacing)
	{
		glVertex2d(x, y + i - 0.5);
		glVertex2d(x + width, y + i - 0.5);
	}
	glEnd();
	
	// Draw border
	glBegin(GL_LINE_LOOP);
	{
		glVertex2d(x + 0.5, y + 0.5);
		glVertex2d(x + 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + 0.5);
	}
	glEnd();

	// Display every line in initiator
	glColor3f(0.0, 0.0, 0.0);
	if (initiator.size() > 1)
	{
		glBegin(GL_LINES);
		auto it1 = initiator.begin();
		auto it2 = initiator.begin();
		for (it2++; it2 != initiator.end(); it1++, it2++)
		{
			glVertex2d(it1->x, it1->y);
			glVertex2d(it2->x, it2->y);
		}
		glEnd();
	}

	// Draw rubberband line
	if (leftButton)
	{
		glBegin(GL_LINES);
		glVertex2d(initiator.back().x, initiator.back().y);
		glVertex2d(endx, endy);
		glEnd();
	}
	
	// Draw dotted line connecting endpoints
	if (initiator.size() > 1)
	{
		glLineStipple(3, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		if (leftButton)
		{
			glVertex2d(endx, endy);
			glVertex2d(initiator.front().x, initiator.front().y);
		}
		else if (initiator.size() > 2)
		{
			glVertex2d(initiator.back().x, initiator.back().y);
			glVertex2d(initiator.front().x, initiator.front().y);
		}
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}


	//dispay instructions
	if(initiator.size() == 0 )
	{
		View::instructions( "Click and drag to draw" );
	}

	View::draw();
}
