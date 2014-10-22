/***************************************************************************//**
 * @file File containing the declaration for the ViewManager class.
 *
 * @brief Contains the declaration for the ViewManager class.
*******************************************************************************/
#ifndef _VIEWMANAGER_H_
#define _VIEWMANAGER_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class ViewManager;

#include <map>
#include <string>
#include "View.h"
#include "Drawable.h"

using namespace std;

/*******************************************************************************
 *                              CLASS INTERFACE
 ******************************************************************************/
/*!
 * @brief Interface for a ViewManager class. Declares methods for registering
 *      and managing multiple views, including switching between views.
 *
 * @details Provides functions and data for managing multiple views.
 */
class ViewManager : Drawable
{
private:
	map<string, View*> views;	/*!< Map of registered views */
	View* active_view;			/*!< Pointer to currently active view */
	
public:
	
	/*!
	 * @brief Registers a view
	 */
	bool registerView(string name, View* view);
	
	/*!
	 * @brief Unregisteres a view from the manager
	 */
	bool unregisterView(string name);
	
	/*!
	 * @brief Hides the current view and displays the given view
	 */
	bool switchView(string name);
	
	/*!
	 * @brief Gets a pointer to the view registered under the given name
	 */
	View* getRegisteredView(string name);
	
	/*!
	 * @brief Gets a pointer to the currently active view
	 */
	View* getActiveView();
	
	/*!
	 * @brief Draws the currently active view if one is active
	 */
	void draw();
};

#endif
