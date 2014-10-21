/***************************************************************************//**
 * @file File containing the declaration for the Line class.
 *
 * @brief This Class is to keep track of the drawn lines from user input
*******************************************************************************/
#ifndef _LINE_H_
#define _LINE_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class Line;

#include <iostream>
#include "Fractal.h"


class Line
{
public:
	Line();
	~Line();

	void setRows( int Rows );
	void setCols( int Cols );


	double** d2array( );
	void d2array_delete( double **&this_array);
	void addLine( double x1, double y1, double x2, double y2 );

private:
	int number_of_lines;
	int Rows;
	int Cols;

};

#endif
