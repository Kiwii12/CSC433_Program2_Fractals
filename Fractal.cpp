#include "Fractal.h"

Fractal::Fractal()
	: initiator_direction(true)
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
	this -> initiator_direction = direction;
}

void Fractal::generateFractal()
{
	// TODO Code to generate fractal
}

void Fractal::clearInitiator()
{
	initiator.clear();
}

void Fractal::clearGenerator()
{
	generator.clear();
}

void Fractal::clearFractal()
{
	fractal.clear();
}

void Fractal::draw()
{
	// TODO Code to draw fractal
}
