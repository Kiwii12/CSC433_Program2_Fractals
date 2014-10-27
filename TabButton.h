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

class TabButton : public Button
{
public:
	bool active;

	TabButton(string l, double x, double y, double w, double h);
	~TabButton();
	void draw();
};

#endif
