/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/24/2014
 *
 * @file File containing the declaration for the Button class.
 *
 * @brief Contains declaration for the button class
*******************************************************************************/
#ifndef _BUTTON_H_
#define _BUTTON_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class Button;

#include <string>
#include <functional>
#include "Drawable.h"


/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
using namespace std;

/***************************************************************************//**
 * @brief The Button Class handles all the user interface buttons
 *
 * @details This Class can be given a function, It then makes a button that
 *		runs that function
*******************************************************************************/
class Button : public Drawable
{
protected:
	string label;	/*!< Button Name */
	double x;		/*!< left coordinate of a button */
	double y;		/*!< bottom coordinate of a button */
	double width;	/*!< width of a button */
	double height;	/*!< height of a button */
	bool hover;		/*!< wither or not the mouse is over the button */
	bool pressed;	/*!< if the button is clicked on */
	function<void()> callback;	/*!< the function the button does */

public:
	/**
	* @brief The Constructor, sets private data
	*/
	Button(string l, double x, double y, double w, double h);

	/**
	* @brief The Destructor, exsists to resolve compile errors
	*/
	virtual ~Button();

	/*
	* @brief sets the given function that the button performs
	*/
	void setAction(function<void()> action);

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
	* @brief callback, draws all parts of the button
	*/
	void draw();
};

#endif
