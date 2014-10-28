/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the implementatio for the View class.
 *
 * @brief Contains the implementation for the Generator View Subclass.
*******************************************************************************/
/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "GeneratorView.h"

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Constructor - initilizes data, and creates a window from information
 * 
 * @param[in]      x - left coordinate of window
 * @param[in]      y - bottom coordinate of window
 * @param[in]      w - width of window
 * @param[in]      h - height of window
 *****************************************************************************/
GeneratorView::GeneratorView(double x, double y, double w, double h)
	: View(x, y, w, h), endx(0), endy(0), leftButton(false),
clear_button("Clear Generator", Fractals::button_x, Fractals::button_y,
			 Fractals::button_w * 2, Fractals::button_h)
{
	// Initialize button with its action
	clear_button.setAction([](){
		Fractals::getInstance()->generatorView->generator.clear();
		Fractals::getInstance()->generatorView->draw();
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
GeneratorView::~GeneratorView()
{
	generator.clear();
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * relays mouse clicks to the button class and allows the user to make the
 * generator
 *
 * @param[in]      button - mouse button pressed
 * @param[in]      state - mouse button pressed or released
 * @param[in]      x - x coordinate of click
 * @param[in]      y - y coordinate of click
 *****************************************************************************/
void GeneratorView::mouseclick(int button, int state, double x, double y)
{
	clear_button.mouseclick(button, state, x, y);

	Fractals::point p;
	
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

				if (generator.size() == 0)
				{
					p.x = x;
					p.y = y;
					p.angle = 0;
					p.distance = 0;
					generator.push_back(p);
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
				generator.push_back(p);

                // force redraw
				glutPostRedisplay();
            }

            break;

        case 2:				// Mouse right button
			if (state == 0) // pressed
			{
				// Delete last point
				if (generator.size() == 2)
				{
					generator.clear();
				}
				else if (generator.size() > 0)
				{
					generator.pop_back();
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
void GeneratorView::mousemove(double x, double y)
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
void GeneratorView::mousedrag(double x, double y)
{
	if (generator.size() > 0 && leftButton) //left Mouse Button
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
 * Draws the background, the drawing grid, and the generator as the user draws
 * it. after it passes drawing control back to view
 *****************************************************************************/
void GeneratorView::draw()
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

	// Display every line in generator
	glColor3f(0.0, 0.0, 0.0);
	if (generator.size() > 1)
	{
		glBegin(GL_LINES);
		auto it1 = generator.begin();
		auto it2 = generator.begin();
		for (it2++; it2 != generator.end(); it1++, it2++)
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
		glVertex2d(generator.back().x, generator.back().y);
		glVertex2d(endx, endy);
		glEnd();
	}


	//draw instuctions
	if(generator.size() == 0 )
	{
		View::instructions( "Click and drag to draw" );
	}

	View::draw();
}
