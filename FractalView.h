/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the declaration for the FractalView class.
 *
 * @brief Contains this subclass holds the Fractal drawing window of the view
 *		class
*******************************************************************************/
#ifndef _FRACTALVIEW_H_
#define _FRACTALVIEW_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class FractalView;

#include <list>
#include <deque>
#include <math.h>
#include "Fractals.h"
#include "View.h"
#include "Button.h"

#ifndef PI
#define PI	3.14159265
#endif

/***************************************************************************//**
 * @brief The FractalView class is a subclass of view, it deals with
 *		calculating and drawing the Fractal
*******************************************************************************/
class FractalView : public View
{
private:
	bool generated;		/*!< fractal has been generated */
	bool generating;	/*!< Fractal is generating */
	int generror;		/*!< throws an exception to help with error checking */
	Button build_button;	/*!< instance of button class for the user to 
							tell when to start building the fractal */

	Button* close_button;	/*!< button to close error windows */

	/**
	* @brief Fills in the distance and theta values in a linked list
	*/
	void completePoints(list<Fractals::point>* points);

	/**
	* @brief with the distance and theta value it creates a fractal
	*		from the initiator and generator
	*/
	void fractalize(
		list<Fractals::point>::iterator it,
		list<Fractals::point> &fractal,
		const list<Fractals::point> &generator);

	/**
	* @brief gives close button function to close errors
	*/
	void createCloseButton();

public:
	list<Fractals::point> fractal; /*!< Linked list to hold the fractal */
	
	/**
	* @brief The Constructor, sets private data, 
	*			and gives the Build Fractal button a function
	*/
	FractalView(double x = 0, double y = 0, double w = 0, double h = 0);

	/**
	* @brief The Destructor, clears the linked list
	*/
	~FractalView();
	
	/**
	* @brief Calcualates the x, y, theta, and distance of every point
	*		in the fractal
	*/
	void calculate();

	/**
	* @brief function close button uses to close error windows
	*/
	void closeErrorMessage();

	/**
	* @brief callback, handles mouseclick events, only used on button
	*/
	void mouseclick(int button, int state, double x, double y);

	/**
	* @brief callback, handles mouse movement events, only used on button
	*/
	void mousemove(double x, double y);

	/**
	* @brief callback, handles click-drag events, only used on button
	*/
	void mousedrag(double x, double y);

	/**
	* @brief callback, draws all parts of the fractal view function
	*/
	void draw();
};

#endif
