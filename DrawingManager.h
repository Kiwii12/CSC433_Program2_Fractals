/***************************************************************************//**
 * @file File containing the declaration for the DrawingManager class.
 *
 * @brief Contains the declaration for the DrawingManager class.
*******************************************************************************/
#ifndef _DRAWINGMANAGER_H_
#define _DRAWINGMANAGER_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class DrawingManager;

#include <map>
#include <list>
#include "Drawable.h"

using namespace std;

/***************************************************************************//**
 * @brief The DrawingManager class provides methods for managing multiple
 *      drawable objects.
 *
 * @details This class provides a way to manage multiple drawable objects and
 *      organize objects into layers.
*******************************************************************************/
class DrawingManager : public Drawable
{
private:
	map<int, list<Drawable*>> drawables;	/*!< list of objects to draw*/

public:
	/*!
	 * @brief Registers a Drawable object to be drawn on demand.
	 */
	void drawObject(Drawable* obj, int layer = 0);
		
	/*!
	 * @brief Checks whether an object is currently being drawn.
	 */
	bool isDrawingObject(Drawable* obj);

	/*!
	 * @brief Determines the layer given the object is drawn at.
	 */
	int getDrawingLayer(Drawable* obj);

	/*!
	 * @brief Sets the drawing layer of an already registered object.
	 */
	void setDrawingLayer(Drawable* obj, int layer);

	/*!
	 * @brief Removes an object from the drawing list and no longer draws
	 *		it. Must be done before the object becomes deallocated.
	 */
	void stopDrawingObject(Drawable* obj);

	/*!
	 * @brief Stops drawing all objects, clearing the drawing list.
	 */
	void stopDrawingAll();

	/*!
	 * @brief Function defining how the object is drawn.
	 */
	void draw();

};

#endif
