/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the implementatio for the View class.
 *
 * @brief Contains the implementation for the View class.
*******************************************************************************/
/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "View.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Constructor. Intitializes variables.
 *****************************************************************************/
View::View(double x, double y, double w, double h)
	: hidden(true), x(x), y(y), width(w), height(h)
{

}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Destructor. Does nothing, exists to resolve warnings.
 *****************************************************************************/
View::~View()
{ }

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Reveals the object. Allows the object to be drawn.
 *****************************************************************************/
void View::show()
{
	hidden = false;
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Hides the object. Prevents the object from being drawn.
 *****************************************************************************/
void View::hide()
{
	hidden = true;
}

/**************************************************************************//**
 * @author Johnathan Ackerman
 * 
 * @par Description:
 * gives instuction to the user
 * 
 * 
 * @param[in]      instruction - the instrunction to display
 *****************************************************************************/
void View::instructions( string instruction )
{	
	double x = 0;
	double y = 0;
	double width = 500;
	double height = 50;

	//Green Highlight rectangle for text
	glColor3d(.5,1,.5);
	glRectd(x, y, width, height);

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
	glutBitmapString( GLUT_BITMAP_HELVETICA_18, (const unsigned char *) instruction.c_str() );
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Checks if the object is currently hidden or not.
 *
 * @returns true if the object is hidden, false if not.
 *****************************************************************************/
bool View::isHidden()
{
	return hidden;
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Draws the object. If the object is hidden, does nothing.
 *****************************************************************************/
void View::draw()
{
	// Do nothing if object is hidden
	if (hidden)
	{
		return;
	}
	else
	{
		DrawingManager::draw();
	}
}
