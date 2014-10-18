#include "Line.h"

/**************************************************************************//**
 * @author Johnny Ackerman
 * 
 * @par Description: allocates a two demensional array
 * 
 * @returns this_array - the newly allocated 2D array
 * 
 *****************************************************************************/
double** Line::d2array ()
{
	//loop variables
	int i = 0;
	int j = 0;
	
	//makes sure the array is initialized to nullptr
	double **this_array = nullptr;

	//allocates memory
	this_array = new (nothrow) double * [Rows];

	//checks if memory was allocated
	if (this_array == nullptr)
		return nullptr;

	//loops through and allocated the second part
	for (i=0; i < Rows; i++)
	{
		this_array[i] = new (nothrow) double [Cols];

		//delets all allocated memory if an error occured
		if (this_array[i] == nullptr)
		{
			for (j=0; j < Rows; j++)
			{
				delete [] this_array[j];
			}
			delete [] this_array;
			this_array = nullptr;
			return nullptr;
		}
	}
	if (this_array == nullptr)
	{
		cout << "memory or allocation error";
		exit(0);
	}
	return this_array;
}

/**************************************************************************//** 
 * @author Johnathan Ackerman
 * 
 * @par Description: deletes a given array
 * 
 * @param[in]	   double **&this_array - the array being deleted
 * 
 *****************************************************************************/
void Line::d2array_delete( double **&this_array)
{
	//loop variable
	int j = 0;

	//deletes array starting with furthest allocation
	for (j=0; j < Rows; j++)
	{
		delete [] this_array[j];
	}
	delete [] this_array;

	//sets array back to nullptr
	this_array = nullptr;

	return;
}


void Line::setRows( int Rows )
{
	this -> Rows = Rows;
}

void Line::setCols( int Cols )
{
	this -> Cols = Cols;
}