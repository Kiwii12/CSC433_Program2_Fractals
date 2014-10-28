/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the implementation of the Fractals class.
 *
 * @brief implementation for handeling callbacks
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Fractals.h"

Fractals* Fractals::instance = NULL;
const double Fractals::vview_x = 16.0;
const double Fractals::vview_y = 16.0;
const double Fractals::vview_w = 704.0;
const double Fractals::vview_h = 512.0;
const double Fractals::button_w = 100.0;
const double Fractals::button_h = 32.0;
const double Fractals::button_x = vview_x + vview_w - button_w * 2;
const double Fractals::button_y = vview_y * 2 + vview_h;

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Constructor, initializes data, registers data with other
 *	classes, and creates instances of subClasses
*******************************************************************************/
Fractals::Fractals()
: view_x(0), view_y(0), view_width(vview_w + 32),
view_height(vview_h + button_h + vview_y * 3),
window_width((int) view_width), window_height((int) view_height),
window_name("Fractals")
{
	instance = this;
	
	// Generate views
	initiatorView = new (nothrow) InitiatorView(
		vview_x, vview_y, vview_w, vview_h
	);
	generatorView = new (nothrow) GeneratorView(
		vview_x, vview_y, vview_w, vview_h
	);
	fractalView = new (nothrow) FractalView(
		vview_x, vview_y, vview_w, vview_h
	);

	// Register views
	registerView("Fractal", fractalView);
	registerView("Initiator", initiatorView);
	registerView("Generator", generatorView);

	// Generate tabs
	tabs.push_back(new (nothrow) TabButton("Fractal",
		vview_x, vview_y * 2 + vview_h, button_w, button_h
	));
	tabs.push_back(new (nothrow) TabButton("Initiator",
		vview_x * 2 + button_w, vview_y * 2 + vview_h, button_w, button_h
	));
	tabs.push_back(new (nothrow) TabButton("Generator",
		vview_x * 3 + button_w * 2, vview_y * 2 + vview_h, button_w, button_h
	));

	// Give tabs some action
	tabs[0]->setAction([](){
		for (auto tab : Fractals::getInstance()->tabs)
		{
			tab->active = false;
		}
		Fractals::getInstance()->tabs[0]->active = true;
		Fractals::getInstance()->switchView("Fractal");
		glutPostRedisplay();
	});
	tabs[1]->setAction([](){
		for (auto tab : Fractals::getInstance()->tabs)
		{
			tab->active = false;
		}
		Fractals::getInstance()->tabs[1]->active = true;
		Fractals::getInstance()->switchView("Initiator");
		glutPostRedisplay();
	});
	tabs[2]->setAction([](){
		for (auto tab : Fractals::getInstance()->tabs)
		{
			tab->active = false;
		}
		Fractals::getInstance()->tabs[2]->active = true;
		Fractals::getInstance()->switchView("Generator");
		glutPostRedisplay();
	});

	// And finally... register the buttons
	for (auto tab : tabs)
	{
		drawObject(tab);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Destructor, destroys subclasses
*******************************************************************************/
Fractals::~Fractals()
{
	delete initiatorView;
	delete generatorView;
	delete fractalView;

	for (auto tab : tabs)
	{
		delete tab;
	}
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
    glutInitDisplayMode( GLUT_RGBA /*| GLUT_DOUBLE*/ | GLUT_MULTISAMPLE );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set up the program window
    glutInitWindowSize( window_width, window_height);    // initial window size
    glutInitWindowPosition( w, h );                  // initial window position
    glutCreateWindow( window_name.c_str() );         // window title

	// Always clear screen to black
	glClearColor( 1.0, 1.0, 1.0, 1.0 );

	glutIgnoreKeyRepeat(1);

    // Register callbacks
    glutDisplayFunc( *::display );
    glutReshapeFunc( *::reshape );
    glutMouseFunc( *::mouseclick );
	glutMotionFunc( *::mousedrag );
	glutPassiveMotionFunc( *::mousemove );
	
	tabs[0]->active = true;
	switchView("Fractal");

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
 * @par Description: Draws the background and the fractal
*******************************************************************************/
void Fractals::draw()
{


	ViewManager::draw();
	DrawingManager::draw();
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
    view_width = window_width = w;
    view_height = window_height = h;

    glMatrixMode( GL_PROJECTION );		// Use an orthographic projection
    glLoadIdentity();					// Initialize transformation matrix
	
	// Adjust viewport and map to window
	gluOrtho2D(0, view_width, 0, view_height);
    glViewport( 0, 0, window_width, window_height );

    // Switch back to (default) model view mode, for transformations
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
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

	// Forward event to tabs
	for (auto tab : tabs)
	{
		tab->mouseclick(button, state, vx, vy);
	}

	// Forward event to active view
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

	// Forward event to tabs
	for (auto tab : tabs)
	{
		tab->mousemove(vx, vy);
	}

	// Forward event to active view
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

	// Forward event to tabs
	for (auto tab : tabs)
	{
		tab->mousedrag(vx, vy);
	}

	// Forward event to active view
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
