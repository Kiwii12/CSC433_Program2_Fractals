/***************************************************************************//**
 * @file File containing the implementation for the ViewManager class.
 *
 * @brief Contains the implementation for the ViewManager class.
*******************************************************************************/
/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "ViewManager.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Constructor for the class. Initializes variables.
 *****************************************************************************/
ViewManager::ViewManager()
	: active_view(NULL)
{
	
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Destructor for the class. Cleans up unfinished business.
 *****************************************************************************/
ViewManager::~ViewManager()
{
	if (active_view != NULL)
	{
		active_view -> hide();
	}
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Registers a view under the given name. If a view under the
 *      given name already exists, will fail and return false.
 *
 * @param[in]	name - The name to register the view under.
 * @param[in]	view - Pointer to the view to register. Fails if pointer is
 *      NULL.
 *
 * @returns true if the view was successfully registered, false if not.
 *****************************************************************************/
bool ViewManager::registerView(string name, View* view)
{
	if (view == NULL) return false;
	View* v = getRegisteredView(name);
	if (v == NULL)
	{
		views[name] = view;
		return true;
	}
	return false;
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Unregisteres the view that is registered under the given
 *      name. If the target view is currently the active view, stops drawing
 *      that view.
 *
 * @param[in]	name - The name of the view to unregister.
 *
 * @returns true if successful, false if not.
 *****************************************************************************/
bool ViewManager::unregisterView(string name)
{
	// Make sure the view exists before attempting to unregister it
	View* v = getRegisteredView(name);
	if (v != NULL)
	{
		// Hide and erase the view
		v -> hide();
		views.erase(name);
		
		// Take proper action if the target view is the currently active view
		if (active_view == v)
		{
			active_view = NULL;
		}
		return true;
	}
	return false;
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Hides the currently active view and makes the view
 *      registered under the given name visible.
 *
 * @param[in]	name - The name under which the desired view is registered.
 *
 * @returns true if the switch was successful, false if not.
 *****************************************************************************/
bool ViewManager::switchView(string name)
{
	// First, make sure the target is even registered
	if (getRegisteredView(name) != NULL)
	{
		// Hide the currently active view if it exists
		if (active_view != NULL)
		{
			active_view -> hide();
		}
		
		// Make the desired view active and show it
		active_view = getRegisteredView(name);
		active_view -> show();
		return true;
	}
	return false;
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets a pointer to the view registered under the given
 *      name.
 *
 * @param[in]	name - The name under which the desired view is registered.
 *
 * @returns Pointer to the view registered under the given name, or NULL if no
 *      views are registered under that name.
 *****************************************************************************/
View* ViewManager::getRegisteredView(string name)
{
	// Use a try-catch to see if the item is in the map. If not, return NULL.
	if (views.find(name) == views.end())
	{
		return views[name];
	}
	else
	{
		return NULL;
	}
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets a pointer to the currently active view.
 *
 * @returns Pointer to the currently active view, or NULL if no views are
 *      active.
 *****************************************************************************/
View* ViewManager::getActiveView()
{
	return active_view;
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Draws the currently active view or nothing if there are
 *      no active views.
 *****************************************************************************/
void ViewManager::draw()
{
	// Of course, make sure we have an active view before attempting to draw it
	if (active_view != NULL)
	{
		active_view -> draw();
	}
}
