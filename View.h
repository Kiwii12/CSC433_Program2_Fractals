/***************************************************************************//**
 * @file File containing the declaration for the View class.
 *
 * @brief Contains the declaration for the View class.
*******************************************************************************/
#ifndef _VIEW_H_
#define _VIEW_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "DrawingManager.h"

/*******************************************************************************
 *                              CLASS INTERFACE
 ******************************************************************************/
/*!
 * @brief Interface for a View class. Declares functions for hiding and showing
 * view.
 *
 * @details Provides functions and data for hiding and showing view and item
 * management.
 */
class View : public DrawingManager
{
private:
	bool hidden;		/*!< Whether or not view is shown on screen */

public:
	double x;
	double y;
	double width;
	double height;

	int lastButton;
	
	View(double x = 0, double y = 0, double w = 0, double h = 0);

	/*!
	 * @brief Allows this object to be drawn.
	 */
	void show();
		
	/*!
	 * @brief Prevents this object from being drawn.
	 */
	void hide();
		
	/*!
	 * @brief Checks if this object is being drawn.
	 */
	bool isHidden();

	/*!
	 * @brief Function defining how the object is drawn.
	 */
	void draw();
	
	/*!
	 * @brief Sends the view a click event.
	 */
	virtual void mouseclick( int button, int state, int x, int y ) = 0;
	
	/*!
	 * @brief Mouse movement callback. Executes whenever a mouse is moved
	 *		inside the program window.
	 */
	virtual void mousemove(int x, int y) = 0;

	/*!
	 * @brief Mouse drag callback. Executes whenever a mouse is moved inside
	 *		the program window while a button is pressed.
	 */
	virtual void mousedrag(int x, int y) = 0;
	
};

#endif
