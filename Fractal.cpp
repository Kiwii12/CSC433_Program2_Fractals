/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the implementatio for the View class.
 *
 * @brief Contains the implementation for the Fractal class.
*******************************************************************************/
#include "Fractal.h"

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * Constructor, sets initiator_direction in private data
 *****************************************************************************/
Fractal::Fractal()
	: initiator_direction(true)
{
	
}
	
/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * adds a list into the data for the class
 * 
 * 
 * @param[in]      Const list<point> &initiator - list for initiator
 *****************************************************************************/
void Fractal::loadInitiator(const list<point> &initiator)
{
	this -> initiator = initiator;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * adds a list into the data for the class
 * 
 * 
 * @param[in]      Const list<point> &generator - list for generator
 *****************************************************************************/
void Fractal::loadGenerator(const list<point> &generator)
{
	this -> generator = generator;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * changes the initiator direction
 * 
 * 
 * @param[in]      bool direction - clockwise, counterclockwise
 *****************************************************************************/
void Fractal::setInitiatorDirection(bool direction)
{
	this -> initiator_direction = direction;
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * empties initiator list
 *****************************************************************************/
void Fractal::clearInitiator()
{
	initiator.clear();
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * empties generator list
 *****************************************************************************/
void Fractal::clearGenerator()
{
	generator.clear();
}

/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:
 * empties fractal list
 *****************************************************************************/
void Fractal::clearFractal()
{
	fractal.clear();
}
