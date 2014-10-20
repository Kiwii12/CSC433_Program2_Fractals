/***************************************************************************//**
 * @file 
 *
 * @mainpage Program 2 - Fractals
 * 
 * @section course_section Course Information 
 *
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @date Oct 24, 2014
 * 
 * @par Professor: 
 *         Dr. Weiss
 * 
 * @par Course: 
 *         CSC-433 - M001-2014FA -  9:00-9:50 AM MWF
 * 
 * @par Location: 
 *         McLaury-311
 *
 * @section program_section Program Information 
 * 
 * @details This is a fractal drawing program designed to allow a user to
 * generate complex fractals using a simple graphical interface.
 *
 * GLUT and OpenGL are the libraries used for gui management.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions: 
 *      Build and run
 * 
 * @par Build:
   @verbatim
   > g++ -std=c++11 -lGL -lglut -lGLU -o fractals
   @endverbatim
 * 
 * @par Make:
   @vertbatim
   > make fractals
   @endverbatim
 * 
 * @par Usage: 
   @verbatim  
   > fractals
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ----------   ---------------------------------------------------------------
   10-05-2014	Created GitHub repo
   10-18-2014	Added program components and fractal functions
   @endverbatim
 *
 ******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Fractal.h"

/**************************************************************************//**
 * @author Johnny Ackerman
 * 
 * @par Description:
 * Main function of the program. This function primarly passes control to the
 * Fractal class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 - program ran successfully.
 *****************************************************************************/
int main( int argc, char *argv[] )
{
	// Initialize program's core class
	Fractal fractal;

	// Run everything through the Pong class
	return fractal.run( argc, argv);
}
