/***************************************************************************//**
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
