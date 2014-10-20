#include "View.h"


View::View() : hidden(false)
{

}

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
