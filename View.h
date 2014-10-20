/***************************************************************************//**
 * @file File containing the declaration for the View class.
 *
 * @brief Contains the declaration for the View class.
*******************************************************************************/
#ifndef _VIEW_H_
#define _VIEW_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Drawable.h"

/*******************************************************************************
 *                              CLASS INTERFACE
 ******************************************************************************/
/*!
 * @brief Interface for a View class. Declares functions for hiding and showing
 * view.
 *
 * @details Provides functions and data for hiding and showing view and item
 * management.
 */
class View : public Drawable
{
	private:
		bool hidden;		/*!< Whether or not view is shown on screen */

	public:
		View();

		/*!
		 * @brief Allows this object to be drawn.
		 */
		void show();
		
		/*!
		 * @brief Prevents this object from being drawn.
		 */
		void hide();
		
		/*!
		 * @brief Checks if this object is being drawn.
		 */
		bool isHidden();

		/*!
		 * @brief Function defining how the object is drawn.
		 */
		void draw();
};

#endif
