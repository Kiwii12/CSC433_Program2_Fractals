#ifndef _VIEWMANAGER_H_
#define _VIEWMANAGER_H_

class ViewManager;

#include <map>
#include <string>
#include "View.h"

using namespace std;

class ViewManager
{
private:
	map<string, View*> views;
	View* active_view;
	
public:
	bool registerView(string name, View* view);
	bool unregisterView(string name);
	bool switchView(string name);
	View* getRegisteredView(string name);
	View* getActiveView();
};

#endif
