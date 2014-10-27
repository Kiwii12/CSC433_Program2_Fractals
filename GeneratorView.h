
/***************************************************************************//**
 * @file File containing the declaration for the GeneratorView class.
 *
 * @brief Contains this subclass holds the generator drawing window of the view
 *		class
*******************************************************************************/
#ifndef _GENERATORVIEW_H_
#define _GENERATORVIEW_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class GeneratorView;

#include <list>
#include "Fractal.h"
#include "Fractals.h"
#include "View.h"
#include "Button.h"

class GeneratorView: public View
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
	list<Fractal::point> generator;
	
	/**
	* @brief The Constructor, sets private data, 
	*			and gives the clear button a function
	*/
	GeneratorView(double x = 0, double y = 0, double w = 0, double h = 0);

	/**
	* @brief The Destructor, clears the linked list
	*/
	~GeneratorView();
	
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
	* @brief callback, draws all parts of the generator view function
	*/
	void draw();
};

#endif
