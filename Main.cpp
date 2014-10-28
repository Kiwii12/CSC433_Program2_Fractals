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
 *
 * Extras  Has Tabs and many useful buttons. Displays Errors for user. 
 *	Has a drawing grid to help the user draw. Has user friendly
 *  instructions. Limited memory usage to half a "gigabyte" so more
 *	complex fractals can be draw without limiting the itterations of
 *	simpler fractals
 *
 * GLUT and OpenGL are the libraries used for gui management.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions: 
 *      Build and Run
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
 * @Bugs	-	Runs Slowly on weak computers for complex fractals
 *				Linux OpenGL or GLUT has an uncommon GL_LINE_LOOP bug
 *
 * @todo	-	Add parallel programing so program doesn't stops during
 *					Fractalization
 *
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ----------   ---------------------------------------------------------------
   10-05-2014	Created GitHub repo
   10-18-2014	Added program components and several classes
   10-22-2014	Added different views
   10-23-2014	Added mouse handling and rubberbanding
   10-24-2014	Major visual overhaul
   10-24-2014	Added fractal generation
   10-25-2014	Made compatible with linux and fixed compile errors and warnings
   10-26-2014	Added most documentation
   10-27-2014	Added memory limit on fractal generation to prevent crashes
   				Added error messages and user prompts and finalized project
   @endverbatim
 *
 ******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "Fractals.h"

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
	Fractals fractals;

	// Run everything through the Fractals class
	return fractals.run( argc, argv);
}
