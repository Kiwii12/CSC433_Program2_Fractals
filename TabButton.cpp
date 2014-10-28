/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/24/2014
 *
 * @file File containing the implementatio for the TabButton class.
 *
 * @brief Contains the implementation for the TabButton Subclass.
*******************************************************************************/
#include "TabButton.h"

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * constuctor, creates a button and given coordinants of given length
 * 
 * 
 * @param[in]      string 1 - name of the button
 * @param[in]	   double x - left coordinant of the button
 * @param[in]	   double y - bottom coordinant of the button
 * @param[in]	   double w - width of button
 * @param[in]	   double h - height of button
 *****************************************************************************/
TabButton::TabButton(string l, double x, double y, double w, double h)
: Button(l, x, y, w, h), active(false)
{

}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * destructor - destructor, exists
 *****************************************************************************/
TabButton::~TabButton()
{

}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * destructor - draws and highlights the function
 *****************************************************************************/
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
