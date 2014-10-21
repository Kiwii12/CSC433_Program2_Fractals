#include "Fractal.h"

Fractal::Fractal()
	: direction(true)
{
	
}
	
void Fractal::loadInitiator(const list<point> &initiator)
{
	this -> initiator = initiator;
}

void Fractal::loadGenerator(const list<point> &generator)
{
	this -> generator = generator;
}

void Fractal::setInitiatorDirection(bool direction)
{
	this -> direction = direction;
}

void Fractal::generateFractal()
{
	
}

void Fractal::clearInitiator()
{
	
}

void Fractal::clearGenerator()
{
	
}

void Fractal::clearFractal()
{
	
}

void Fractal::draw()
{
	
}
