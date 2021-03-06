/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the implementatio for the View class.
 *
 * @brief Contains the implementation for the FractalView Subclass.
*******************************************************************************/
/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "FractalView.h"

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
FractalView::FractalView(double x, double y, double w, double h)
: View(x, y, w, h), generated(false), generating(false), generror(0),
build_button("Build Fractal", Fractals::button_x, Fractals::button_y,
Fractals::button_w * 2, Fractals::button_h), close_button(NULL)
{
	// Initialize button with its action
	build_button.setAction([](){
		Fractals::getInstance()->fractalView->calculate();
		glutPostRedisplay();
	});
	drawObject(&build_button);
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Destructor - deletes the linked list
 *****************************************************************************/
FractalView::~FractalView()
{
	fractal.clear();
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * calculates values for initiator and generator and then uses those values
 *		to create the fractal list
 *****************************************************************************/
void FractalView::calculate()
{
	// Reset variables
	generated = false;
	generating = true;
	generror = 0;

	// Get shortcut pointers to initiator and generator
	list<point>* initiator = 
				&(Fractals::getInstance() -> initiatorView -> initiator);
	list<point>* generator =
				&(Fractals::getInstance() -> generatorView -> generator);

	// Make sure both have minimum number of points
	if(initiator->size() < 3 || generator->size() < 3)
	{
		generror = (initiator->size() < 3 ? 1 : 2);
		generating = false;
		createCloseButton();
		return;
	}

	// Fill the initiator and generator
	completePoints(initiator);
	completePoints(generator);

	// Make generator is valid
	unsigned int i = 0;
	for (auto it = generator->begin();
		it != generator->end() && i < generator->size()-1;
		it++, i++)
	{
		// checks if segment distance is longer than total length
		if (it->distance >= generator->back().distance)
		{
			// Cancel generation and leave an error code
			generating = false;
			generror = 3;
			createCloseButton();
			return;
		}
	}

	// Clear our current fractal
	fractal.clear();
	generated = false;

	// Copy initiator into fractal
	fractal.insert(fractal.end(), initiator->begin(), initiator->end());

	// ... for calculations
	generator->back().angle += PI;

	// Set up queue
	deque<list<point>::iterator> queue;

	// Copy fractal into queue
	for (auto it = fractal.begin(); it != fractal.end(); it++)
	{
		queue.push_back(it);
	}
	
	// Time to build fractal, limit size to 0.5 GB
	i = 500000000/sizeof(point)/(generator->size() - 1);
	while (!queue.empty() && --i > 0)
	{
		auto it = queue.front();
		queue.pop_front();
		fractalize(it, fractal, *generator);
		for (unsigned int i = 1; i < generator->size(); i++, it++)
		{
			if (it->distance > 1)
			{
				queue.push_back(it);
			}
		}
	}
	
	// Do something special if we hit our memory limit
	if (i <= 0)
	{
		generated = true;
		generating = false;
		generror = 4;
		createCloseButton();
		return;
	}
	
	// Set variables to indicate success
	generated = true;
	generating = false;
	generror = 0;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Closes error message and removes close error button
 *****************************************************************************/
void FractalView::closeErrorMessage()
{
	if (close_button != NULL)
	{
		DrawingManager::stopDrawingObject(close_button);
		delete close_button;
	}
	close_button = NULL;
	generror = 0;
	glutPostRedisplay();
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Process mouse click events
 *
 * @param[in]      button - mouse button pressed
 * @param[in]      state - mouse button pressed or released
 * @param[in]      x - x coordinate of click
 * @param[in]      y - y coordinate of click
 *****************************************************************************/
void FractalView::mouseclick(int button, int state, double x, double y)
{
	build_button.mouseclick(button, state, x, y);
	if (close_button != NULL)
	{
		close_button->mouseclick(button, state, x, y);
	}
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Process mouse movement events.
 *
 * @param[in]      x - x coordinate of mouse
 * @param[in]      y - y coordinate of mouse
 *****************************************************************************/
void FractalView::mousemove(double x, double y)
{
	build_button.mousemove(x, y);
	if (close_button != NULL)
	{
		close_button->mousemove(x, y);
	}
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Process mouse dragging events
 *
 * @param[in]      x - x coordinate of mouse
 * @param[in]      y - y coordinate of mouse
 *****************************************************************************/
void FractalView::mousedrag(double x, double y)
{
	build_button.mousedrag(x, y);
	if (close_button != NULL)
	{
		close_button->mousedrag(x, y);
	}
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Draws the background, the drawing grid, and the fractal.
 *****************************************************************************/
void FractalView::draw()
{
	const static double grid_spacing = 32.0;

	//shortcut points - used for instuction check
	list<point>* initiator = 
				&(Fractals::getInstance() -> initiatorView -> initiator);
	list<point>* generator =
				&(Fractals::getInstance() -> generatorView -> generator);

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
	
	// Draw outline
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		glVertex2d(x + 0.5, y + 0.5);
		glVertex2d(x + 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + height - 0.5);
		glVertex2d(x + width - 0.5, y + 0.5);
	}
	glEnd();

	// Draw the fractal
	if (generated && !generating)
	{
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_STRIP);
		for (auto p : fractal)
		{
			glVertex2d(p.x, p.y);
		}
		glVertex2d(fractal.front().x, fractal.front().y);
		glEnd();
	}
	
	// Display an error message
	if (generror != 0)
	{
		// Draw white background
		glColor3ub(255, 255, 255);
		glRectd(x + width/2 - 230, y + height/2 - 60,
			x + width/2 + 230, y + height/2 + 60);
		
		// Draw black border. Using GL_LINE_STRIPE because loop is broken
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2d(x + width/2 - 230.5, y + height/2 - 60.5);
			glVertex2d(x + width/2 - 230.5, y + height/2 + 60.5);
			glVertex2d(x + width/2 + 230.5, y + height/2 + 60.5);
			glVertex2d(x + width/2 + 230.5, y + height/2 - 60.5);
		}
		glEnd();

		glRasterPos2d(x + width/2 - 200, y + height/2 + 30);
		
		// Decide which message to display
		switch (generror)
		{
		case 1:
			glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char*)
				"Error: Initiator must have at least 3 points!" );
			break;
		case 2:
			glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char*)
				"Error: Generator must have at least 3 points!" );
			break;
		case 3:
			glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char*)
				"Error: All lines in generator must be shorter than\n"
				" the distance between the end points!" );
			break;
		case 4:
			glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char*)
				"Error: Space limit reached!" );
			break;
		case 0:
		default:
			break;
		}
	}
	
	//draws instuctions
	if( initiator->size() == 0 && generator->size() == 0 )
	{
		View::instructions( "Press initiator or generator to begin" );
	}
	else if( fractal.size() == 0 )
	{
		View::instructions( "Build Fractal to see your creation" );
	}

	View::draw();

}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Calculates the distance and angle values for each line segment and stores
 * them with the point data in the given list.
 * 
 * @param[in]      points - passes a list to complete by calculating the angle
 * and distance to next point
 *****************************************************************************/
void FractalView::completePoints(list<point>* points)
{
	// Loop through every point in list
	auto it1 = points->begin();
	auto it2 = it1;
	for (it2++; it1 != points->end(); it1++, it2++)
	{
		// Wrap around
		if (it2 == points->end()) it2 = points->begin();

		// Calculate distance
		it1->distance = sqrt((it2->x - it1->x) * (it2->x - it1->x)
						+ (it2->y - it1->y) * (it2->y - it1->y));

		// Calculate angle, special case for vertical lines & x2 < x1
		// Will give us an angle between -90 <= x < 270 in radians
		it1->angle =
			(it2->x == it1->x ?		// If x1 == x2
				(it2->y > it1->y ?		// If y2 > y1
					PI/2.0					// angle is 90
					: -PI/2.0)				// else, angle is 270
				: atan((it2->y - it1->y) / (it2->x - it1->x)))
			+ (it2->x < it1->x ? PI : 0);	// adjust for x2 < x1
	}
}


/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Replaces a line segment in fractal with segments from generator-> Relies on
 * accurate angle and distance values.
 *
 * @param[in]      it - initiator to point to modify in fractal list
 * @param[in]      fractalize - fractal list
 * @param[in]      generator - generator list
 *****************************************************************************/
void FractalView::fractalize(
		list<point>::iterator it,
		list<point> &fractal,
		const list<point> &generator)
{
	// Base case
	if (it->distance <= 1)
	{
		return;
	}
	
	double distance = it->distance;
	double angle = it->angle;

	// Replace line segment with generator
	unsigned int i = 0;
	for (point p : generator)
	{
		// Set new distance and angle for old point
		it->distance = ((p.distance * distance) / generator.back().distance);
		it->angle = (p.angle + angle - generator.back().angle);

		// Set new point's x and y
		p.x = it->x + (it->distance * cos(it->angle));
		p.y = it->y + (it->distance * sin(it->angle));

		if (i < generator.size() - 2)
		{
			// Insert new point
			it++;
			fractal.insert(it, p);
			it--;
		}
		else
		{
			break;
		}
		i++;
	}

	// END
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Creats error closing button button and gives it a closing function
 *****************************************************************************/
void FractalView::createCloseButton()
{
	if (close_button == NULL)
	{
		close_button = new Button("OK", x + width/2 - 50, y + height/2 - 40, 100, 24);
		close_button->setAction([](){
			Fractals::getInstance()->fractalView->closeErrorMessage();
		});
		DrawingManager::drawObject(close_button);
	}
}
