/***************************************************************************//**
 * @file File containing the declaration for the Fractal class.
 *
 * @brief Contains the declaration for the Fractal class, the core class of the
 *		entire program.
*******************************************************************************/
#ifndef _FRACTAL_H_ //makes sure class is not declared twice
#define _FRACTAL_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class Fractal;

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <GL/freeglut.h>
#include <time.h>
#include "Drawable.h"

using namespace std;


class Fractal
{
	public:
		Fractal();
		~Fractal();

		/*!
		 * @brief Drawing callback. Executes every glut display callaback. Also
		 *		calls the draw function of all registerd Drawable objects.
		 */
		void display();

		/*!
		 * @brief Resize callback. Executes whenever the window is resized.
		 */
		void reshape( int w, int h );

		/*!
		 * @brief Key down callback. Executes whenever a typical key is pressed.
		 */
		void keyDown(unsigned char key, int x, int y);

		/*!
		 * @brief Key up callback. Executes whenever a typical key is released.
		 */
		void keyUp(unsigned char key, int x, int y);

		/*!
		 * @brief Special key down callback. Executes whenever a "special" key
		 *		such as an arrow key is pressed.
		 */
		void keySpecialDown(int key, int x, int y);

		/*!
		 * @brief Special key up callback. Executes whenever a "special" key
		 *		such as an arrow key is released.
		 */
		void keySpecialUp(int key, int x, int y);

		/*!
		 * @brief Mouse click callback. Executes whenever a mouse button is
		 *		either clicked or released.
		 */
		void mouseclick( int button, int state, int x, int y );

		/*!
		 * @brief Step callback. Called every frame of the game. Calls step
		 *		function of other classes necessary for the game. Necessary
		 *		for game elemnts that are not dependent on user interaction.
		 */
		void step();
};



/*******************************************************************************
 *                         GLUT CALLBACK FUNCTIONS
*******************************************************************************/
/*!
 * @brief Drawing callback. Executes every glut display callaback. Also
 *		calls the draw function of all registerd Drawable objects. simply
 *		forwards to Pong class' identical function.
 */
void display();

/*!
 * @brief Resize callback. Executes whenever the window is resized.
 *		Simply forwards to Pong class' identical function.
 */
void reshape( int w, int h );

/*!
 * @brief Key down callback. Executes whenever a typical key is pressed.
 *		Simply forwards to Pong class' identical function.
 */
void keyDown(unsigned char key, int x, int y);

/*!
 * @brief Key up callback. Executes whenever a typical key is released.
 *		Simply forwards to Pong class' identical function.
 */
void keyUp(unsigned char key, int x, int y);

/*!
 * @brief Special key down callback. Executes whenever a "special" key
 * 		such as an arrow key is pressed. Simply forwards to Pong class'
 *		identical function.
 */
void keySpecialDown(int key, int x, int y);

/*!
 * @brief Special key up callback. Executes whenever a "special" key
 * 		such as an arrow key is released. Simply forwards to Pong class'
 *		identical function.
 */
void keySpecialUp(int key, int x, int y);

/*!
 * @brief Mouse click callback. Executes whenever a mouse button is
 * 		either clicked or released. Simply forwards to Pong class'
 * 		identical function.
 */
void mouseclick( int button, int state, int x, int y );

/*!
 * @brief Step callback. Called every frame of the game. Calls step
 *		function of other classes necessary for the game. Necessary
 *		for game elemnts that are not dependent on user interaction.
 *		Simply to Pong class' step() function.
 */
void step(int i);

#endif
