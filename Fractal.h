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
	/**
	* @brief Struct to contain point data for initiator, generator, and fractal
	*/
	struct point
	{
		double x;			/*!< X position of the point */
		double y;			/*!< Y position of the point */
		double angle;		/*!< Angle from current point to next point */
		double distance;	/*!< Distance from current point to next point */
	};
	
	Fractal();
	
	/*!
	* @brief Loads points in the initiator
	*/
	void loadInitiator(const list<point> &initiator);
	
	/*!
	* @brief Loads points in the generator
	*/
	void loadGenerator(const list<point> &generator);
	
	/*!
	* @brief Sets the direction the initiator travels
	*/
	void setInitiatorDirection(bool direction);
	
	/*!
	* @brief Generates a fractal using the loaded initiator and generator
	*/
	void generateFractal();
	
	/*!
	* @brief Clears all points from the initiator
	*/
	void clearInitiator();
	
	/*!
	* @brief Clears all points from the generator
	*/
	void clearGenerator();
	
	/*!
	* @brief Clears all points from the generated fractal
	*/
	void clearFractal();
	
	/*!
	* @brief Draws the generated fractal
	*/
	void draw();
	
private:
	bool initiator_direction;	/*!< Direction initiator goes */
	list<point> initiator;		/*!< Points in the initiator */
	list<point> generator;		/*!< Points in the generator */
	list<point> fractal;		/*!< Points in the fractal */
};

#endif
