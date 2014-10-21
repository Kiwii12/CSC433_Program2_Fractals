/***************************************************************************//**
 * @file File containing the declaration for the Fractal class.
 *
 * @brief Contains the declaration for the Fractal class, the class that
 *      generates a fractal from an initiator and a generator.
*******************************************************************************/
#ifndef _FRACTAL_H_
#define _FRACTAL_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class Fractal;

#include<list>
#include "Drawable.h"

/***************************************************************************//**
 * @brief The Fractal class is responsible for generating a fractal using an
 *      initiator and a generator.
 *
 * @details This class takes in an initiator and a generator and builds a
 *      fractal.
*******************************************************************************/
class Fractal::public Drawable
{
public:
	struct point
	{
		double x;
		double y;
		double angle;
		double distance;
	};
	
	Fractal();
	
	void loadInitiator(const list<point> &initiator);
	void loadGenerator(const list<point> &generator);
	void setInitiatorDirection(bool direction);
	void generateFractal();
	void clearInitiator();
	void clearGenerator();
	void clearFractal();
	void draw();
	
private:
	bool initiator_direction;
	list<point> initiator;
	list<point> generator;
	list<point> fractal;
};

#endif
