/***************************************************************************//**
 * @file File containing the implementation of the Fractals class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Fractals.h"

Fractals* Fractals::instance = NULL;

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
Fractals::Fractals()
	: view_x(0), view_y(0), view_width(735), view_height(480),
	window_width((int) view_width), window_height((int) view_height),
	window_name("Fractals"),
	initiatorView(view_x, view_y, view_width, view_height),
	generatorView(view_x, view_y, view_width, view_height),
	fractalView(view_x, view_y, view_width, view_height)
{
	instance = this;
	
	registerView("Fractal", &fractalView);
	registerView("Initiator", &initiatorView);
	registerView("Generator", &generatorView);
}

Fractals::~Fractals()
{

}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Begins running the program. Initializes OpenGL, registers
 *		events, instantiates objects, and runs the game. Beware when
 *		calling this function, as it enters the OpenGL main loop, only
 *		to return at end of program execution.
 *
 * @returns Status code of the program. 0 means no problems.
*******************************************************************************/
int Fractals::run( int argc, char *argv[] )
{
	srand((unsigned int) time(NULL));

	window_width = (int) view_width;
	window_height = (int) view_height;

	// perform various OpenGL initializations
    glutInit( &argc, argv );

	// Put window in center of screen
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	if (w != 0 && h != 0)
	{
		w = w / 2 - window_width / 2;
		h = h / 2 - window_height / 2;
	}

	// Initialize glut with 32-bit graphics, double buffering, and anti-aliasing
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set up the program window
    glutInitWindowSize( window_width, window_height);    // initial window size
    glutInitWindowPosition( w, h );                  // initial window position
    glutCreateWindow( window_name.c_str() );         // window title

	// Always clear screen to black
	glClearColor( 0, 0, 0, 1.0 );

	glutIgnoreKeyRepeat(1);

    // Register callbacks
    glutDisplayFunc( *::display );
    glutReshapeFunc( *::reshape );
    glutKeyboardFunc( *::keyDown );
	glutKeyboardUpFunc( *::keyUp );
	glutSpecialFunc( *::keySpecialDown );
	glutSpecialUpFunc( *::keySpecialUp );
    glutMouseFunc( *::mouseclick );
	glutMotionFunc( *::mousedrag );
	glutPassiveMotionFunc( *::mousemove );

	// allow XORing
    glEnable( GL_COLOR_LOGIC_OP ); //used for rubberbanding

	switchView("Initiator");

    // Go into OpenGL/GLUT main loop
    glutMainLoop();

    return 0;

}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Function to get the current instance of the program.
 *
 * @returns Pointer to the current instance of the program.
*******************************************************************************/
Fractals* Fractals::getInstance()
{
	return instance;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the width of the view port in the virtual space.
 * 
 * @returns The width of the view port in pixels.
*******************************************************************************/
double Fractals::getViewWidth()
{
	return view_width;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the height of the view port in the virtual space.
 *
 * @returns The height of the view port in pixels.
*******************************************************************************/
double Fractals::getViewHeight()
{
	return view_height;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Drawing callback. Executes every glut display callaback.
 *		Also calls the draw function of all registerd Drawable objects.
*******************************************************************************/
void Fractals::display()
{
	//clear the display and set backround to black
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1.0, 1.0, 1.0 );
    
	ViewManager::draw();
	DrawingManager::draw();

	// Flush graphical output
    glutSwapBuffers();
    glFlush();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Resize callback. Executes whenever the window is resized.
 *
 * @param[in]	w - The window's new width in pixels.
 * @param[in]	h - The window's new height in pixels.
*******************************************************************************/
void Fractals::reshape(int w, int h)
{
	// store new window dimensions globally
    window_width = w;
    window_height = h;

	/* Ignore window resizes and just roll with it. Just stretch the content.
	 * Laziness to the max.
	double ratio = (double) view_width / (double) view_height;
	double scale;

    // Orthographic projection of 3-D scene onto 2-D, maintaining aspect ratio
    glMatrixMode( GL_PROJECTION );		// Use an orthographic projection
    glLoadIdentity();					// Initialize transformation matrix
	if (w > h * ratio)					// Adjust viewport based on ratio
	{
		scale = (double) h / (double) view_height;
		this -> scale = scale;
		gluOrtho2D( 0 - ((w / scale) - view_width) / 2,
			view_width + ((w / scale) - view_width) / 2,
			0,
			view_height );
		
		view_x = (int) (w / scale - view_width) / 2;
		view_y = 0;
	}
	else
	{
		scale = (double) w / (double) view_width;
		this -> scale = scale;
		gluOrtho2D( 0,
			view_width,
			0 - ((h / scale) - view_height) / 2,
			view_height + ((h / scale) - view_height) / 2 );

		view_x = 0;
		view_y = (int) (h / scale - view_height) / 2;
	}
	*/
    glViewport( 0, 0, w, h );			// Adjust viewport to new window

    // Switch back to (default) model view mode, for transformations
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key down callback. Executes whenever a typical key is
 *		pressed.
 *
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Fractals::keyDown(unsigned char key, int x, int y)
{
    // TODO
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key up callback. Executes whenever a typical key is
 *		released.
 * 
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Fractals::keyUp(unsigned char key, int x, int y)
{
	// TODO
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key down callback. Executes whenever a "special"
 *		key such as an arrow key is pressed.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Fractals::keySpecialDown(int key, int x, int y)
{
	// TODO
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key up callback. Executes whenever a "special" key
 *		such as an arrow key is released.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void Fractals::keySpecialUp(int key, int x, int y)
{
	// TODO
}

/***************************************************************************//**
 * @author Johnny Ackerman
 * 
 * @par Description: Mouse click callback. Executes whenever a mouse button is
 *		either clicked or released.
 *  
 * @param[in]	button - The button whose state was changed.
 * @param[in]	state - The new state of the button.
 * @param[in]	x - The x coordinate of the mouse at the time the button
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the button
 *				was pressed.
*******************************************************************************/
void Fractals::mouseclick(int button, int state, int x, int y)
{
	double vx;	// view x
	double vy;	// view y

	// Correct for coordinate system
	vx = x;
    vy = window_height - y;

	// Correct for scaling
	vx *= view_width / window_width;
	vy *= view_height / window_height;

	vx -= view_x;
	vy -= view_y;

	if (getActiveView() != NULL)
	{
		getActiveView()->mouseclick(button, state, vx, vy);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void Fractals::mousemove(int x, int y)
{
	double vx;	// view x
	double vy;	// view y

	// Correct for coordinate system
	vx = x;
    vy = window_height - y;

	// Correct for scaling
	vx *= view_width / window_width;
	vy *= view_height / window_height;

	vx -= view_x;
	vy -= view_y;

	if (getActiveView() != NULL)
	{
		getActiveView()->mousemove(vx, vy);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window while a button is pressed.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void Fractals::mousedrag(int x, int y)
{
	double vx;	// view x
	double vy;	// view y

	// Correct for coordinate system
	vx = x;
    vy = window_height - y;

	// Correct for scaling
	vx *= view_width / window_width;
	vy *= view_height / window_height;

	vx -= view_x;
	vy -= view_y;

	if (getActiveView() != NULL)
	{
		getActiveView()->mousedrag(vx, vy);
	}
}

/*******************************************************************************
 *                         GLUT CALLBACK FUNCTIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Drawing callback. Executes every glut display callaback.
 *		Also calls the draw function of all registerd Drawable objects.
*******************************************************************************/
void display()
{
	Fractals::getInstance()->display();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Resize callback. Executes whenever the window is resized.
 *
 * @param[in]	w - The window's new width in pixels.
 * @param[in]	h - The window's new height in pixels.
*******************************************************************************/
void reshape(int w, int h)
{
	Fractals::getInstance()->reshape(w, h);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key down callback. Executes whenever a typical key is
 *		pressed.
 *
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keyDown(unsigned char key, int x, int y)
{
	Fractals::getInstance()->keyDown(key, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key up callback. Executes whenever a typical key is
 *		released.
 * 
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keyUp(unsigned char key, int x, int y)
{
	Fractals::getInstance()->keyUp(key, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key down callback. Executes whenever a "special"
 *		key such as an arrow key is pressed.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keySpecialDown(int key, int x, int y)
{
	Fractals::getInstance()->keySpecialDown(key, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Special key up callback. Executes whenever a "special" key
 * 		such as an arrow key is released.
 *  
 * @param[in]	key - Special GLUT enumerator of the key.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keySpecialUp(int key, int x, int y)
{
	Fractals::getInstance()->keySpecialUp(key, x, y);
}

/***************************************************************************//**
 * @author Johnny Ackerman
 * 
 * @par Description: Mouse click callback. Executes whenever a mouse button is
 * 		either clicked or released.
 *  
 * @param[in]	button - The button whose state was changed.
 * @param[in]	state - The new state of the button.
 * @param[in]	x - The x coordinate of the mouse at the time the button
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the button
 *				was pressed.
*******************************************************************************/
void mouseclick(int button, int state, int x, int y)
{
	Fractals::getInstance()->mouseclick(button, state, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void mousemove(int x, int y)
{
	Fractals::getInstance()->mousemove(x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window while a button is pressed.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void mousedrag(int x, int y)
{
	Fractals::getInstance()->mousedrag(x, y);
}
