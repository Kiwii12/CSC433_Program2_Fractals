#include "ViewManager.h"

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

bool ViewManager::unregisterView(string name)
{
	View* view = getRegisteredView(name);
	if (view != NULL)
	{
		view -> hide();
		views.erase(name);
		if (active_view == view)
		{
			active_view = NULL;
		}
		return true;
	}
	return false;
}

bool ViewManager::switchView(string name)
{
	if (getRegisteredView(name) != NULL)
	{
		if (active_view != NULL)
		{
			active_view -> hide();
		}
		active_view = getRegisteredView(name);
		active_view -> show();
		return true;
	}
	return false;
}

View* ViewManager::getRegisteredView(string name)
{
	try
	{
		return views.at(name);
	}
	catch (int e)
	{
		e;
		return NULL;
	}
}

View* ViewManager::getActiveView()
{
	return active_view;
}
