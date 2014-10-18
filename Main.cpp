



/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: 
 * This function primarly passes control to the Fractol class.
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 program ran successfully.
 *****************************************************************************/
int main( int argc, char *argv[] )
{
	// Initialize program's core class
	Fractal Fractal;

	// Run everything through the Pong class
	return Fractal.run( argc, argv);
}