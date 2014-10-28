/***************************************************************************//**
 * @author Daniel Andrus
 *
 * @Date	9/30/2014
 * @file File containing the declaration for the Drawable class.
 *
 * @brief Contains the declaration for the Drawable class.
*******************************************************************************/
#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include <GL/freeglut.h>

/*******************************************************************************
 *                              CLASS INTERFACE
 ******************************************************************************/
/*!
 * @brief Interface for the Drawable class. Declares single virtual function
 * draw().
 *
 * @details Declares a single virtual function draw() that defines how an object
 * is drawn using GLUT.
 */
class Drawable
{
public:
	/*!
	* @brief Function defining how the object is drawn.
	*/
	virtual void draw() = 0;
};

#endif
