/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the declaration for the InitiatorView class.
 *
 * @brief Contains this subclass holds the initaitor drawing window of the view
 *		class
*******************************************************************************/
#ifndef _INITIATORVIEW_H_
#define _INITIATORVIEW_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class InitiatorView;

#include <list>
#include "Fractals.h"
#include "View.h"
#include "Button.h"
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the implementatio for the View class.
 *
 * @brief Contains the implementation for the View class.
*******************************************************************************/
/***************************************************************************//**
 * @brief The InitiatorView class is a subclass of view, it deals with
 *		drawing the initiator
*******************************************************************************/
class InitiatorView: public View
{
private:
	double endx;	/*!< x value, of the second of two points,
					being added to linked list */
	double endy;	/*!< y value, of the second of two points,
					being added to linked list */
	bool leftButton;	/*!< wither or not the left button is pressed */
	Button clear_button; /*!< instance of button class used
						 to clear the linked list */

public:
	list<Fractals::point> initiator; /*!< holds the points that 
									make up the initiator */
	/**
	* @brief The Constructor, sets private data, 
	*			and gives the clear button a function
	*/
	InitiatorView(double x = 0, double y = 0, double w = 0, double h = 0);

	/**
	* @brief The Destructor, clears the linked list
	*/
	~InitiatorView();
	
	/**
	* @brief callback, handles mouseclick events
	*/
	void mouseclick(int button, int state, double x, double y);

	/**
	* @brief callback, handles mouse movement events
	*/
	void mousemove(double x, double y);

	/**
	* @brief callback, handles click-drag events
	*/
	void mousedrag(double x, double y);

	/**
	* @brief callback, draws all parts of the initiator view function
	*/
	void draw();
};

#endif
