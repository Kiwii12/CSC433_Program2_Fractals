/***************************************************************************//**
 * @file File containing the declaration for the Fractals class.
 *
 * @brief Contains the declaration for the Fractals class, the core class of the
 *		entire program.
*******************************************************************************/
#ifndef _FRACTALS_H_ //makes sure class is not declared twice
#define _FRACTALS_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class Fractals;

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <GL/freeglut.h>
#include <time.h>
#include "DrawingManager.h"

using namespace std;

/***************************************************************************//**
 * @brief The Fractals class is in charge of window management, drawing
 *		all the parts of the screen, and running the other classes. It also
 *		handles the interaction between glut and the program and event
 *		management.
 *
 * @details This class essentially provides a base for the rest of the program.
 *		It handles drawing functions, forwards OpenGL events, generates a
 *		framerate, and standardizes various aspects of the program.
*******************************************************************************/
class Fractals : public DrawingManager
{
private:
	static Fractals* instance;	/*!< reference to main instance */
	int view_x;					/*!< The x offset of the drawing region */
	int view_y;					/*!< The y offset of the drawing region */
	int view_width;				/*!< The width of the drawable region */
	int view_height;			/*!< The height of the drawable region */
	int window_width;			/*!< Width of gui window */
	int window_height;			/*!< Height of gui window */
	double scale;				/*!< Scale of the gui contents */
	string window_name;			/*!< Name of the gui window */

public:
	Fractals();
	~Fractals();
	int run( int argc, char *argv[] );


	/*!
	* @brief Function to get the current instance of the program.
	*/
	static Fractals* getInstance( );

	/*!
	* @brief Gets the width of the view port in the virtual space.
	*/
	int getViewWidth();

	/*!
	* @brief Gets the height of the view port in the virtual space.
	*/
	int getViewHeight();

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
