#include "ViewManager.h"

bool ViewManager::registerView(string name, View* view)
{
	// TODO
}

bool ViewManager::unregisterView(string name)
{
	// TODO
}

bool ViewManager::switchView(string name)
{
	if (getRegisteredView(name) != NULL)
	{
		getRegisteredView(current_view) -> hide();
		active_view = name;
		getRegisteredView(current_view) -> show();
	}
}

View* ViewManager::getRegisteredView(string name)
{
	try
	{
		return views.at(name);
	}
	catch (int e)
	{
		return NULL;
	}
}

View* ViewManager::getActiveView()
{
	return getRegisteredView(active_view);
}
