/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the declaration for the Fractals class.
 *
 * @brief Contains the declaration for the Fractals class, the core class of the
 *      entire program.
*******************************************************************************/
#ifndef _FRACTALS_H_ //makes sure class is not declared twice
#define _FRACTALS_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class Fractals;

/**
 * @brief Struct to contain point data for initiator, generator, and fractal
 */
struct point
{
	double x;			/*!< X position of the point */
	double y;			/*!< Y position of the point */
	double angle;		/*!< Angle from current point to next point */
	double distance;	/*!< Distance from current point to next point */
};

#include <iostream>
#include <string>
#include <GL/freeglut.h>
#include <vector>
#include "DrawingManager.h"

#include "ViewManager.h"
#include "InitiatorView.h"
#include "GeneratorView.h"
#include "FractalView.h"
#include "TabButton.h"

using namespace std;

/***************************************************************************//**
 * @brief The Fractals class is in charge of window management, drawing
 *      all the parts of the screen, and running the other classes. It also
 *      handles the interaction between glut and the program and event
 *      management.
 *
 * @details This class essentially provides a base for the rest of the program.
 *      It handles drawing functions, forwards OpenGL events, generates a
 *      framerate, and standardizes various aspects of the program.
*******************************************************************************/
class Fractals : public DrawingManager, public ViewManager
{
private:
	static Fractals* instance;	/*!< reference to main instance */
	double view_x;					/*!< The x offset of the drawing region */
	double view_y;					/*!< The y offset of the drawing region */
	double view_width;				/*!< The width of the drawable region */
	double view_height;			/*!< The height of the drawable region */
	int window_width;			/*!< Width of gui window */
	int window_height;			/*!< Height of gui window */
	string window_name;			/*!< Name of the gui window */

public:
	static const double vview_x;	/*!< left side coordinate of draw area */
	static const double vview_y;	/*!< bottom coordinate of draw area */
	static const double vview_w;	/*!< Width of draw window */
	static const double vview_h;	/*!< height of draw window */
	static const double button_x;	/*!< left coordinate of button */
	static const double button_y;	/*!< right coordinate of button */
	static const double button_w;	/*!< width of button */
	static const double button_h;	/*!< height of button */
	
	InitiatorView* initiatorView;/*!< View controller for initiator view */
	GeneratorView* generatorView;/*!< View controller for generator view */
	FractalView* fractalView;	/*!< View controller for fractal view */
	vector<TabButton*> tabs;

	/*!
	* @brief Constructor, allocates pointers for Initiator, generator and Fractal
	*		views as well as initializes private data.
	*/
	Fractals();

	/*!
	* @brief Destructor, removes pointers.
	*/
	~Fractals();

	/*!
	* @brief Function to get the current instance of the program.
	*/
	int run( int argc, char *argv[] );

	/*!
	* @brief Function to get the current instance of the program.
	*/
	static Fractals* getInstance( );

	/*!
	* @brief Gets the width of the view port in the virtual space.
	*/
	double getViewWidth();

	/*!
	* @brief Gets the height of the view port in the virtual space.
	*/
	double getViewHeight();

	/*!
	 * @brief Drawing function. Calls superclass functions.
	 */
	void draw();

	/*!
	* @brief Drawing callback. Executes every glut display callaback. Also
	*      calls the draw function of all registerd Drawable objects.
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
	*      such as an arrow key is pressed.
	*/
	void keySpecialDown(int key, int x, int y);

	/*!
	* @brief Special key up callback. Executes whenever a "special" key
	*      such as an arrow key is released.
	*/
	void keySpecialUp(int key, int x, int y);

	/*!
	* @brief Mouse click callback. Executes whenever a mouse button is
	*      either clicked or released.
	*/
	void mouseclick( int button, int state, int x, int y );
	
	/*!
	 * @brief Mouse movement callback. Executes whenever a mouse is moved
	 *		inside the program window.
	 */
	void mousemove(int x, int y);

	/*!
	 * @brief Mouse drag callback. Executes whenever a mouse is moved inside
	 *		the program window while a button is pressed.
	 */
	void mousedrag(int x, int y);
	
};



/*******************************************************************************
 *                         GLUT CALLBACK FUNCTIONS
*******************************************************************************/
/*!
 * @brief Drawing callback. Executes every glut display callaback. Also
 *      calls the draw function of all registerd Drawable objects.
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
 *      such as an arrow key is pressed.
 */
void keySpecialDown(int key, int x, int y);

/*!
 * @brief Special key up callback. Executes whenever a "special" key
 *      such as an arrow key is released.
 */
void keySpecialUp(int key, int x, int y);

/*!
 * @brief Mouse click callback. Executes whenever a mouse button is
 *      either clicked or released.
 */
void mouseclick(int button, int state, int x, int y );

/*!
 * @brief Mouse movement callback. Executes whenever a mouse is moved
 *		inside the program window.
 */
void mousemove(int x, int y);

/*!
 * @brief Mouse drag callback. Executes whenever a mouse is moved inside
 *		the program window while a button is pressed.
 */
void mousedrag(int x, int y);

#endif
