/***************************************************************************//**
 * @file File containing the implementation of the Fractal class.
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Fractal.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
Fractal::Fractal()
{

}

Fractal::~Fractal()
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
int Fractal::run( int argc, char *argv[] )
{
	srand((unsigned int) time(NULL));

	// perform various OpenGL initializations
    glutInit( &argc, argv );

	// Put window in center of screen
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	if (w != 0 && h != 0)
	{
		w = w / 2 - view_width / 2;
		h = h / 2 - view_height / 2;
	}

	// Initialize glut with 32-bit graphics, double buffering, and anti-aliasing
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set up the program window
    glutInitWindowSize( view_width, view_height);    // initial window size
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
	glutTimerFunc(0, *::step, 0);

    // Go into OpenGL/GLUT main loop
    glutMainLoop();

    return 0;

}