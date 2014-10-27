/***************************************************************************//**
 * @file File containing the implementation for the DrawingManager class.
 *
 * @brief Contains the implementation for the DrawingManager class.
*******************************************************************************/
/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "DrawingManager.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
DrawingManager::~DrawingManager()
{

}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Registers a Drawable object to be drawn on demand.
 *
 * @param[in]	obj - Pointer to the object to draw
 * @param[in]	layer - OPTIONAL. The drawing layer of the object.
 *				Greater values will cause the object to be drawn above
 *				others. Negative values are allowed. Default is 0.
 *				Objects at the same layer are drawn in an undefined
 *				order.
*******************************************************************************/
void DrawingManager::drawObject(Drawable* obj, int layer)
{
	if (!isDrawingObject(obj))
	{
		drawables[layer].push_back(obj);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Checks whether an object is currently being drawn.
 *
 * @param[in]	obj - Pointer to the object to search for.
 *
 * @returns True if the object is being drawn, false if not.
*******************************************************************************/
bool DrawingManager::isDrawingObject(Drawable* obj)
{
	// Loop through every later and every object in that row until we find obj
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			if (d == obj)
			{
				return true;	// Found it!
			}
		}
	}
	return false;	// Didn't find it :(
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Determines the layer given the object is drawn at.
 *
 * @param[in]	-obj - Pointer to the object to search for.
 *
 * @returns The layer at which the object is being drawn. If object is
 *		not being drawn, will return 0.
*******************************************************************************/
int DrawingManager::getDrawingLayer(Drawable* obj)
{
	// Loop through every later and every object in that row until we find obj
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			if (d == obj)
			{
				iterator -> first;
			}
		}
	}
	return 0;	// If object is not found, return default value of 0.
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Removes an object from the drawing list and no longer draws
 *		it. Must be done before the object becomes deallocated.
 *
 * @param[in]	obj - Pointer to the object to no longer draw.
*******************************************************************************/
void DrawingManager::stopDrawingObject(Drawable* obj)
{
	// For every later, remove reference to object. Don't bother searching.
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		iterator->second.remove(obj);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Stops drawing all objects, clearing the drawing list.
*******************************************************************************/
void DrawingManager::stopDrawingAll()
{
	drawables.clear();
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Drawing function. Draws all registered drawable objects
 *      ordered by layers in ascending order.
*******************************************************************************/
void DrawingManager::draw()
{
	// Draw all registered drawables
	typedef map<int, list<Drawable*>>::iterator it_type;
	for (it_type iterator = drawables.begin();
		iterator != drawables.end();
		iterator++)
	{
		for (Drawable* d : iterator->second)
		{
			d->draw();
		}
	}
}
