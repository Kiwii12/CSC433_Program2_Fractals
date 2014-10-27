/***************************************************************************//**
 * @file File containing the declaration for the TabButton class.
 *
 * @brief This Class is responsible for switching view tabs
*******************************************************************************/
#ifndef _TABBUTTON_H_
#define _TABBUTTON_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class TabButton;

#include "Button.h"
#include <string>

using namespace std;

/***************************************************************************//**
 * @brief The TabButton Class is a subclass of button, It deals with buttons 
 *		that switch which view class is active
*******************************************************************************/
class TabButton : public Button
{
public:
	bool active; /*!< if the mouse is over the button */

	/**
	* @brief The Constructor, sets private data from Button
	*/
	TabButton(string l, double x, double y, double w, double h);

	/**
	* @brief The Destructor, exsists
	*/
	~TabButton();

	/**
	* @brief The Draws and highlights the button
	*/
	void draw();
};

#endif
